#ifndef OS_CONTEXT_BASIC_WINDOWS_CONTEXT_HPP
#define OS_CONTEXT_BASIC_WINDOWS_CONTEXT_HPP

#include "basic_context.hpp"
#include "system_error.hpp"


struct basic_windows_context : basic_context
{
    basic_windows_context()
    {
        memset(&status, 0, sizeof(status));
        status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    }

    void
    cancel(void)
    {
        if (stopped())
        {
            return;
        }

        set_status(SERVICE_STOP_PENDING);
    }

  protected:
    SERVICE_STATUS_HANDLE handle;

    void
    serve(void)
    try
    {
        set_status(SERVICE_RUNNING);
        execute();
        set_status(SERVICE_STOPPED);
    }
    catch (...)
    {
        set_status(SERVICE_STOPPED);
        throw;
    }

    void
    service_handler(DWORD ctrl)
    {
        if (stopped())
        {
            return;
        }

        switch (ctrl)
        {
        case SERVICE_CONTROL_STOP:
            set_status(SERVICE_STOP_PENDING);
            try_invoke(on_stop);
            return;

        case SERVICE_CONTROL_SHUTDOWN:
            set_status(SERVICE_STOP_PENDING);
            try_invoke(on_shutdown);
            return;
        }
    }

  private:
    SERVICE_STATUS status;

    bool
    stopped(void) noexcept
    {
        return status.dwCurrentState != SERVICE_RUNNING;
    }

    void
    on_work_started(void) noexcept
    {
        if (status.dwControlsAccepted == 0)
        {
            status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
            get_executor().on_work_started();
        }
    }

    void
    on_work_finished(void) noexcept
    {
        if (status.dwControlsAccepted != 0)
        {
            status.dwControlsAccepted = 0;
            get_executor().on_work_finished();
        }
    }

    void
    set_status(DWORD state) noexcept
    {
        switch (state)
        {
        case SERVICE_RUNNING:
            on_work_started();
            break;

        default:
            on_work_finished();
            break;
        }

        status.dwCurrentState = state;
        if (!SetServiceStatus(handle, &status))
        {
            throw_last_error("SetServiceStatus()");
        }
    }
};

#endif // OS_CONTEXT_BASIC_WINDOWS_CONTEXT_HPP
