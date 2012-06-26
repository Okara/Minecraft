#include "mod.hpp"
#include "camera.hpp"

#include <cmath>
#include <iostream>

C_camera::C_camera(const Vector3D & position)
{
    _position = position;
    _target = Vector3D(0.0f, 0.0f, 0.0f);
    _phi = 0;
    _theta = 90;
    lastesttimestep = 0;
    VectorsFromAngles();

    _speed = 0.01;
    _sensivity = 0.2;
    _verticalMotionActive = false;
    _keyconf["forward"] = sf::Key::Z;
    _keyconf["backward"] = sf::Key::S;
    _keyconf["strafe_left"] = sf::Key::Q;
    _keyconf["strafe_right"] = sf::Key::D;
    _keyconf["boost"] = sf::Key::RShift;
    _keystates[_keyconf["forward"]] = false;
    _keystates[_keyconf["backward"]] = false;
    _keystates[_keyconf["strafe_left"]] = false;
    _keystates[_keyconf["strafe_right"]] = false;
    _keystates[_keyconf["boost"]] = false;

    previousX = previousY = 300;

    C_Log::GetSingleton()->AddMessage( std::string("Camera created : pos( "+FloatToString(_position.X)+", "
                                                                        +FloatToString(_position.Y)+", "
                                                                        +FloatToString(_position.Z)+").") );
}

void C_camera::SetMousePosition(float xx, float yy)
{
    previousX = xx;
    previousY = yy;
}

void C_camera::OnMouseMotion(float xx, float yy)
{
    _theta -= (xx-previousX)*_sensivity;
    _phi -= (yy-previousY)*_sensivity;
    VectorsFromAngles();
}

void C_camera::MouseWheel(const sf::Event & ev)
{
    if(ev.MouseWheel.Delta == -1)
    {

    }
    else if(ev.MouseWheel.Delta == 1)
    {

    }
}

void C_camera::OnKeyboard(const sf::Event & event)
{
    for (KeyStates::iterator it = _keystates.begin();it != _keystates.end(); it++)
    {
        if (event.Key.Code == it->first)
        {
            it->second = (event.Type == sf::Event::KeyPressed);
            break;
        }
    }
}

void C_camera::animate(unsigned int timestep)
{
    static const Vector3D up(0,-1,0);
    Vector3D _up;
    _up.X = _left.Y;
    _up.Y = _left.X;
    _up.Z = _left.Z;

    double realspeed = (_keystates[_keyconf["boost"]])?10*_speed:_speed;

    if (_keystates[_keyconf["forward"]])
    {
        _position.X += _temp.X * (realspeed * timestep);
        _position.Y += _temp.Y * (realspeed * timestep);
    }
    if (_keystates[_keyconf["backward"]])
    {
        _position.X -= _temp.X * (realspeed * timestep);
        _position.Y -= _temp.Y * (realspeed * timestep);
    }
    if (_keystates[_keyconf["strafe_left"]])
    {
        _position.X += _left.X * (realspeed * timestep);
        _position.Y += _left.Y * (realspeed * timestep);
    }
    if (_keystates[_keyconf["strafe_right"]])
    {
        _position.X -= _left.X * (realspeed * timestep);
        _position.Y -= _left.Y * (realspeed * timestep);
    }

    _target = _position + _forward;

    lastesttimestep = timestep;
}

void C_camera::BackToLastestPositionX()
{
    static const Vector3D up(0,-1,0);
    Vector3D _up;
    _up.X = _left.Y;
    _up.Y = _left.X;
    _up.Z = _left.Z;

    double realspeed = (_keystates[_keyconf["boost"]])?10*_speed:_speed;

    if (_keystates[_keyconf["forward"]])
        _position.X -= _temp.X * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["backward"]])
        _position.X += _temp.X * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["strafe_left"]])
        _position.X -= _left.X * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["strafe_right"]])
        _position.X += _left.X * (realspeed * lastesttimestep);

    _target = _position + _forward;
}

void C_camera::BackToLastestPositionY()
{
    static const Vector3D up(0,-1,0);
    Vector3D _up;
    _up.X = _left.Y;
    _up.Y = _left.X;
    _up.Z = _left.Z;

    double realspeed = (_keystates[_keyconf["boost"]])?10*_speed:_speed;

    if (_keystates[_keyconf["forward"]])
        _position.Y -= _temp.Y * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["backward"]])
        _position.Y += _temp.Y * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["strafe_left"]])
        _position.Y -= _left.Y * (realspeed * lastesttimestep);
    if (_keystates[_keyconf["strafe_right"]])
        _position.Y += _left.Y * (realspeed * lastesttimestep);

    _target = _position + _forward;
}

void C_camera::setSpeed(double speed)
{
    _speed = speed;
}

void C_camera::setSensivity(double sensivity)
{
    _sensivity = sensivity;
}

void C_camera::setPosition(const Vector3D & position)
{
    _position = position;
    _target = _position + _forward;
}

const Vector3D C_camera::getPosition() const
{
    return _position;
}

const Vector3D C_camera::getForward() const
{
    return _forward;
}

const Vector3D C_camera::getTemp() const
{
    return _temp;
}

void C_camera::VectorsFromAngles()
{
    static const Vector3D up(0,0,1);
    if (_phi > 89)
        _phi = 89;
    else if (_phi < -89)
        _phi = -89;
    double r_temp = cos(_phi*M_PI/180);
    _forward.Z = sin(_phi*M_PI/180);
    _forward.X = r_temp*cos(_theta*M_PI/180);
    _forward.Y = r_temp*sin(_theta*M_PI/180);

    _temp.Z = sin(_phi*M_PI/180);
    _temp.X = cos(_theta*M_PI/180);
    _temp.Y = sin(_theta*M_PI/180);

    _left = up.crossProduct(_forward);
    _left.normalize();

    _target = _position + _forward;
}

void C_camera::look()
{
    gluLookAt(_position.X,_position.Y,_position.Z,
              _target.X,_target.Y,_target.Z,
              0,0,1);
}
