#include "game.hpp"

void C_Game::InitFog()
{
    _fogStart = 64;

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, 0.25f);
    float params[4] = {165.0f/256.0f, 222.0f/256.0f, 237.0f/256.0f, 1.0f};
    glFogfv(GL_FOG_COLOR, params);
    glFogf(GL_FOG_START, _fogStart/4);
    glFogf(GL_FOG_END, _fogStart);
}
