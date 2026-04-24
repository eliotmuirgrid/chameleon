# C/C++ compiler concepts

If you are new to how C/C++ projects become runnable programs, start with [Building C/C++ programs (basics)](A.building-cpp-basics.md). This document assumes that mental model and focuses on the command line levers the shared makefiles use most often.

You write programs in C or C++ so other people can read your intent. The machine does not run that text directly; it runs machine code, the low-level instructions a specific CPU understands. If those terms are new, see [Building C/C++ programs (basics)](A.building-cpp-basics.md) first. Between your editor and a finished program sits a pipeline: the compiler turns each source file into an object file, and the linker stitches those object files into one executable. This repository’s usual link step passes all project objects into a single binary, not separate library archives. The sections below walk that pipeline with real flags. Exact spelling depends on the compiler; GCC and Clang match the examples, while Microsoft’s `cl` uses different switches for the same ideas.

You will read: how a single compile is aimed (`-std`, `-I`, `-c`, `-o`); how header changes are tracked (`-MMD` and `.d` files); what linking looks like on the command line; where to read next. For faster repeated compiles, see [ccache](D.ccache.md).

---

## Steering a single compilation

Each run of the compiler answers a few practical questions: which dialect of the language, where to look for `#include` files, which source file to compile, and where to write the object file. The flags below are the usual answers when you use Clang or GCC (and similar compilers).

Language standard. To request a specific C++ standard (example: C++14), you pass a flag such as:

```text
-std=c++14
```

Other standards follow the same pattern (`-std=c++11`, `-std=c++17`, …). The project’s shared makefile may pin a particular `-std=` in `../makefile.common`; match that or override deliberately when you know what you are doing.

Include search path. The `-I` flag adds a directory to the list the preprocessor searches for headers. In this tree we often use:

```text
-I../
```

so includes resolve one level up from the leaf build directory, matching the name prefix layout (for example headers included as `<COR/CORlog.h>` from the `cpp/` tree). Add more `-I` paths when you need additional roots.

Compile one file, write one object. The `-c` flag means “compile only; do not link.” The source file follows it. The `-o` flag names the output. Together:

```text
-c blah.cpp
-o blah.o
```

On Windows the object extension is often `.obj`; the pairing is the same.

---

## Headers, the preprocessor, and dependency files

When a header changes, every source file that includes it (directly or indirectly) may need to be recompiled. Tracking that by hand does not scale. Compilers can emit makefile snippets, usually files ending in `.d`, that list each object file’s prerequisites: the `.cpp` plus every header that contributed to that compile. GNU `g++` and LLVM/Clang support the `-MMD` flag for this: it writes that rule beside the object, without changing how you think about the compile. Your makefile then includes those files (see [Make concepts](C.make-concepts.md)) so `make` knows the full graph.

Suppose you compile `main.cpp` with `-MMD`. A generated rule might look like the block below. Paths are illustrative; real trees vary. The point is scale: the preprocessor expands `#include` recursively, so a short `.cpp` can still imply a long list of headers.

```makefile
main.o: main.cpp ../COR/CORcommandLine.h ../COR/CORlog.h \
  ../COR/CORostream.h ../COR/CORstring.h ../COR/CORminimumInclude.h \
  ../FIL/FILutils.h ../COR/CORauto.h ../COR/CORerror.h \
  ../COR/CORrefCounted.h ../COR/CORsinkString.h ../COR/CORsink.h \
  ../COR/CORclosure.h ../COR/CORlist.h ../SCK/SCKloop.h \
  ../SCK/SCKsystem.h ../SCK/SCKschedule.h ../COR/CORmap.h \
  ../COR/CORpair.h ../COR/CORhashmap.h ../COR/CORhash.h \
  ../COR/CORdateTime.h ../SCK/SCKnameResolver.h ../SCK/SCKaddress.h \
  ../COR/CORthread.h ../COR/CORthreadQueue.h ../COR/CORqueue.h \
  ../COR/CORlocker.h ../COR/CORmutex.h ../WEB/WEBserver.h \
  ../SCK/SCKlistener.h ../SCKS/SCKSsslContext.h ../COR/CORvector.h \
  ../COR/CORweb.h ../COR/CORvar.h ../WEB/WEBsession.h \
  ../WEB/WEBrequestData.h ../WEB/WEBmainThread.h ../WEB/WEBresponse.h \
  ../WEBI/WEBImimeLookup.h ../COR/CORthreadPool.h ../SCK/SCKutils.h
```

If any of those headers changes, `main.cpp` should be recompiled so `main.o` stays consistent. Details of `-MMD` (and related flags, such as where the `.d` file is written) are in your compiler’s manual. The shared POSIX rules here pass `-MMD` together with `-I../` in `../makefile.common`.

---

## Linking

Linking is the step that combines object files into one executable. The linker resolves references between those `.o` (or `.obj`) files so the whole program is consistent. In this tree, that usually means every compiled object from the project goes into one static binary, matching the shared makefiles’ “link all objects” model.

Example (illustrative):

```text
llvm-g++ main.o life.o -o test
```

Here `main.o` and `life.o` are inputs, and `-o test` names the output program. On POSIX, executables often have no filename extension; on Windows, they usually end in `.exe`. The same `-o` idea selects the output path for the linked program.

---

## Going deeper

Optimization levels, warnings, diagnostics, and advanced linker options live in your compiler’s and linker’s manuals. Those references are authoritative; this file is the map. For incremental compile speed, see [ccache](D.ccache.md).
