#ifndef RESOURCE_HPP_INCLUDED
#define RESOURCE_HPP_INCLUDED

#include <GL/Glew.h>
#include <map>
#include <SFML/graphics.hpp>

#include "log.hpp"
#include "DAT_header.hpp"

#include "memory.hpp"

class C_Resource
{
    public:
        static C_Resource *GetSingleton()
        {
            if (_singleton == NULL)
            {
                _singleton =  new C_Resource;
                C_Log::GetSingleton()->AddMessage("Creating singleton Resource.");
            }

            return _singleton;
        }

        static void kill()
        {
            if (_singleton != NULL)
            {
                GetSingleton()->clear();
                delete _singleton;
                _singleton = NULL;
                C_Log::GetSingleton()->AddMessage("Singleton Resource killed.");
            }
        }

        void clear();
        sf::Image* GetImage(const std::string &);
    private:
        C_Resource();
        ~C_Resource();

        static C_Resource *_singleton;

        C_DAT _data;
        char* _buffer;
        std::map<std::string, sf::Image*> _map;
};


#endif // RESOURCE_HPP_INCLUDED
