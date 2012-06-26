#include "tools/render.hpp"
#include "tools/memory.hpp"

C_Log *C_Log::_singleton = NULL;
C_Resource *C_Resource::_singleton = NULL;
C_Memory *C_Memory::_singleton = NULL;

int main(void)
{
    C_Render _render;

    C_Resource::GetSingleton()->kill();
    C_Memory::GetSingleton()->kill();
    C_Log::GetSingleton()->kill();

    return 0;
}
