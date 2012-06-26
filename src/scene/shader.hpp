#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

#define GLEW_STATIC
#include <GL/Glew.h>


class C_Shader
{
    public:
        C_Shader();
        ~C_Shader();
        void CreateShader(const std::string, GLenum);
        void DeleteShader();

        GLuint _shader;
};

#endif // SHADER_HPP_INCLUDED
