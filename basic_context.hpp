#ifndef OS_CONTEXT_BASIC_CONTEXT_HPP
#define OS_CONTEXT_BASIC_CONTEXT_HPP

#include <boost/asio/defer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>

#include <future>


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

  protected:
    void
    execute(void)
    {
        ioc.run();
    }

    static void
    try_invoke(const handler_type &fn)
    {
        if (fn)
        {
            fn();
        }
    }

  private:
    boost::asio::io_context ioc;
};

#endif // OS_CONTEXT_BASIC_CONTEXT_HPP
