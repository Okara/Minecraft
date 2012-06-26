#ifndef OKARA_RENDER_HPP_INCLUDED
#define OKARA_RENDER_HPP_INCLUDED

#include "../game/game.hpp"
#include "resource.hpp"
#include "memory.hpp"

class C_Render : public sf::RenderWindow
{
    public:
        C_Render();
        ~C_Render();
    protected:

        C_Game *_game;
};

#endif // RENDER_HPP_INCLUDED
