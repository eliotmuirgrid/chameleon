//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventLoopDispatch — platform implementations (epoll/kqueue); Windows stub.
//-------------------------------------------------------

#include <BAS/BASeventLoopDispatch.h>
#include <BAS/BASerror.h>
#include <BAS/BASstring.h>

#include <errno.h>
#include <new>

#ifdef _WIN32

struct BASeventLoopDispatch::Impl {
};

BASeventLoopDispatch::BASeventLoopDispatch(Impl* pImpl) : m_pImpl(pImpl) {
}

BASeventLoopDispatch::~BASeventLoopDispatch() {
   delete m_pImpl;
   m_pImpl = nullptr;
}

BASeventLoopDispatch* BASeventLoopDispatch::create(BASstring* pError) {
   (void)pError;
   return nullptr;
}

void BASeventLoopDispatch::signal() {
}

void BASeventLoopDispatch::drain() {
}

int BASeventLoopDispatch::wait(int timeout_ms) {
   (void)timeout_ms;
   return -1;
}

#else

#include <fcntl.h>
#include <unistd.h>

#if defined(__linux__)
#include <sys/epoll.h>
#include <sys/eventfd.h>
#elif defined(__APPLE__)
#include <sys/event.h>
#include <sys/types.h>
#endif

struct BASeventLoopDispatch::Impl {
#if defined(__linux__)
   int epoll_fd;
   int eventfd_fd;
#elif defined(__APPLE__)
   int kqueue_fd;
   int pipe_r;
   int pipe_w;
#endif
};

static void BASeventLoopDispatchAppendError(BASstring* pError, const char* pMsg) {
   if (!pError) {
      return;
   }
   pError->append(pMsg);
   pError->append(BASerrorStringFromErrno(errno));
}

BASeventLoopDispatch::BASeventLoopDispatch(Impl* pImpl) : m_pImpl(pImpl) {
}

BASeventLoopDispatch::~BASeventLoopDispatch() {
   if (!m_pImpl) {
      return;
   }
#if defined(__linux__)
   if (m_pImpl->eventfd_fd >= 0) {
      close(m_pImpl->eventfd_fd);
      m_pImpl->eventfd_fd = -1;
   }
   if (m_pImpl->epoll_fd >= 0) {
      close(m_pImpl->epoll_fd);
      m_pImpl->epoll_fd = -1;
   }
#elif defined(__APPLE__)
   if (m_pImpl->kqueue_fd >= 0) {
      close(m_pImpl->kqueue_fd);
      m_pImpl->kqueue_fd = -1;
   }
   if (m_pImpl->pipe_w >= 0) {
      close(m_pImpl->pipe_w);
      m_pImpl->pipe_w = -1;
   }
   if (m_pImpl->pipe_r >= 0) {
      close(m_pImpl->pipe_r);
      m_pImpl->pipe_r = -1;
   }
#endif
   delete m_pImpl;
   m_pImpl = nullptr;
}

BASeventLoopDispatch* BASeventLoopDispatch::create(BASstring* pError) {
   if (pError) {
      pError->clear();
   }
   Impl* pImpl = nullptr;
   try {
      pImpl = new Impl();
   } catch (const std::bad_alloc&) {
      if (pError) {
         pError->append("BASeventLoopDispatch: alloc failed");
      }
      return nullptr;
   }

#if defined(__linux__)
   pImpl->epoll_fd = -1;
   pImpl->eventfd_fd = -1;
   pImpl->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
   if (pImpl->epoll_fd < 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: epoll_create1: ");
      delete pImpl;
      return nullptr;
   }
   pImpl->eventfd_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
   if (pImpl->eventfd_fd < 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: eventfd: ");
      close(pImpl->epoll_fd);
      delete pImpl;
      return nullptr;
   }
   struct epoll_event ev = {};
   ev.events = EPOLLIN;
   ev.data.fd = pImpl->eventfd_fd;
   if (epoll_ctl(pImpl->epoll_fd, EPOLL_CTL_ADD, pImpl->eventfd_fd, &ev) != 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: epoll_ctl: ");
      close(pImpl->eventfd_fd);
      close(pImpl->epoll_fd);
      delete pImpl;
      return nullptr;
   }
#elif defined(__APPLE__)
   pImpl->kqueue_fd = -1;
   pImpl->pipe_r = -1;
   pImpl->pipe_w = -1;
   int fds[2] = {-1, -1};
   if (pipe(fds) != 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: pipe: ");
      delete pImpl;
      return nullptr;
   }
   pImpl->pipe_r = fds[0];
   pImpl->pipe_w = fds[1];
   (void)fcntl(pImpl->pipe_r, F_SETFL, O_NONBLOCK);
   (void)fcntl(pImpl->pipe_w, F_SETFL, O_NONBLOCK);
   pImpl->kqueue_fd = kqueue();
   if (pImpl->kqueue_fd < 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: kqueue: ");
      close(pImpl->pipe_w);
      close(pImpl->pipe_r);
      delete pImpl;
      return nullptr;
   }
   struct kevent ch = {};
   EV_SET(&ch, pImpl->pipe_r, EVFILT_READ, EV_ADD, 0, 0, nullptr);
   if (kevent(pImpl->kqueue_fd, &ch, 1, nullptr, 0, nullptr) != 0) {
      BASeventLoopDispatchAppendError(pError, "BASeventLoopDispatch: kevent add: ");
      close(pImpl->kqueue_fd);
      close(pImpl->pipe_w);
      close(pImpl->pipe_r);
      delete pImpl;
      return nullptr;
   }
#else
   delete pImpl;
   if (pError) {
      pError->append("BASeventLoopDispatch: unsupported platform (need Linux or macOS)");
   }
   return nullptr;
#endif

   return new BASeventLoopDispatch(pImpl);
}

void BASeventLoopDispatch::signal() {
   if (!m_pImpl) {
      return;
   }
#if defined(__linux__)
   uint64_t inc = 1;
   (void)write(m_pImpl->eventfd_fd, &inc, sizeof(inc));
#elif defined(__APPLE__)
   char b = 1;
   (void)write(m_pImpl->pipe_w, &b, 1);
#endif
}

void BASeventLoopDispatch::drain() {
   if (!m_pImpl) {
      return;
   }
#if defined(__linux__)
   uint64_t v;
   while (read(m_pImpl->eventfd_fd, &v, sizeof(v)) == (ssize_t)sizeof(v)) {
   }
#elif defined(__APPLE__)
   char buf[64];
   ssize_t n;
   while ((n = read(m_pImpl->pipe_r, buf, sizeof(buf))) > 0) {
      (void)n;
   }
#endif
}

int BASeventLoopDispatch::wait(int timeout_ms) {
   if (!m_pImpl) {
      return -1;
   }
#if defined(__linux__)
   struct epoll_event ev = {};
   return epoll_wait(m_pImpl->epoll_fd, &ev, 1, timeout_ms);
#elif defined(__APPLE__)
   struct kevent ev = {};
   struct timespec ts;
   struct timespec* pts = nullptr;
   if (timeout_ms >= 0) {
      ts.tv_sec = timeout_ms / 1000;
      ts.tv_nsec = (long)(timeout_ms % 1000) * 1000000L;
      pts = &ts;
   }
   return kevent(m_pImpl->kqueue_fd, nullptr, 0, &ev, 1, pts);
#else
   (void)timeout_ms;
   return -1;
#endif
}

#endif
