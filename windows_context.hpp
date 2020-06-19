#ifndef OS_CONTEXT_WINDOWS_CONTEXT_HPP
#define OS_CONTEXT_WINDOWS_CONTEXT_HPP

#include "basic_windows_context.hpp"


struct windows_context : basic_windows_context
{
    windows_context()
    {
        instance = this;
    }

    ~windows_context()
    {
        instance = nullptr;
    }

    void
    run(void)
    {
    }

  private:
    static windows_context *instance;
};

#endif // OS_CONTEXT_WINDOWS_CONTEXT_HPP
