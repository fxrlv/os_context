#ifndef OS_CONTEXT_POSIX_CONTEXT_HPP
#define OS_CONTEXT_POSIX_CONTEXT_HPP

#include "basic_posix_context.hpp"


struct posix_context : basic_posix_context
{
    posix_context()
    {
        instance = this;
    }

    ~posix_context()
    {
        instance = nullptr;
    }

    void
    run(void)
    {
    }

  private:
    static posix_context *instance;
};

#endif // OS_CONTEXT_POSIX_CONTEXT_HPP
