#ifndef OKARA_MOD_HPP_INCLUDED
#define OKARA_MOD_HPP_INCLUDED

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <GL/GL.h>
#include <GL/glu.h>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

#include "../UI/lineedit.hpp"

#include "skydome.hpp"
#include "camera.hpp"
#include "log.hpp"

const std::string FloatToString(const float);
const std::string IntToString(const int);
const float StringToFloat( const std::string &);

class C_Mod
{
    public:
        C_Mod(sf::RenderWindow*);
        virtual ~C_Mod();
        void loop();

        void AddWidget(C_Widget*);

    protected:
        virtual void MousePressed() = 0;
        virtual void MouseReleased() = 0;
        virtual void MouseMoved() = 0;
        virtual void KeyPressed() = 0;
        virtual void KeyReleased() = 0;
        virtual void MouseWheel() = 0;
        virtual void Draw() = 0;
        virtual void TimerManagement() = 0;

        void DrawUI();
        std::vector<C_Widget*> _widget;

        sf::RenderWindow* _screen;
        sf::Event _event;
        bool continuer, click, keyboard;

        C_Skydome _skydome;

        C_camera *_cam;

        bool _enableBlend, _enabledShader;
};

#endif // MOD_HPP_INCLUDED
