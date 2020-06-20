#ifndef OS_CONTEXT_BASIC_POSIX_CONTEXT_HPP
#define OS_CONTEXT_BASIC_POSIX_CONTEXT_HPP

#include "basic_context.hpp"
#include "system_error.hpp"


struct basic_posix_context : basic_context
{
    basic_posix_context() :
        watcher(get_executor(), SIGINT, SIGTERM)
    {}

    void
    cancel(void)
    {
        canceled = true;
        watcher.cancel();
    }

  protected:
    bool canceled;

    void
    register_handler(void)
    {
        canceled = false;
        watcher.async_wait([this](const auto &ec, int signum) {
            if (ec || canceled)
            {
                return;
            }

            switch (signum)
            {
            case SIGINT:
                try_invoke(on_stop);
                return;

            case SIGTERM:
                try_invoke(on_shutdown);
                return;
            }

            register_handler();
        });
    }

  private:
    boost::asio::signal_set watcher;
};

#endif // OS_CONTEXT_BASIC_POSIX_CONTEXT_HPP
