Inspired by Boost.Application

# Example

```cpp
#include "os_context.hpp"

int
main(void)
{
    os_context ctx;

    ctx.on_stop = [] {
        /**
         * SIGINT               on POSIX
         * SERVICE_CONTROL_STOP on Windows
         */
    };

    ctx.on_shutdown = [] {
        /**
         * SIGTERM                  on POSIX
         * SERVICE_CONTROL_SHUTDOWN on Windows
         */
    };

    ctx.run();
    return 0;
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
