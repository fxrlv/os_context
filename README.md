Inspired by Boost.Application

# Example

```cpp
#include "os_context.hpp"

struct context : os_context
{
    void
    stop(void)
    {
        /**
         * SIGINT               on POSIX
         * SERVICE_CONTROL_STOP on Windows
         */
    }

    void
    shutdown(void)
    {
        /**
         * SIGTERM                  on POSIX
         * SERVICE_CONTROL_SHUTDOWN on Windows
         */
    }
};

int
main(int argc, char *argv[])
{
    context ctx(argc, argv);
    return ctx.exec();
}
```

Install & Run service:

```powershell
New-Service -Name <name> -BinaryPathName <executable>
Start-Service -Name <name>
```

Invoke `on_stop`:

```powershell
Stop-Service -Name <name>
```

Invoke `on_shutdown`:

```powershell
Stop-Computer
```
