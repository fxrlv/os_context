#ifndef OS_CONTEXT_SYSTEM_ERROR_HPP
#define OS_CONTEXT_SYSTEM_ERROR_HPP

#include "config.hpp"

#include <system_error>
#if defined(BOOST_POSIX_API)
#include <errno.h>
#elif defined(BOOST_WINDOWS_API)
#include <windows.h>
#endif


inline std::error_code
get_last_error(void) noexcept
{
#if defined(BOOST_POSIX_API)
    return std::error_code(errno, std::system_category());
#elif defined(BOOST_WINDOWS_API)
    return std::error_code(GetLastError(), std::system_category());
#endif
}

inline void
throw_last_error(const char *msg)
{
    throw std::system_error(get_last_error(), msg);
}

#endif // OS_CONTEXT_SYSTEM_ERROR_HPP
