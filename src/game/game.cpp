#include "game.hpp"

C_Game::C_Game(sf::RenderWindow* sc)
    : C_Mod(sc)
{
    sf::Clock loadTimer;

    glewInit();

    InitFog();
    InitTexture();

    _cam->setPosition(Vector3D(CHUNK_SIZE/2, CHUNK_SIZE/2, CHUNK_ZVALUE/2 +1.6f));
    _cam->setSpeed(0.0006);
    _screen->ShowMouseCursor(false);

    glEnable(GL_TEXTURE_2D);
    InitCubes();

    _boolJumping = false;
    _frameJumping = 0;

    InitGUI();
    SetItemInHotkeys(CUBE_DIRT, 0);
    SetItemInHotkeys(CUBE_SAND, 1);
    SetItemInHotkeys(CUBE_SAND+1, 2);
    SetItemInHotkeys(CUBE_SAND+2, 3);
    SetItemInHotkeys(CUBE_SAND+3, 4);
    SetItemInHotkeys(CUBE_SAND+4, 5);
    SetItemInHotkeys(CUBE_SAND+5, 6);
    SetItemInHotkeys(CUBE_SAND+6, 7);
    SetItemInHotkeys(CUBE_SAND+7, 8);

    _actuelCubeInHand = _itemInHotkeys[0];

    C_Log::GetSingleton()->AddMessage( std::string("Scene loaded in " + FloatToString(loadTimer.GetElapsedTime()) + "sec.") );

    /*C_LineEdit *widg = new C_LineEdit();
    widg->move(10, sc->GetHeight()-40);
    widg->resize(350, 30);
    AddWidget(widg);*/

    Launch();
}

C_Game::~C_Game()
{
    _screen->ShowMouseCursor(true);

    Wait(); //Waiting for thread to end

    for(unsigned int i=0;i<_chunks.size();i++)
        SaveChunk(_chunks[i]->x, _chunks[i]->y);

    glDeleteTextures(1, &_texture);

    delete[] _cube;

    for(unsigned int i=0;i<_chunks.size();i++)
        delete _chunks[i];
}

void C_Game::MouseReleased()
{
    if(_event.MouseButton.Button == sf::Mouse::Right)
        RightClick();

    _boolBreakAnim = false;
}

void C_Game::MousePressed()
{
    if(_event.MouseButton.Button == sf::Mouse::Left)
    {
        if(_bSelectedCube && !_boolBreakAnim)
        {
            _boolBreakAnim = true;
            _frameBreakAnim = CUBE_BREAK_ANIM0;
            _timerBreakAnim.Reset();
        }
    }
}

void C_Game::MouseMoved()
{

}

void C_Game::MouseWheel()
{
    if(_event.MouseWheel.Delta == -1)
        _actualHotkeys =  (_actualHotkeys+1) < 9 ? _actualHotkeys+1 : 0;
    else if(_event.MouseWheel.Delta == 1)
        _actualHotkeys = (_actualHotkeys-1) >= 0 ? _actualHotkeys-1 : 9;

    _sprSelectedHotkeys.SetPosition( _sprHotkeys.GetPosition().x-1 + _actualHotkeys*20, _sprHotkeys.GetPosition().y);
    _actuelCubeInHand = _itemInHotkeys[_actualHotkeys];
}

void C_Game::KeyPressed()
{
    if(_event.Key.Code == sf::Key::Escape)
        continuer = false;
    else if(_event.Key.Code == sf::Key::F)
    {
        Vector3D v, w;
        v = _cam->getPosition();
        w = _cam->getForward();

        std::cout << "x : "<<v.X << ", y : "<<v.Y<<", z : "<<v.Z<<std::endl;
        std::cout << "Forward x : "<<w.X << ", y : "<<w.Y<<", z : "<<w.Z<<std::endl;
        std::cout << "Target x : "<<_vSelectedCube.X<<", y : "<<_vSelectedCube.Y<<", z : "<<_vSelectedCube.Z<<std::endl<<std::endl;
    }
    else if(_event.Key.Code == sf::Key::Space)
    {
        if(GetCubeType(_cam->getPosition().X, _cam->getPosition().Y, _cam->getPosition().Z-2) != CUBE_AIR)
            _boolJumping = true;
    }

    for(int i=0;i<9;i++)
    {
        if(_event.Key.Code == 49+i)
        {
            _actualHotkeys = i;
            _sprSelectedHotkeys.SetPosition( _sprHotkeys.GetPosition().x-1 + i*20, _sprHotkeys.GetPosition().y);
            _actuelCubeInHand = _itemInHotkeys[i];
        }
    }
}

void C_Game::KeyReleased()
{

}

