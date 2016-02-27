
/*
 * shared_mutext.hpp
 *
 *  Created on: Feb 26, 2016
 *      Author: nick
 */



// -*- C++ -*-
//===------------------------ shared_mutex --------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SHARED_MUTEX
#define _LIBCPP_SHARED_MUTEX

/*
    shared_mutex synopsis

// C++1y

namespace std
{

class shared_mutex      // C++17
{
public:
    shared_mutex();
    ~shared_mutex();

    shared_mutex(const shared_mutex&) = delete;
    shared_mutex& operator=(const shared_mutex&) = delete;

    // Exclusive ownership
    void lock(); // blocking
    bool try_lock();
    void unlock();

    // Shared ownership
    void lock_shared(); // blocking
    bool try_lock_shared();
    void unlock_shared();

    typedef implementation-defined native_handle_type; // See 30.2.3
    native_handle_type native_handle(); // See 30.2.3
};

class shared_timed_mutex
{
public:
    shared_timed_mutex();
    ~shared_timed_mutex();

    shared_timed_mutex(const shared_timed_mutex&) = delete;
    shared_timed_mutex& operator=(const shared_timed_mutex&) = delete;

    // Exclusive ownership
    void lock(); // blocking
    bool try_lock();
    template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
    template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
    void unlock();

    // Shared ownership
    void lock_shared(); // blocking
    bool try_lock_shared();
    template <class Rep, class Period>
        bool
        try_lock_shared_for(const chrono::duration<Rep, Period>& rel_time);
    template <class Clock, class Duration>
        bool
        try_lock_shared_until(const chrono::time_point<Clock, Duration>& abs_time);
    void unlock_shared();
};

template <class Mutex>
class shared_lock
{
public:
    typedef Mutex mutex_type;

    // Shared locking
    shared_lock() noexcept;
    explicit shared_lock(mutex_type& m); // blocking
    shared_lock(mutex_type& m, defer_lock_t) noexcept;
    shared_lock(mutex_type& m, try_to_lock_t);
    shared_lock(mutex_type& m, adopt_lock_t);
    template <class Clock, class Duration>
        shared_lock(mutex_type& m,
                    const chrono::time_point<Clock, Duration>& abs_time);
    template <class Rep, class Period>
        shared_lock(mutex_type& m,
                    const chrono::duration<Rep, Period>& rel_time);
    ~shared_lock();

    shared_lock(shared_lock const&) = delete;
    shared_lock& operator=(shared_lock const&) = delete;

    shared_lock(shared_lock&& u) noexcept;
    shared_lock& operator=(shared_lock&& u) noexcept;

    void lock(); // blocking
    bool try_lock();
    template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
    template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
    void unlock();

    // Setters
    void swap(shared_lock& u) noexcept;
    mutex_type* release() noexcept;

    // Getters
    bool owns_lock() const noexcept;
    explicit operator bool () const noexcept;
    mutex_type* mutex() const noexcept;
};

template <class Mutex>
    void swap(shared_lock<Mutex>& x, shared_lock<Mutex>& y) noexcept;

}  // std

*/

#define _LIBCPP_BUILDING_SHARED_MUTEX

#include "__config.hpp"

#if _LIBCPP_STD_VER > 11 || defined(_LIBCPP_BUILDING_SHARED_MUTEX)

#include "__mutex_base.hpp"

#include "__undef_min_max.hpp"

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

#ifdef _LIBCPP_HAS_NO_THREADS
#error <shared_mutex> is not supported on this single threaded system
#else // !_LIBCPP_HAS_NO_THREADS

_LIBCPP_BEGIN_NAMESPACE_STD

struct _LIBCPP_TYPE_VIS __shared_mutex_base
{
    mutex               __mut_;
    condition_variable  __gate1_;
    condition_variable  __gate2_;
    unsigned            __state_;

    static const unsigned __write_entered_ = 1U << (sizeof(unsigned)*__CHAR_BIT__ - 1);
    static const unsigned __n_readers_ = ~__write_entered_;

    __shared_mutex_base();
    _LIBCPP_INLINE_VISIBILITY ~__shared_mutex_base() = default;

    __shared_mutex_base(const __shared_mutex_base&) = delete;
    __shared_mutex_base& operator=(const __shared_mutex_base&) = delete;

    // Exclusive ownership
    void lock(); // blocking
    bool try_lock();
    void unlock();

    // Shared ownership
    void lock_shared(); // blocking
    bool try_lock_shared();
    void unlock_shared();

//     typedef implementation-defined native_handle_type; // See 30.2.3
//     native_handle_type native_handle(); // See 30.2.3
};


#if _LIBCPP_STD_VER > 14
class _LIBCPP_TYPE_VIS shared_mutex
{
	__shared_mutex_base __base;
public:
    shared_mutex() : __base() {}
    _LIBCPP_INLINE_VISIBILITY ~shared_mutex() = default;

    shared_mutex(const shared_mutex&) = delete;
    shared_mutex& operator=(const shared_mutex&) = delete;

