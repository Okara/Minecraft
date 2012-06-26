#ifndef CHUNK_HPP_INCLUDED
#define CHUNK_HPP_INCLUDED

#define CHUNK_SIZE 16
#define CHUNK_ZVALUE 128

struct
{
    int x, y;
    unsigned char _chunkMap[CHUNK_SIZE][CHUNK_SIZE][CHUNK_ZVALUE];
    bool _hidden;
}typedef MinecraftChunk;

#endif // CHUNK_HPP_INCLUDED
