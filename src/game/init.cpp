#include "game.hpp"

void C_Game::InitTexture()
{
    sf::Image *i_texture = C_Resource::GetSingleton()->GetImage("data/texture/terrain.png");
    if(i_texture == NULL)
    {
        C_Log::GetSingleton()->AddMessage( "Loading default texture.");
        i_texture = C_Resource::GetSingleton()->GetImage("data/texture/notexture.bmp");
    }
    i_texture->SetSmooth(false);

    _texture = 0;
    glGenTextures (1, &_texture);
    glBindTexture (GL_TEXTURE_2D, _texture);
    gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGBA, i_texture->GetWidth(), i_texture->GetHeight(),
                              GL_RGBA, GL_UNSIGNED_BYTE, i_texture->GetPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void C_Game::InitCubes()
{
    _cube = new C_Cube[NB_TYPE_CUBE];
    _cube[0].Create(0, 1.002f);
    for(int i=1;i<NB_TYPE_CUBE;i++)
        _cube[i].Create(i);

    _bSelectedCube = false;

    for(int i=0;i<10;i++)
        _cubeBreakAnim[i].Create(CUBE_BREAK_ANIM0+i, 1.001f);
    _frameBreakAnim = CUBE_BREAK_ANIM0;
    _boolBreakAnim = false;

    /// INIT MAP

    for(int i=-(_fogStart/CHUNK_SIZE);i< (_fogStart/CHUNK_SIZE)+1;i++)
    {
        for(int j=-(_fogStart/CHUNK_SIZE);j < (_fogStart/CHUNK_SIZE)+1;j++)
        {
            if( !LoadChunk(i, j))
                CreateRandomChunk(i, j);
            CheckChunksCubesVisibility(i, j);
        }
    }

    _actuelCubeInHand = CUBE_AIR;
    _actualChunkX = 0;
    _actualChunkY = 0;
}

void C_Game::InitGUI()
{
    _sprHotkeys.SetImage( *C_Resource::GetSingleton()->GetImage("data/gui/hotkeys.png"));
    _sprHotkeys.SetPosition( (_screen->GetWidth()-_sprHotkeys.GetImage()->GetWidth()) / 2, (_screen->GetHeight() - _sprHotkeys.GetImage()->GetHeight()));
    _sprSelectedHotkeys.SetImage( *C_Resource::GetSingleton()->GetImage("data/gui/select.png"));
    _sprSelectedHotkeys.SetPosition( _sprHotkeys.GetPosition().x-1, _sprHotkeys.GetPosition().y);
    _actualHotkeys = 0;

    for(int i=0;i<9;i++)
    {
        _itemInHotkeys[i] = 0;
        _sprItemInHotkeys[i].SetPosition( (_sprHotkeys.GetPosition().x + 3 + 20*i), _sprHotkeys.GetPosition().y+3);
    }
}
