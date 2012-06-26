#include "game.hpp"

void C_Game::CallPhysicsFunctions()
{
    Vector3D v = _cam->getPosition();

    //COLLISIONS TESTS
    if(GetCubeType(v.X+0.4f, v.Y+0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X+0.4f, v.Y+0.4f, v.Z) != CUBE_AIR
    || GetCubeType(v.X+0.4f, v.Y-0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X+0.4f, v.Y-0.4f, v.Z) != CUBE_AIR
    || GetCubeType(v.X-0.4f, v.Y+0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X-0.4f, v.Y+0.4f, v.Z) != CUBE_AIR
    || GetCubeType(v.X-0.4f, v.Y-0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X-0.4f, v.Y-0.4f, v.Z) != CUBE_AIR)
    {
        _cam->BackToLastestPositionX();
        _cam->BackToLastestPositionY();
    }
    else
    {
        if(GetCubeType(v.X+0.4f, v.Y, v.Z-1) != CUBE_AIR || GetCubeType(v.X+0.4f, v.Y, v.Z) != CUBE_AIR
        || GetCubeType(v.X-0.4f, v.Y, v.Z-1) != CUBE_AIR || GetCubeType(v.X-0.4f, v.Y, v.Z) != CUBE_AIR)
            _cam->BackToLastestPositionX();
        if(GetCubeType(v.X, v.Y+0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X, v.Y+0.4f, v.Z) != CUBE_AIR
        || GetCubeType(v.X, v.Y-0.4f, v.Z-1) != CUBE_AIR || GetCubeType(v.X, v.Y-0.4f, v.Z) != CUBE_AIR)
            _cam->BackToLastestPositionY();
    }



    if(_boolJumping && _timerPhysics.GetElapsedTime() > 0.025f) // JUMPING
    {
        _frameJumping++;
        if(_frameJumping != 6 && _frameJumping != 7)
        {
            if(GetCubeType(_cam->getPosition().X, _cam->getPosition().Y, _cam->getPosition().Z+0.2f+(0.1f*_frameJumping)) == CUBE_AIR)
                _cam->setPosition(Vector3D(_cam->getPosition().X, _cam->getPosition().Y, _cam->getPosition().Z+(0.1f*_frameJumping) ));
            else
            {
                _frameJumping = 0;
                _boolJumping = false;
            }
        }
        if(_frameJumping > 6)
        {
            _frameJumping = 0;
            _boolJumping = false;
        }
        _timerPhysics.Reset();
    }
    else if(!_boolJumping && _timerPhysics.GetElapsedTime() > 0.015f) //FALLING
    {
        if(GetCubeType(v.X+0.2f, v.Y+0.2f, v.Z-1.6f) == CUBE_AIR && GetCubeType(v.X+0.2f, v.Y-0.2f, v.Z-1.6f) == CUBE_AIR
        && GetCubeType(v.X-0.2f, v.Y+0.2f, v.Z-1.6f) == CUBE_AIR && GetCubeType(v.X-0.2f, v.Y-0.2f, v.Z-1.6f) == CUBE_AIR
        && GetCubeType(v.X+0.2f, v.Y, v.Z-1.6f) == CUBE_AIR && GetCubeType(v.X-0.2f, v.Y, v.Z-1.6f) == CUBE_AIR
        && GetCubeType(v.X, v.Y+0.2f, v.Z-1.6f) == CUBE_AIR && GetCubeType(v.X, v.Y-0.2f, v.Z-1.6f) == CUBE_AIR)
        {
            _isFalling = true;
        }

        if(_isFalling)
        {
            if(GetCubeType(v.X, v.Y, v.Z-1.6f) == CUBE_AIR)
            {
                _cam->setSpeed(0.0003);
                _cam->setPosition(Vector3D(_cam->getPosition().X, _cam->getPosition().Y, _cam->getPosition().Z-0.1f));
            }
            else
            {
                _isFalling = false;
                _cam->setSpeed(0.0006);
            }
        }
        _timerPhysics.Reset();
    }
}

