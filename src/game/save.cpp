#include "game.hpp"

void C_Game::SaveChunk(const int a, const int b)
{
    MinecraftChunk *chunk = GetChunk(a, b);
    if(chunk == NULL)
        return;

    int intA, intB;
    unsigned char uc;

    long pos = 0, size;

    std::fstream file;
    file.open("save.txt", std::fstream::binary | std::ios::in | std::ios::out);

    bool isEmpty = true;
    file.seekp(0, std::ios::end);
    size = file.tellp();
    if( size > 0)
        isEmpty = false;
    file.seekp(0, std::ios::beg);

    if(!isEmpty)
    {
        while(1)
        {
            pos = file.tellp();
            if( (pos + CHUNK_SIZE*CHUNK_SIZE*CHUNK_ZVALUE + 8) == size)
                break;
            file.read(reinterpret_cast<char*>(&intA), sizeof(int));
            file.read(reinterpret_cast<char*>(&intB), sizeof(int));

            if(intA == a && intB == b)
            {
                file.seekp(0, std::ios::cur);
                for(int h=0;h<CHUNK_SIZE;h++)
                {
                    for(int i=0;i<CHUNK_SIZE;i++)
                    {
                        for(int j=0;j<CHUNK_ZVALUE;j++)
                        {
                            uc = chunk->_chunkMap[h][i][j];
                            file.write(reinterpret_cast<const char*>(&uc), sizeof(unsigned char));
                        }
                    }
                }

                file.close();
                return;
            }
            else
                file.seekp( (CHUNK_SIZE*CHUNK_SIZE*CHUNK_ZVALUE), std::ios::cur);
        }
    }

    file.seekp(0, std::ios::end);
    intA = a;
    file.write(reinterpret_cast<const char*>(&intA), sizeof(int));
    intB = b;
    file.write(reinterpret_cast<const char*>(&intB), sizeof(int));

    for(int h=0;h<CHUNK_SIZE;h++)
    {
        for(int i=0;i<CHUNK_SIZE;i++)
        {
            for(int j=0;j<CHUNK_ZVALUE;j++)
            {
                uc = chunk->_chunkMap[h][i][j];
                file.write(reinterpret_cast<const char*>(&uc), sizeof(unsigned char));
            }
        }
    }

    file.close();
}

const bool C_Game::LoadChunk(const int a, const int b)
{
    if(GetChunk(a, b) != NULL)
        return false;

    int intA, intB;

    std::ifstream file;
    file.open("save.txt", std::ifstream::binary | std::ios::in);

    if(!file.is_open())
        return false;

    while( !file.eof())
    {
        file.read(reinterpret_cast<char*>(&intA), sizeof(int));
        file.read(reinterpret_cast<char*>(&intB), sizeof(int));

        if(intA == a && intB == b)
        {
            MinecraftChunk *temp = new MinecraftChunk;
            temp->x = a;
            temp->y = b;
            temp->_hidden = true;
            _chunks.push_back(temp);

            for(int h=0;h<CHUNK_SIZE;h++)
            {
                for(int i=0;i<CHUNK_SIZE;i++)
                {
                    for(int j=0;j<CHUNK_ZVALUE;j++)
                    {
                        file.read(reinterpret_cast<char*>(&_chunks.back()->_chunkMap[h][i][j]), sizeof(unsigned char));

                    }
                }
            }

            file.close();
            return true;
        }
        else
            file.seekg( (CHUNK_SIZE*CHUNK_SIZE*CHUNK_ZVALUE) , std::ios::cur);
    }

    file.close();
    return false;
}
