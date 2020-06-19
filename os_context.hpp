#ifndef OS_CONTEXT_OS_CONTEXT_HPP
#define OS_CONTEXT_OS_CONTEXT_HPP

#include "config.hpp"

#if defined(BOOST_POSIX_API)
#include "posix_context.hpp"
#elif defined(BOOST_WINDOWS_API)
#include "windows_context.hpp"
#endif

#if defined(BOOST_POSIX_API)
using os_context = posix_context;
#elif defined(BOOST_WINDOWS_API)
using os_context = windows_context;
#endif

#endif // OS_CONTEXT_OS_CONTEXT_HPP
