#include "cube.hpp"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))

C_Cube::C_Cube()
{
}

C_Cube::~C_Cube()
{
    glDeleteBuffers(1, &_bufVert);
    glDeleteBuffers(1, &_bufNorm);
    glDeleteBuffers(1, &_bufIndex);
    glDeleteBuffers(1, &_bufText);
}

void C_Cube::Create(const int type, const float dimension)
{
    InitDraw(dimension, type);
}

void C_Cube::InitDraw(const float dim, const int coordText)
{
    float pos[72] = { 0.0f, 0.0f, 0.0f  ,  dim, 0.0f, 0.0f  ,  0.0f, dim, 0.0f  ,  dim, dim, 0.0f ,
                        0.0f, 0.0f, dim  ,  dim, 0.0f, dim  ,  0.0f, dim, dim  ,  dim, dim, dim,
                        0.0f, dim, 0.0f  ,  0.0f, 0.0f, dim  ,  0.0f, dim, dim  ,  0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f  ,  dim, 0.0f, 0.0f  ,  0.0f, 0.0f, dim  ,  dim, 0.0f, dim,
                        dim, dim, 0.0f  ,  0.0f, dim, 0.0f  ,  dim, dim, dim  ,  0.0f, dim, dim,
                        dim, dim, dim  ,  dim, 0.0f, dim  ,  dim, dim, 0.0f  ,  dim, 0.0f, 0.0f};

    float norm[72] = {  0.0f, 0.0f, -1.0f   ,  0.0f, 0.0f, -1.0f    ,  0.0f, 0.0f, -1.0f    ,  0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, 1.0f    ,  0.0f, 0.0f, 1.0f     ,  0.0f, 0.0f, 1.0f     ,  0.0f, 0.0f, 1.0f,
                        -1.0f, 0.0f, 0.0f   ,  -1.0f, 0.0f, 0.0f    ,  -1.0f, 0.0f, 0.0f    ,  -1.0f, 0.0f, 0.0f,
                        0.0f, -1.0f, 0.0f   , 0.0f, -1.0f, 0.0f     , 0.0f, -1.0f, 0.0f     ,  0.0f, -1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f    , 0.0f, 1.0f, 0.0f      , 0.0f, 1.0f, 0.0f      ,  0.0f, 1.0f, 0.0f,
                        1.0f, 0.0f, 0.0f    ,  1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f, 0.0f};

    int index[36] = { 4, 5, 6  ,  6, 5, 7,
                    1, 0, 2  ,  1, 2, 3,
                    8, 9, 10  ,  9, 8, 11,
                    12, 13, 14  ,  14, 13, 15,
                    16, 17, 18  ,  18, 17, 19,
                    20, 21, 22  ,  22, 21, 23 };


    float a, b;
    a = coordText % 16;
    a /= 16.0f;
    b = static_cast<int>(coordText / 16);
    b /= 16.0f;
    float const_c = 1.0f / 16.0f;
    float textCoord[48] = { a+const_c, b+const_c    ,  a+const_c, b  ,  a, b+const_c            ,  a, b,
                            a+const_c, b+const_c    ,  a+const_c, b  ,  a, b+const_c            ,  a, b,
                            a+const_c, b            ,  a, b+const_c  ,  a+const_c, b+const_c    ,  a, b,
                            a,      b               ,  a+const_c, b  ,  a, b+const_c            ,  a+const_c, b+const_c,
                            a+const_c, b+const_c    ,  a, b+const_c  ,  a+const_c, b            ,  a, b,
                            a+const_c, b+const_c    ,  a, b+const_c  ,  a+const_c, b            ,  a, b};

    glGenBuffers(1, &_bufVert);
    glGenBuffers(1, &_bufNorm);
    glGenBuffers(1, &_bufIndex);
    glGenBuffers(1, &_bufText);

    glBindBuffer(GL_ARRAY_BUFFER,  _bufVert);
    glBufferData(GL_ARRAY_BUFFER, (72*sizeof *pos), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 72*sizeof *pos, pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER,  _bufNorm);
    glBufferData(GL_ARRAY_BUFFER, (72*sizeof *norm), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 72*sizeof *norm, norm);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (36*sizeof *index), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 36*sizeof *index, index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER,  _bufText);
    glBufferData(GL_ARRAY_BUFFER, (48*sizeof *textCoord), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 48*sizeof *textCoord, textCoord);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void C_Cube::Draw()
{
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
}

void C_Cube::BindBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, _bufVert);
    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, _bufNorm);
    glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(0));
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, _bufText);
    glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufIndex);
}

void C_Cube::UnbindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
