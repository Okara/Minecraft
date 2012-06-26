#include "game.hpp"

void C_Game::Picking()
{
    int oldX = _vSelectedCube.X;
    int oldY = _vSelectedCube.Y;
    int oldZ = _vSelectedCube.Z;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glViewport(0, 0, _screen->GetWidth(), _screen->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, float(_screen->GetWidth()) / float(_screen->GetHeight()), 0.1f, 5000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _cam->look();

        glPushMatrix();
        Vector3D u = _cam->getPosition();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_FOG);
        glDisable(GL_LIGHTING);
        int compt = 0;
        for(int a=1;a<NB_TYPE_CUBE;a++) // a inits to 1, 0 = CUBE_AIR
        {
            _cube[a].BindBuffer();
            for(unsigned int i=0;i<_tabCube[a].size();i++)
            {
                _tabCube[a][i]._dist = (u.X-_tabCube[a][i].x)*(u.X-_tabCube[a][i].x) + (u.Y-_tabCube[a][i].y)*(u.Y-_tabCube[a][i].y) + (u.Z-_tabCube[a][i].z)*(u.Z-_tabCube[a][i].z);
                if( _tabCube[a][i]._dist < 25)
                {
                    glPushMatrix();
                    glTranslated( _tabCube[a][i].x, _tabCube[a][i].y, _tabCube[a][i].z);
                    compt++;
                    glColor3ub(compt , 0, 0);
                    _cube[a].Draw();
                    glPopMatrix();
                }
            }
            _cube[a].UnbindBuffer();
        }
        glEnable(GL_FOG);
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    unsigned char pixels[3];
    glReadPixels(_screen->GetInput().GetMouseX(), _screen->GetInput().GetMouseY(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);


    if(pixels[0] == 0)
        _bSelectedCube = false;
    else
    {
        compt = 0;
        for(int a=1;a<NB_TYPE_CUBE;a++) // a inits to 1, 0 = CUBE_AIR
        {
            for(unsigned int i=0;i<_tabCube[a].size();i++)
            {
                if( _tabCube[a][i]._dist < 25)
                {
                    compt++;
                    if(compt == pixels[0])
                    {
                        _vSelectedCube.X = _tabCube[a][i].x;
                        _vSelectedCube.Y = _tabCube[a][i].y;
                        _vSelectedCube.Z = _tabCube[a][i].z;
                        _bSelectedCube = true;

                        if(_vSelectedCube.X != oldX || _vSelectedCube.Y != oldY || _vSelectedCube.Z != oldZ)
                        {
                            _frameBreakAnim = CUBE_BREAK_ANIM0;
                            _timerBreakAnim.Reset();
                        }

                        return;
                    }
                    else
                        _bSelectedCube = false;
                }
            }
        }
    }
}

void C_Game::LeftClick()
{
    if(_bSelectedCube)
    {
        int h = _vSelectedCube.X;
        int i = _vSelectedCube.Y;
        int j = _vSelectedCube.Z;

        int diffX = 0;
        int diffY = 0;
        if(h < 0) diffX = 1;
        if(i < 0) diffY = 1;

        int a = (h+diffX)/CHUNK_SIZE;
        if(h < 0)
            a--;
        int b = (i+diffY)/CHUNK_SIZE;
        if(i < 0)
            b--;

        MinecraftChunk *ch = GetChunk(a, b);

        int xx = h + diffX - (int)((h+diffX)/CHUNK_SIZE) * CHUNK_SIZE;
        if(h < 0)
        {
            if(xx <= 0)
                    xx = CHUNK_SIZE - 1 + xx;
        }

        int yy = i + diffY - (int)((i+diffY)/CHUNK_SIZE) * CHUNK_SIZE;
        if(i < 0)
        {
            if(yy <= 0)
                    yy = CHUNK_SIZE - 1 + yy;
        }
        int zz = j;

        int typ = ch->_chunkMap[xx][yy][zz];
        ch->_chunkMap[xx][yy][zz] = CUBE_AIR;
        DeleteCubeOfVector(typ, _vSelectedCube.X, _vSelectedCube.Y, _vSelectedCube.Z);

        CheckCubeVisibility(h, i, j);
        CheckCubeVisibility(h-1, i, j);
        CheckCubeVisibility(h+1, i, j);
        CheckCubeVisibility(h, i-1, j);
        CheckCubeVisibility(h, i+1, j);
        CheckCubeVisibility(h, i, j-1);
        CheckCubeVisibility(h, i, j+1);

        _bSelectedCube = false;
    }
}

void C_Game::RightClick()
{
    if(!_bSelectedCube || _actuelCubeInHand == CUBE_AIR)
        return;

    {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glViewport(0, 0, _screen->GetWidth(), _screen->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, float(_screen->GetWidth()) / float(_screen->GetHeight()), 0.1f, 5000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _cam->look();

    glPushMatrix();
    glTranslated(_vSelectedCube.X-0.0005f, _vSelectedCube.Y - 0.0005f, _vSelectedCube.Z - 0.0005f);

    glBegin(GL_TRIANGLES);

    glColor3ub(10, 10, 10);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
    glColor3ub(20, 20, 20);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3ub(30, 30, 30);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3ub(40, 40, 40);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
    glColor3ub(50, 50, 50);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
    glColor3ub(60, 60, 60);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);

    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();
    }

    unsigned char pixels[3];
    glReadPixels(_screen->GetInput().GetMouseX(), _screen->GetInput().GetMouseY(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    int h = _vSelectedCube.X;
    int i = _vSelectedCube.Y;
    int j = _vSelectedCube.Z;
    int diffX = 0;
    int diffY = 0;
    if(h < 0) diffX = 1;
    if(i < 0) diffY = 1;

    int a = (h+diffX)/CHUNK_SIZE;
    if(h < 0)
        a--;
    int b = (i+diffY)/CHUNK_SIZE;
    if(i < 0)
        b--;
    int xx = h + diffX - (int)((h+diffX)/CHUNK_SIZE) * CHUNK_SIZE;
    if(h < 0)
    {
        if(xx <= 0)
                xx = CHUNK_SIZE - 1 + xx;
    }

    int yy = i + diffY - (int)((i+diffY)/CHUNK_SIZE) * CHUNK_SIZE;
    if(i < 0)
    {
        if(yy <= 0)
                yy = CHUNK_SIZE - 1 + yy;
    }
    int zz = j;

    MinecraftChunk *ch = GetChunk(a, b);

    if(pixels[0] != 0)
    {
        if(pixels[0] == 10 && (zz + 1) < CHUNK_ZVALUE && ch->_chunkMap[xx][yy][zz+1] == CUBE_AIR)
        {
            if((int)_cam->getPosition().X != h || (int)_cam->getPosition().Y != i || (int)_cam->getPosition().Z-1 != j+1)
            {
                ch->_chunkMap[xx][yy][zz+1] = _actuelCubeInHand;
                tabCube temp;
                temp.x = h;
                temp.y = i;
                j++;
                temp.z = j;
                _tabCube[_actuelCubeInHand].push_back(temp);
            }
        }
        else if(pixels[0] == 20 && (zz - 1) >= 0 && ch->_chunkMap[xx][yy][zz-1] == CUBE_AIR)
        {
            if((int)_cam->getPosition().X != h || (int)_cam->getPosition().Y != i || (int)_cam->getPosition().Z != j-1)
            {
                ch->_chunkMap[xx][yy][zz-1] = _actuelCubeInHand;
                tabCube temp;
                temp.x = h;
                temp.y = i;
                j--;
                temp.z = j;
                _tabCube[_actuelCubeInHand].push_back(temp);
            }
        }
        else if(pixels[0] == 30)
        {
            if((int)_cam->getPosition().X != h-1 || (int)_cam->getPosition().Y != i
            || ( (int)_cam->getPosition().Z-1 != j && (int)_cam->getPosition().Z != j))
            {
                if( (xx - 1) >= 0)
                {
                    if( ch->_chunkMap[xx-1][yy][zz] == CUBE_AIR)
                    {
                        ch->_chunkMap[xx-1][yy][zz] = _actuelCubeInHand;
                        tabCube temp;
                        h--;
                        temp.x = h;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
                else
                {
                    MinecraftChunk *chNext = GetChunk(a - 1, b );
                    if( chNext->_chunkMap[15][yy][zz] == CUBE_AIR)
                    {
                        chNext->_chunkMap[15][yy][zz] = _actuelCubeInHand;
                        tabCube temp;
                        h--;
                        temp.x = h;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
            }
        }
        else if(pixels[0] == 60)
        {
            if((int)_cam->getPosition().X != h+1 || (int)_cam->getPosition().Y != i
            || ((int)_cam->getPosition().Z-1 != j && (int)_cam->getPosition().Z != j))
            {
                if((xx + 1) < CHUNK_SIZE)
                {
                    if(ch->_chunkMap[xx+1][yy][zz] == CUBE_AIR)
                    {
                        ch->_chunkMap[xx+1][yy][zz] = _actuelCubeInHand;
                        tabCube temp;
                        h++;
                        temp.x = h;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
                else
                {
                    MinecraftChunk *chNext = GetChunk(a + 1, b);
                    if( chNext->_chunkMap[0][yy][zz] == CUBE_AIR)
                    {
                        chNext->_chunkMap[0][yy][zz] = _actuelCubeInHand;
                        tabCube temp;
                        h++;
                        temp.x = h;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
            }
        }
        else if(pixels[0] == 40)
        {
            if((int)_cam->getPosition().X != h || (int)_cam->getPosition().Y != i-1
            || ((int)_cam->getPosition().Z-1 != j && (int)_cam->getPosition().Z != j))
            {
                if( (yy - 1) >= 0)
                {
                    if( ch->_chunkMap[xx][yy-1][zz] == CUBE_AIR)
                    {
                        ch->_chunkMap[xx][yy-1][zz] = _actuelCubeInHand;
                        tabCube temp;
                        temp.x = h;
                        i--;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
                else
                {
                    MinecraftChunk *chNext = GetChunk(a, b - 1);
                    if( chNext->_chunkMap[xx][15][zz] == CUBE_AIR)
                    {
                        chNext->_chunkMap[xx][15][zz] = _actuelCubeInHand;
                        tabCube temp;
                        temp.x = h;
                        i--;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
            }
        }
        else if(pixels[0] == 50)
        {
            if((int)_cam->getPosition().X != h || (int)_cam->getPosition().Y != i+1
            || ((int)_cam->getPosition().Z-1 != j && (int)_cam->getPosition().Z != j))
            {
                if((yy + 1) < CHUNK_SIZE)
                {
                    if(ch->_chunkMap[xx][yy+1][zz] == CUBE_AIR)
                    {
                        ch->_chunkMap[xx][yy+1][zz] = _actuelCubeInHand;
                        tabCube temp;
                        temp.x = h;
                        i++;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
                else
                {
                    MinecraftChunk *chNext = GetChunk(a, b +1 );
                    if( chNext->_chunkMap[xx][0][zz] == CUBE_AIR)
                    {
                        chNext->_chunkMap[xx][0][zz] = _actuelCubeInHand;
                        tabCube temp;
                        temp.x = h;
                        i++;
                        temp.y = i;
                        temp.z = j;
                        _tabCube[_actuelCubeInHand].push_back(temp);
                    }
                }
            }
        }

        CheckCubeVisibility(h, i, j);
        CheckCubeVisibility(h-1, i, j);
        CheckCubeVisibility(h+1, i, j);
        CheckCubeVisibility(h, i-1, j);
        CheckCubeVisibility(h, i+1, j);
        CheckCubeVisibility(h, i, j-1);
        CheckCubeVisibility(h, i, j+1);
    }
}

void C_Game::CheckCubeVisibility(const int h, const int i, const int j)
{
    int diffX = 0;
    int diffY = 0;
    if(h < 0) diffX = 1;
    if(i < 0) diffY = 1;

    int a = (h+diffX)/CHUNK_SIZE;
    if(h < 0)
        a--;
    int b = (i+diffY)/CHUNK_SIZE;
    if(i < 0)
        b--;

    MinecraftChunk *ch = GetChunk(a, b);

    int xx = h + diffX - (int)((h+diffX)/CHUNK_SIZE) * CHUNK_SIZE;
    if(h < 0)
    {
        if(xx <= 0)
                xx = CHUNK_SIZE - 1 + xx;
    }

    int yy = i + diffY - (int)((i+diffY)/CHUNK_SIZE) * CHUNK_SIZE;
    if(i < 0)
    {
        if(yy <= 0)
                yy = CHUNK_SIZE - 1 + yy;
    }
    int zz = j;

    if(xx >= 0 && xx < CHUNK_SIZE
    && yy >= 0 && yy < CHUNK_SIZE
    && zz >= 0 && zz < CHUNK_ZVALUE
    && ch->_chunkMap[xx][yy][zz] != CUBE_AIR)
    {
        DeleteCubeOfVector(ch->_chunkMap[xx][yy][zz], h, i, j);

        bool visible = false;

        if(xx-1 >= 0)
        {
            if(ch->_chunkMap[xx-1][yy][zz] == CUBE_AIR)
                visible = true;
        }
        else
        {
            MinecraftChunk *chNext = GetChunk(a - 1, b);

            if(chNext->_chunkMap[15][yy][zz] == CUBE_AIR)
                visible = true;
        }
        if(xx+1 < CHUNK_SIZE)
        {
            if(ch->_chunkMap[xx+1][yy][zz] == CUBE_AIR)
                visible = true;
        }
        else
        {
            MinecraftChunk *chNext = GetChunk(a + 1, b);
            if(chNext->_chunkMap[0][yy][zz] == CUBE_AIR)
                visible = true;
        }

        if( yy-1 >= 0)
        {
            if(ch->_chunkMap[xx][yy-1][zz] == CUBE_AIR)
                visible = true;
        }
        else
        {
            MinecraftChunk *chNext = GetChunk(a , b - 1);
            if(chNext->_chunkMap[xx][15][zz] == CUBE_AIR)
                visible = true;
        }

        if(yy+1 < CHUNK_SIZE)
        {
            if(ch->_chunkMap[xx][yy+1][zz] == CUBE_AIR)
                visible = true;
        }
        else
        {
            MinecraftChunk *chNext = GetChunk(a, b + 1);
            if(chNext->_chunkMap[xx][0][zz] == CUBE_AIR)
                visible = true;
        }

        if( (zz-1 >= 0 && ch->_chunkMap[xx][yy][zz-1] == CUBE_AIR) || ( zz+1 < CHUNK_ZVALUE && ch->_chunkMap[xx][yy][zz+1] == CUBE_AIR) )
            visible =  true;

        if(visible)
        {
            tabCube temp;
            temp.x = h;
            temp.y = i;
            temp.z = j;
            _tabCube[ch->_chunkMap[xx][yy][zz]].push_back(temp);
        }
    }
}
