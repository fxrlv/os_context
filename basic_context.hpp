#ifndef OS_CONTEXT_BASIC_CONTEXT_HPP
#define OS_CONTEXT_BASIC_CONTEXT_HPP

#include <boost/asio/defer.hpp>
#include <boost/asio/io_service.hpp>


struct basic_context
{
    using handler_type  = std::function< void() >;
    using executor_type = boost::asio::io_context::executor_type;

    executor_type
    get_executor(void)
    {
        return ioc.get_executor();
    }

    handler_type on_stop;
    handler_type on_shutdown;

  protected:
    void
    run(void)
    {
        ioc.run();
    }

    void
    action_required(handler_type &handler)
    {
        defer(ioc, [&handler] {
            if (handler)
            {
                handler_type fn;
                fn.swap(handler);
                fn();
            }
        });
    }

  private:
    boost::asio::io_context ioc;
};

#endif // OS_CONTEXT_BASIC_CONTEXT_HPP
