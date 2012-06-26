#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <GL/Glew.h>
#include <GL/GL.h>
#include <GL/glu.h>

#include "../tools/mod.hpp"

class C_Light
{
    public:
        C_Light();
        void InitLight(const float,const float,const float);
        void ReplaceLight();
        float _pos[4], _amb[4], _dif[4], _spec[4];

        C_Light *_next;
};

#endif // LIGHT_HPP_INCLUDED
