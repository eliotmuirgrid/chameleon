#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASuniquePtr
//
// A smart pointer that strictly owns the object it points to.
// Designed for fresh developers: no accidental copies, 
// explicit ownership transfer, and no STL dependencies.
//-------------------------------------------------------

/**
 * HOW TO USE BASuniquePtr:
 * 
 * 1. CREATION:
 *    BASuniquePtr<MyClass> ptr(new MyClass());
 *
 * 2. AUTOMATIC CLEANUP:
 *    When 'ptr' goes out of scope, 'delete' is called automatically.
 *
 * 3. NO ACCIDENTAL COPIES:
 *    BASuniquePtr<MyClass> ptr2 = ptr; // ERROR: Will not compile.
 *    This prevents two pointers from trying to delete the same memory.
 *
 * 4. TRANSFERRING OWNERSHIP (The Move):
 *    If you WANT to move the object to a new owner, use BASmove:
 *    BASuniquePtr<MyClass> ptr2 = BASmove(ptr); 
 *    - ptr2 now owns the object.
 *    - ptr is now NULL and safe to ignore.
 *
 * 5. PASSING TO FUNCTIONS:
 *    void APPprocess(BASuniquePtr<MyClass> p);
 *    APPprocess(BASmove(ptr)); // Explicitly handing off responsibility.
 */

// Internal utility to enable ownership transfer (replaces std::move)
template <typename T>
struct BASremove_reference      { typedef T type; };
template <typename T>
struct BASremove_reference<T&>  { typedef T type; };
template <typename T>
struct BASremove_reference<T&&> { typedef T type; };

template <typename T>
constexpr typename BASremove_reference<T>::type&& BASmove(T&& t) noexcept {
    return static_cast<typename BASremove_reference<T>::type&&>(t);
}

template<typename T>
class BASuniquePtr {
public:
    // Constructors
    BASuniquePtr() : m_ptr(nullptr) {}
    explicit BASuniquePtr(T* ptr) : m_ptr(ptr) {}

    // Destructor - Automatic Cleanup
    ~BASuniquePtr() {
        reset();
    }

    // DISALLOW COPYING
    // Forces developers to be intentional about ownership.
    BASuniquePtr(const BASuniquePtr&) = delete;
    BASuniquePtr& operator=(const BASuniquePtr&) = delete;

    // ALLOW MOVING (Explicit Ownership Transfer)
    BASuniquePtr(BASuniquePtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    BASuniquePtr& operator=(BASuniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    // Manual Management
    void reset(T* ptr = nullptr) {
        if (m_ptr) delete m_ptr;
        m_ptr = ptr;
    }

    T* release() {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    // Accessors
    T* get() const            { return m_ptr; }
    T* operator->() const     { return m_ptr; }
    T& operator*() const      { return *m_ptr; }
    explicit operator bool() const { return m_ptr != nullptr; }

private:
    T* m_ptr;
};
