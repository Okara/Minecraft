#include "render.hpp"

C_Render::C_Render()
{
    C_Log::GetSingleton()->AddMessage("Create RenderWindow");
    Create(sf::VideoMode(900, 670, 32), "Minecraft");
    C_Log::GetSingleton()->AddMessage("RenderWindow created");

    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f, GetWidth()/GetHeight(), 0.001f, 50000.f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
	glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LESS);
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CCW );

    _game = new C_Game(this);
    _game->loop();
    delete _game;
}

C_Render::~C_Render()
{
}