void C_Game::Draw()
{
    Vector3D u = _cam->getPosition();

    glBindTexture(GL_TEXTURE_2D, _texture); // Bind the cubes' texture

    for(int a=1;a<NB_TYPE_CUBE;a++) // a inits to 1, 0 = CUBE_AIR
    {
        _cube[a].BindBuffer(); //Bind the cube's VBO ( vertices, texture coord, indices )
        for(unsigned int i=0;i<_tabCube[a].size();i++)
        {
            if( _tabCube[a][i]._dist < (_fogStart*_fogStart))
            {
                glPushMatrix();
                glTranslated( _tabCube[a][i].x, _tabCube[a][i].y, _tabCube[a][i].z);
                _cube[a].Draw();
                glPopMatrix();
            }
        }
        _cube[a].UnbindBuffer();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(_bSelectedCube)
    {
        glPushMatrix();
        glTranslated(_vSelectedCube.X-0.0005f, _vSelectedCube.Y - 0.0005f, _vSelectedCube.Z - 0.0005f); // _cubeBreakAnim is 0.001f larger than an usual cube

        if(_boolBreakAnim)
        {
            _cubeBreakAnim[_frameBreakAnim-CUBE_BREAK_ANIM0].BindBuffer();
            _cubeBreakAnim[_frameBreakAnim-CUBE_BREAK_ANIM0].Draw();
            _cubeBreakAnim[_frameBreakAnim-CUBE_BREAK_ANIM0].UnbindBuffer();
        }

        glTranslated(-0.0005f, -0.0005f, -0.0005f); // The selection's cube is 0.001f larger than _cubeBreakAnim
        _cube[0].BindBuffer();
        _cube[0].Draw();
        _cube[0].UnbindBuffer();

        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);

    _screen->Draw(_sprHotkeys);
    _screen->Draw(_sprSelectedHotkeys);
    for(int i=0;i<9;i++)
        if(_itemInHotkeys[i] != CUBE_AIR)
            _screen->Draw(_sprItemInHotkeys[i]);
}

void C_Game::TimerManagement()
{
    Picking();

    if(_boolBreakAnim)
    {
        if(_timerBreakAnim.GetElapsedTime() > 0.20f)
        {
            if(_frameBreakAnim == CUBE_BREAK_ANIM9)
                LeftClick();
            else
                _frameBreakAnim++;

            _timerBreakAnim.Reset();
        }
    }

    CallPhysicsFunctions();

}

void C_Game::DeleteCubeOfVector(const int typ, const int x, const int y, const int z) //Delete cube from display vector
{
    for(unsigned int i=0;i< _tabCube[typ].size();i++)
    {
        if(_tabCube[typ][i].x == x &&_tabCube[typ][i].y == y && _tabCube[typ][i].z == z)
        {
            _tabCube[typ].erase( _tabCube[typ].begin() + i );
            break;
        }
    }
}

void C_Game::Run() // Thread Function !
{
    while(continuer)
    {
        Vector3D v = _cam->getPosition();
        int a = v.X / CHUNK_SIZE;
        int b = v.Y / CHUNK_SIZE;
        int marge = (_fogStart / CHUNK_SIZE) + 1;

        if(v.X < 0) a--;
        if(v.Y < 0) b--;

        if(_actualChunkX != a)
        {
            if( (_actualChunkX - a) > 0)
            {
                for(int i=b-marge;i<b+marge+1;i++)
                {
                    if(!LoadChunk(_actualChunkX-marge, i)) //If the chunk can't be founded in the save
                        CreateRandomChunk(_actualChunkX-marge, i); // A random chunk is created
                    CheckChunksCubesVisibility(_actualChunkX-marge, i);
                    DeleteChunkFromMemory(_actualChunkX+marge, i); // Delete the chunk which is too far to be displayed
                }
            }
            else
            {
                for(int i=b-marge;i<b+marge+1;i++)
                {
                    if(!LoadChunk(_actualChunkX+marge, i))
                        CreateRandomChunk(_actualChunkX+marge, i);
                    CheckChunksCubesVisibility(_actualChunkX+marge, i);
                    DeleteChunkFromMemory(_actualChunkX-marge, i);
                }
            }
        }
        if(_actualChunkY != b)
        {
            if( (_actualChunkY - b) > 0)
            {
                for(int i=a-marge;i<a+marge+1;i++)
                {
                    if(!LoadChunk(i, _actualChunkY-marge))
                        CreateRandomChunk(i, _actualChunkY-marge);
                    CheckChunksCubesVisibility(i, _actualChunkY-marge);
                    DeleteChunkFromMemory(i, _actualChunkY+marge);
                }
            }
            else
            {
                for(int i=a-marge;i<a+marge+1;i++)
                {
                    if(!LoadChunk(i, _actualChunkY+marge))
                        CreateRandomChunk(i, _actualChunkY+marge);
                    CheckChunksCubesVisibility(i, _actualChunkY+marge);
                    DeleteChunkFromMemory(i, _actualChunkY-marge);
                }
            }
        }

        _actualChunkX = a;
        _actualChunkY = b;
    }
}