    // Exclusive ownership
    _LIBCPP_INLINE_VISIBILITY void lock()     { return __base.lock(); }
    _LIBCPP_INLINE_VISIBILITY bool try_lock() { return __base.try_lock(); }
    _LIBCPP_INLINE_VISIBILITY void unlock()   { return __base.unlock(); }

    // Shared ownership
    _LIBCPP_INLINE_VISIBILITY void lock_shared()     { return __base.lock_shared(); }
    _LIBCPP_INLINE_VISIBILITY bool try_lock_shared() { return __base.try_lock_shared(); }
    _LIBCPP_INLINE_VISIBILITY void unlock_shared()   { return __base.unlock_shared(); }

//     typedef __shared_mutex_base::native_handle_type native_handle_type;
//     _LIBCPP_INLINE_VISIBILITY native_handle_type native_handle() { return __base::unlock_shared(); }
};
#endif


class _LIBCPP_TYPE_VIS shared_timed_mutex
{
	__shared_mutex_base __base;
public:
    shared_timed_mutex();
    _LIBCPP_INLINE_VISIBILITY ~shared_timed_mutex() = default;

    shared_timed_mutex(const shared_timed_mutex&) = delete;
    shared_timed_mutex& operator=(const shared_timed_mutex&) = delete;

    // Exclusive ownership
    void lock();
    bool try_lock();
    template <class _Rep, class _Period>
        _LIBCPP_INLINE_VISIBILITY
        bool
        try_lock_for(const chrono::duration<_Rep, _Period>& __rel_time)
        {
            return try_lock_until(chrono::steady_clock::now() + __rel_time);
        }
    template <class _Clock, class _Duration>
        bool
        try_lock_until(const chrono::time_point<_Clock, _Duration>& __abs_time);
    void unlock();

    // Shared ownership
    void lock_shared();
    bool try_lock_shared();
    template <class _Rep, class _Period>
        _LIBCPP_INLINE_VISIBILITY
        bool
        try_lock_shared_for(const chrono::duration<_Rep, _Period>& __rel_time)
        {
            return try_lock_shared_until(chrono::steady_clock::now() + __rel_time);
        }
    template <class _Clock, class _Duration>
        bool
        try_lock_shared_until(const chrono::time_point<_Clock, _Duration>& __abs_time);
    void unlock_shared();
};

template <class _Clock, class _Duration>
bool
shared_timed_mutex::try_lock_until(
                        const chrono::time_point<_Clock, _Duration>& __abs_time)
{
    unique_lock<mutex> __lk(__base.__mut_);
    if (__base.__state_ & __base.__write_entered_)
    {
        while (true)
        {
            cv_status __status = __base.__gate1_.wait_until(__lk, __abs_time);
            if ((__base.__state_ & __base.__write_entered_) == 0)
                break;
            if (__status == cv_status::timeout)
                return false;
        }
    }
    __base.__state_ |= __base.__write_entered_;
    if (__base.__state_ & __base.__n_readers_)
    {
        while (true)
        {
            cv_status __status = __base.__gate2_.wait_until(__lk, __abs_time);
            if ((__base.__state_ & __base.__n_readers_) == 0)
                break;
            if (__status == cv_status::timeout)
            {
                __base.__state_ &= ~__base.__write_entered_;
                __base.__gate1_.notify_all();
                return false;
            }
        }
    }
    return true;
}

template <class _Clock, class _Duration>
bool
shared_timed_mutex::try_lock_shared_until(
                        const chrono::time_point<_Clock, _Duration>& __abs_time)
{
    unique_lock<mutex> __lk(__base.__mut_);
    if ((__base.__state_ & __base.__write_entered_) || (__base.__state_ & __base.__n_readers_) == __base.__n_readers_)
    {
        while (true)
        {
            cv_status status = __base.__gate1_.wait_until(__lk, __abs_time);
            if ((__base.__state_ & __base.__write_entered_) == 0 &&
                                       (__base.__state_ & __base.__n_readers_) < __base.__n_readers_)
                break;
            if (status == cv_status::timeout)
                return false;
        }
    }
    unsigned __num_readers = (__base.__state_ & __base.__n_readers_) + 1;
    __base.__state_ &= ~__base.__n_readers_;
    __base.__state_ |= __num_readers;
    return true;
}

template <class _Mutex>
class shared_lock
{
public:
    typedef _Mutex mutex_type;

private:
    mutex_type* __m_;
    bool __owns_;

public:
    _LIBCPP_INLINE_VISIBILITY
    shared_lock() _NOEXCEPT
        : __m_(nullptr),
          __owns_(false)
        {}

    _LIBCPP_INLINE_VISIBILITY
    explicit shared_lock(mutex_type& __m)
        : __m_(&__m),
          __owns_(true)
        {__m_->lock_shared();}

    _LIBCPP_INLINE_VISIBILITY
    shared_lock(mutex_type& __m, defer_lock_t) _NOEXCEPT
        : __m_(&__m),
          __owns_(false)
        {}

    _LIBCPP_INLINE_VISIBILITY
    shared_lock(mutex_type& __m, try_to_lock_t)
        : __m_(&__m),
          __owns_(__m.try_lock_shared())
        {}

