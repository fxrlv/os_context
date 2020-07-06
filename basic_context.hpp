#ifndef OS_CONTEXT_BASIC_CONTEXT_HPP
#define OS_CONTEXT_BASIC_CONTEXT_HPP

#include <boost/asio/io_context.hpp>


struct basic_context
{
  private:
    boost::asio::io_context ioc;
};

#endif // OS_CONTEXT_BASIC_CONTEXT_HPP
