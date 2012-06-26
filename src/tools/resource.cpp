#include "resource.hpp"

C_Resource::C_Resource()
{
    _data.Read("Data/data.dat");

    clear();

    _map["notfound"] = GetImage("data/notexture.bmp");
}

C_Resource::~C_Resource()
{
    clear();
}

void C_Resource::clear()
{
    std::map<std::string, sf::Image*>::iterator it;
    for(it = _map.begin(); it != _map.end() ; it++)
        delete it->second;
    _map.clear();

    C_Log::GetSingleton()->AddMessage("All resources have been cleared.");
}

sf::Image* C_Resource::GetImage(const std::string & s)
{
    if(_map.count(s))
        return _map[s];
    else
    {
        _buffer = _data.GetFile(s);
        if(_buffer == NULL)
        {
            C_Log::GetSingleton()->AddMessage("File \""+s+"\" not found !");
            return NULL;
        }
        else
            C_Log::GetSingleton()->AddMessage("Texture loaded: "+s+".");

        _map[s] = new sf::Image();
        _map[s]->LoadFromMemory(_buffer, _data.GetFileSize(s));
        _map[s]->SetSmooth(false);
        _map[s]->CreateMaskFromColor(sf::Color::Green);

        return _map[s];
    }

    return NULL;
}
