#ifndef OS_CONTEXT_WINDOWS_CONTEXT_HPP
#define OS_CONTEXT_WINDOWS_CONTEXT_HPP

#include "basic_windows_context.hpp"


struct windows_context : basic_windows_context
{
    windows_context()
    {
        instance = this;
    }

    void
    run(void)
    {
        auto ready = attach.get_future();

        std::thread th([this] {
            run_service();
        });

        try
        {
            ready.get();
            serve();
            th.join();
        }
        catch (...)
        {
            th.join();
            throw;
        }
    }

  protected:
    std::promise< void > attach;

    void
    run_service(void) noexcept
    try
    {
        std::basic_string< TCHAR > empty;

        SERVICE_TABLE_ENTRY table[] = {
            {empty.data(), service_main_entry},
            {nullptr, nullptr},
        };

        if (!StartServiceCtrlDispatcher(table))
        {
            throw_last_error("StartServiceCtrlDispatcher()");
        }
    }
    catch (...)
    {
        attach.set_exception(std::current_exception());
    }

    void
    service_main(DWORD, LPTSTR *) noexcept
    try
    {
        std::basic_string< TCHAR > empty;

        handle = RegisterServiceCtrlHandler(empty.data(), service_handler_entry);
        if (!handle)
        {
            throw_last_error("RegisterServiceCtrlHandler()");
        }

        attach.set_value();
    }
    catch (...)
    {
        attach.set_exception(std::current_exception());
    }

  private:
    static windows_context *instance;

    static void
    service_main_entry(DWORD argc, LPTSTR *argv) noexcept
    {
        instance->service_main(argc, argv);
    }

    static void
    service_handler_entry(DWORD ctrl)
    {
        defer(instance->get_executor(), [ctrl] {
            instance->service_handler(ctrl);
        });
    }
};

#endif // OS_CONTEXT_WINDOWS_CONTEXT_HPP
