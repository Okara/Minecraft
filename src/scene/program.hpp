#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "shader.hpp"

class C_Program
{
    public:
        C_Program();
        ~C_Program();

        void AddShader(C_Shader &);
        void EnableProgram();
        void DisableProgram();
        void Compile();
        const GLuint GetProgram() const;
    protected:
        GLuint _program;
};

#endif // PROGRAM_HPP_INCLUDED
