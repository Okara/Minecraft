#ifndef MINECUBE_HPP_INCLUDED
#define MINECUBE_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

#define GLEW_STATIC
#include <GL/Glew.h>

#include "..\tools\resource.hpp"

#include "..\scene\light.hpp"

enum {CUBE_AIR = 0, CUBE_DIRT = 1, CUBE_SAND = 2, CUBE_STONE = 3, CUBE_COAL = 4, CUBE_IRON = 5, CUBE_GOLD = 6,
        CUBE_REDSTONE = 7, CUBE_DIAMOND = 8, CUBE_GRAVEL = 9,

        CUBE_BREAK_ANIM0 = 240, CUBE_BREAK_ANIM1 = 241, CUBE_BREAK_ANIM2 = 242, CUBE_BREAK_ANIM3 = 243, CUBE_BREAK_ANIM4 = 244,
        CUBE_BREAK_ANIM5 = 245, CUBE_BREAK_ANIM6 = 246, CUBE_BREAK_ANIM7 = 247, CUBE_BREAK_ANIM8 = 248, CUBE_BREAK_ANIM9 = 249 };
#define NB_TYPE_CUBE 10

struct
{
    int x, y, z;
    float _dist;
}typedef tabCube;


class C_Cube
{
    public:
        C_Cube();
        ~C_Cube();

        void Create(const int, const float dimension = 1.0);
        void Draw();

        void BindBuffer();
        void UnbindBuffer();

    protected:
        void InitDraw(const float, const int);

        //GLuint _id;

        GLuint _bufVert, _bufNorm, _bufIndex, _bufText;
};


#endif // MINECUBE_HPP_INCLUDED
