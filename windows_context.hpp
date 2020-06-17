#ifndef OS_CONTEXT_WINDOWS_CONTEXT_HPP
#define OS_CONTEXT_WINDOWS_CONTEXT_HPP

#include "basic_context.hpp"


struct windows_context : basic_context
{
    windows_context()
    {
        instance = this;
    }

    void
    wait(void)
    {
    }

  protected:
    SERVICE_STATUS        status;
    SERVICE_STATUS_HANDLE status_handle;

    void
    service_main(DWORD, LPTSTR *)
    {
    }

    void
    service_handler(DWORD ctrl)
    {
    }

  private:
    static windows_context *instance;

    static void
    service_main_entry(DWORD argc, LPTSTR *argv)
    {
        instance->service_main(argc, argv);
    }

    static void
    service_handler_entry(DWORD ctrl)
    {
        instance->service_handler(ctrl);
    }
};

#endif // OS_CONTEXT_WINDOWS_CONTEXT_HPP
