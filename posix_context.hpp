#ifndef OS_CONTEXT_POSIX_CONTEXT_HPP
#define OS_CONTEXT_POSIX_CONTEXT_HPP

#include "basic_context.hpp"

#include <boost/asio/signal_set.hpp>


struct posix_context : basic_context
{
    posix_context() :
        watcher(get_executor(), SIGINT, SIGTERM)
    {
        instance = this;
    }

    void
    wait(void)
    {
        register_signal_handler();

        run();
    }

  protected:
    boost::asio::signal_set watcher;

    void
    register_signal_handler(void)
    {
        watcher.async_wait([this](const auto &ec, int signum) {
            if (ec)
            {
                return;
            }

            switch (signum)
            {
            case SIGINT:
                action_required(on_stop);
                action_required(on_stop);
                return;
            case SIGTERM:
                action_required(on_shutdown);
                return;
            }

            register_signal_handler();
        });
    }

  private:
    static posix_context *instance;
};

#endif // OS_CONTEXT_POSIX_CONTEXT_HPP
