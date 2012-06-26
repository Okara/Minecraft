#include "skydome.hpp"

C_Skydome::C_Skydome()
{

}

void C_Skydome::Draw()
{
    glDisable(GL_FOG);

    glBegin(GL_TRIANGLES);
        glColor3ub(165, 222, 237);
            glVertex3f( -500.0f, -500.0f, -500.0f);
            glVertex3f( 500.0f, -500.0f, -500.0f);
            glVertex3f( -500.0f, 500.0f, -500.0f);
            glVertex3f( -500.0f, 500.0f, -500.0f );
            glVertex3f( 500.0f, -500.0f, -500.0f );
            glVertex3f( 500.0f, 500.0f, -500.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
    glEnable(GL_FOG);
}
