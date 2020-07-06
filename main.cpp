#include "os_context.hpp"

struct context : os_context
{
    context(int argc, char *argv[]):
        os_context(argc, argv)
    {}
};

int
main(int argc, char *argv[])
{
    context ctx(argc, argv);
    return ctx.exec();
}
