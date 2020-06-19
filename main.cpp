#include "os_context.hpp"

#include <iostream>
#include <thread>


int
main(void)
{
    os_context ctx;

    ctx.on_stop = [] {
        std::cout << std::this_thread::get_id() << ": stop" << std::endl;
    };

    ctx.on_shutdown = [] {
        std::cout << std::this_thread::get_id() << ": shutdown" << std::endl;
    };

    try
    {
        ctx.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
