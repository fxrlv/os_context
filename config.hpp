#ifndef OS_CONTEXT_CONFIG_HPP
#define OS_CONTEXT_CONFIG_HPP

#include <boost/system/api_config.hpp>

#if !defined(BOOST_POSIX_API) && !defined(BOOST_WINDOWS_API)
#error Only POSIX and Windows are supported!
#endif

#endif // OS_CONTEXT_CONFIG_HPP
