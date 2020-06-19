#ifndef OS_CONTEXT_BASIC_CONTEXT_HPP
#define OS_CONTEXT_BASIC_CONTEXT_HPP

#include <boost/asio/io_context.hpp>


struct basic_context
{
    using handler_type = std::function< void() >;

    auto
    get_executor(void) noexcept
    {
        return ioc.get_executor();
    }

    handler_type on_stop;
    handler_type on_shutdown;

  private:
    boost::asio::io_context ioc;
};

#endif // OS_CONTEXT_BASIC_CONTEXT_HPP
