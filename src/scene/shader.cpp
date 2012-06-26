#include "shader.hpp"
#include "../tools/log.hpp"

char* LoadSource(const std::string filename)
{
    char *src = NULL;
    FILE *fp = NULL;
    long size;
    long i;

    fp = fopen(filename.c_str(), "r");

    if(fp == NULL)
    {
        C_Log::GetSingleton()->AddMessage( std::string("Shader : File can't be opened : "+filename) );
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    rewind(fp);

    src = new char[size+1];
    if(src == NULL)
    {
        fclose(fp);
        C_Log::GetSingleton()->AddMessage("Shader : Memory cannot be allowed.");
        return NULL;
    }

    for(i=0; i<size; i++)
        src[i] = fgetc(fp);

    src[size] = '\0';

    fclose(fp);

    return src;
}




C_Shader::C_Shader()
{

}

C_Shader::~C_Shader()
{
    DeleteShader();
}

void C_Shader::DeleteShader()
{
    if(_shader != 0)
    {
        glDeleteShader(_shader);
        _shader = 0;
    }
}

void C_Shader::CreateShader(const std::string str, GLenum type)
{
    _shader = 0;

    GLsizei logsize = 0;
    GLint compile_status = GL_TRUE;
    char *log = NULL;
    char *src = NULL;

    _shader = glCreateShader(type);
    if(_shader == 0)
    {
        C_Log::GetSingleton()->AddMessage("Shader can't be created !");
        return;
    }

    src = LoadSource(str.c_str());
    if(src == NULL)
    {
        C_Log::GetSingleton()->AddMessage("Shader : Source's file is empty.");
        return;
    }

    glShaderSource(_shader, 1, (const GLchar**)&src, NULL);
    glCompileShader(_shader);

    glGetShaderiv(_shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logsize);

        log = new char[logsize + 1];
        if(log == NULL)
        {
            C_Log::GetSingleton()->AddMessage("Shader : Memory can't be allowed!");
            return;
        }

        log[logsize] = '\0';

        glGetShaderInfoLog(_shader, logsize, &logsize, log);
        C_Log::GetSingleton()->AddMessage("Shader's compilation failed ( "+str+" ) : "+log);

        delete[] log;
        delete[] src;

        return;
    }
    delete[] src;
}
