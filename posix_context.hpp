#ifndef OS_CONTEXT_POSIX_CONTEXT_HPP
#define OS_CONTEXT_POSIX_CONTEXT_HPP

#include "basic_posix_context.hpp"


struct posix_context : basic_posix_context
{
    posix_context()
    {
        instance = this;
    }

    void
    run(void)
    {
        register_handler();
        execute();
    }

  private:
    static posix_context *instance;
};

#endif // OS_CONTEXT_POSIX_CONTEXT_HPP