    _LIBCPP_INLINE_VISIBILITY
    shared_lock(mutex_type& __m, adopt_lock_t)
        : __m_(&__m),
          __owns_(true)
        {}

    template <class _Clock, class _Duration>
        _LIBCPP_INLINE_VISIBILITY
        shared_lock(mutex_type& __m,
                    const chrono::time_point<_Clock, _Duration>& __abs_time)
            : __m_(&__m),
              __owns_(__m.try_lock_shared_until(__abs_time))
            {}

    template <class _Rep, class _Period>
        _LIBCPP_INLINE_VISIBILITY
        shared_lock(mutex_type& __m,
                    const chrono::duration<_Rep, _Period>& __rel_time)
            : __m_(&__m),
              __owns_(__m.try_lock_shared_for(__rel_time))
            {}

    _LIBCPP_INLINE_VISIBILITY
    ~shared_lock()
    {
        if (__owns_)
            __m_->unlock_shared();
    }

    shared_lock(shared_lock const&) = delete;
    shared_lock& operator=(shared_lock const&) = delete;

    _LIBCPP_INLINE_VISIBILITY
    shared_lock(shared_lock&& __u) _NOEXCEPT
        : __m_(__u.__m_),
          __owns_(__u.__owns_)
        {
            __u.__m_ = nullptr;
            __u.__owns_ = false;
        }

    _LIBCPP_INLINE_VISIBILITY
    shared_lock& operator=(shared_lock&& __u) _NOEXCEPT
    {
        if (__owns_)
            __m_->unlock_shared();
        __m_ = nullptr;
        __owns_ = false;
        __m_ = __u.__m_;
        __owns_ = __u.__owns_;
        __u.__m_ = nullptr;
        __u.__owns_ = false;
        return *this;
    }

    void lock();
    bool try_lock();
    template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
    template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
    void unlock();

    // Setters
    _LIBCPP_INLINE_VISIBILITY
    void swap(shared_lock& __u) _NOEXCEPT
    {
        _VSTD::swap(__m_, __u.__m_);
        _VSTD::swap(__owns_, __u.__owns_);
    }

    _LIBCPP_INLINE_VISIBILITY
    mutex_type* release() _NOEXCEPT
    {
        mutex_type* __m = __m_;
        __m_ = nullptr;
        __owns_ = false;
        return __m;
    }

    // Getters
    _LIBCPP_INLINE_VISIBILITY
    bool owns_lock() const _NOEXCEPT {return __owns_;}

    _LIBCPP_INLINE_VISIBILITY
    explicit operator bool () const _NOEXCEPT {return __owns_;}

    _LIBCPP_INLINE_VISIBILITY
    mutex_type* mutex() const _NOEXCEPT {return __m_;}
};

template <class _Mutex>
void
shared_lock<_Mutex>::lock()
{
    if (__m_ == nullptr)
        __throw_system_error(EPERM, "shared_lock::lock: references null mutex");
    if (__owns_)
        __throw_system_error(EDEADLK, "shared_lock::lock: already locked");
    __m_->lock_shared();
    __owns_ = true;
}

template <class _Mutex>
bool
shared_lock<_Mutex>::try_lock()
{
    if (__m_ == nullptr)
        __throw_system_error(EPERM, "shared_lock::try_lock: references null mutex");
    if (__owns_)
        __throw_system_error(EDEADLK, "shared_lock::try_lock: already locked");
    __owns_ = __m_->try_lock_shared();
    return __owns_;
}

template <class _Mutex>
template <class _Rep, class _Period>
bool
shared_lock<_Mutex>::try_lock_for(const chrono::duration<_Rep, _Period>& __d)
{
    if (__m_ == nullptr)
        __throw_system_error(EPERM, "shared_lock::try_lock_for: references null mutex");
    if (__owns_)
        __throw_system_error(EDEADLK, "shared_lock::try_lock_for: already locked");
    __owns_ = __m_->try_lock_shared_for(__d);
    return __owns_;
}

template <class _Mutex>
template <class _Clock, class _Duration>
bool
shared_lock<_Mutex>::try_lock_until(const chrono::time_point<_Clock, _Duration>& __t)
{
    if (__m_ == nullptr)
        __throw_system_error(EPERM, "shared_lock::try_lock_until: references null mutex");
    if (__owns_)
        __throw_system_error(EDEADLK, "shared_lock::try_lock_until: already locked");
    __owns_ = __m_->try_lock_shared_until(__t);
    return __owns_;
}

template <class _Mutex>
void
shared_lock<_Mutex>::unlock()
{
    if (!__owns_)
        __throw_system_error(EPERM, "shared_lock::unlock: not locked");
    __m_->unlock_shared();
    __owns_ = false;
}

template <class _Mutex>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(shared_lock<_Mutex>& __x, shared_lock<_Mutex>& __y) _NOEXCEPT
    {__x.swap(__y);}

_LIBCPP_END_NAMESPACE_STD

#endif  // !_LIBCPP_HAS_NO_THREADS

#endif  // _LIBCPP_STD_VER > 11

#endif  // _LIBCPP_SHARED_MUTEX



