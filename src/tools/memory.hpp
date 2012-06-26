#ifndef MEMORY_HPP_INCLUDED
#define MEMORY_HPP_INCLUDED

#include "mod.hpp"
#include "log.hpp"

class C_Memory
{
    public:
        static C_Memory *GetSingleton()
        {
            if (_singleton == NULL)
            {
                _singleton =  new C_Memory;

                C_Log::GetSingleton()->AddMessage("Creating singleton Memory.");
            }

            return _singleton;
        }

        static void kill()
        {
            if (_singleton != NULL)
            {
                C_Log::GetSingleton()->AddMessage("Memory leak : "+FloatToString(C_Memory::GetSingleton()->_memoryLeak) +".");

                C_Log::GetSingleton()->AddMessage("Singleton Memory killed.");
                delete _singleton;
                _singleton = NULL;
            }
        }

        void* MemoryAlloc(int c_size, int nbEntity = 0)
        {
            void* ptr;

            if(nbEntity == 0)
            {
                ptr = malloc(c_size);
                C_Memory::GetSingleton()->_memoryLeak += sizeof ptr;
            }
            else
            {
                ptr = malloc(c_size * nbEntity);
                C_Memory::GetSingleton()->_memoryLeak += sizeof ptr;
            }

            //C_Log::GetSingleton()->AddMessage("MemoryMalloc of "+FloatToString(static_cast<int>(sizeof(ptr)))+" bytes");
            return ptr;
        }

        void MemoryFree(void* ptr)
        {
            //C_Log::GetSingleton()->AddMessage("MemoryFree of "+FloatToString(static_cast<int>(sizeof(ptr)))+" bytes");

            C_Memory::GetSingleton()->_memoryLeak -= sizeof ptr;

            free(ptr);
        }

    private:
        C_Memory()
        {
            _memoryLeak = 0;
        }

        ~C_Memory()
        {
        }

        long _memoryLeak;

        static C_Memory *_singleton;
};


#endif // MEMORY_HPP_INCLUDED
