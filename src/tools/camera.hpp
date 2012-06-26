#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <GL/GL.h>
#include <GL/glu.h>
#include <map>

#include "vector3D.hpp"

class C_camera
{
    public:
        C_camera(const Vector3D & position = Vector3D(0,0,0));

        void OnMouseMotion(float, float);
        void SetMousePosition(float, float);
        void MouseWheel(const sf::Event &);
        void OnKeyboard(const sf::Event&);

        void animate(unsigned int timestep);
        void BackToLastestPositionX();
        void BackToLastestPositionY();
        void setSpeed(double speed);
        void setSensivity(double sensivity);

        void setPosition(const Vector3D & position);
        const Vector3D getPosition() const;
        const Vector3D getForward() const;
        const Vector3D getTemp() const;

        void look();


    protected:
        double _speed;
        double _sensivity;

        //vertical motion stuffs
        unsigned int _timeBeforeStoppingVerticalMotion;
        bool _verticalMotionActive;
        int _verticalMotionDirection;

        typedef std::map<sf::Key::Code,bool> KeyStates;
        KeyStates _keystates;
        typedef std::map<std::string,sf::Key::Code> KeyConf;
        KeyConf _keyconf;

        Vector3D _position;
        Vector3D _target;
        Vector3D _forward, _temp;
        Vector3D _left;
        double _theta;
        double _phi;

        unsigned int lastesttimestep;

        float previousX, previousY;

        void VectorsFromAngles();
};

#endif // CAMERA_HPP_INCLUDED
