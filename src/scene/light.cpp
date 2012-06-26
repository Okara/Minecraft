#include <sstream>

#include "light.hpp"


C_Light::C_Light()
{
    _next = NULL;
}

void C_Light::InitLight(const float a, const float b, const float c)
{
    _pos[0] = a;
    _pos[1] = b;
    _pos[2] = c;
    _pos[3] = 1.0f;

    _amb[0] = 1.0f;
    _amb[1] = 1.0f;
    _amb[2] = 1.0f;
    _amb[3] = 1.0f;

    _dif[0] = 1.0f;
    _dif[1] = 1.0f;
    _dif[2] = 1.0f;
    _dif[3] = 1.0f;

    _spec[0] = 1.0f;
    _spec[1] = 1.0f;
    _spec[2] = 1.0f;
    _spec[3] = 1.0f;

    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, _pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, _amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _spec);

    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0f );
	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION,  0.0f );
	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f );

	/*glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 15);
	float Light1Dir[3] = {0.0f, 0.0f, -1.0f};
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, 20);*/


	C_Log::GetSingleton()->AddMessage( std::string("Light created : pos("+FloatToString(_pos[0])+", "+FloatToString(_pos[1])+", "+FloatToString(_pos[2])+")."));
}

void C_Light::ReplaceLight()
{
    glLightfv(GL_LIGHT0, GL_POSITION, _pos);
}
