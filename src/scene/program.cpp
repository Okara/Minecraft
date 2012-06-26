#include "program.hpp"
#include "../tools/log.hpp"

C_Program::C_Program()
{
    _program = 0;
    _program = glCreateProgram();
    if(_program == 0)
        C_Log::GetSingleton()->AddMessage("Program GLSL can't be created.");
}

C_Program::~C_Program()
{
    if(_program != 0)
        glDeleteProgram(_program);
}

void C_Program::EnableProgram()
{
    if(_program != 0)
        glUseProgram(_program);
}

void C_Program::DisableProgram()
{
    glUseProgram(0);
}

void C_Program::AddShader(C_Shader & shader)
{
    glAttachShader(_program, shader._shader);
}

const GLuint C_Program::GetProgram() const
{
    return _program;
}

void C_Program::Compile()
{
    GLsizei logsize = 0;
    GLint compile_status = GL_TRUE;
    char *log = NULL;

    glLinkProgram(_program);

    glGetProgramiv(_program, GL_LINK_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logsize);

        log = new char[logsize + 1];
        if(log == NULL)
        {
            C_Log::GetSingleton()->AddMessage( "Program GLSL : Memory can't be allowed!");
            return;
        }

        log[logsize] = '\0';

        glGetProgramInfoLog(_program, logsize, &logsize, log);
        C_Log::GetSingleton()->AddMessage("Program GLSL : Program's compilation failed.");
        C_Log::GetSingleton()->AddMessage( log );

        delete[] log;

        return;
    }
}
