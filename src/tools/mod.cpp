#include "mod.hpp"

const std::string FloatToString(const float f)
{
    std::ostringstream oss;
    oss << f;
    return oss.str();
}

const std::string IntToString(const int f)
{
    std::ostringstream oss;
    oss << f;
    return oss.str();
}

const float StringToFloat( const std::string & str)
{
    std::istringstream iss( str );
    float tmp;
    iss >> tmp;

    return tmp;
}

C_Mod::C_Mod(sf::RenderWindow* scr)
{
    _screen = scr;

    _cam = new C_camera(Vector3D(1.0f, 1.0f, 1.0f));

    _screen->SetCursorPosition(_screen->GetWidth()/2, _screen->GetHeight()/2);
    _cam->SetMousePosition(_screen->GetWidth()/2, _screen->GetHeight()/2);

    _enableBlend = false;
    _enabledShader = false;

    srand(time(NULL));
}

C_Mod::~C_Mod()
{
    delete _cam;

    for(unsigned int i=0;i<_widget.size();i++)
        delete _widget[i];
}

void C_Mod::loop()
{
    continuer = true;
    click = keyboard = false;
    bool clickOnUI = false;
    sf::Clock camTimer;
    float previousX = 0, previousY = 0;

    sf::String str_fps;
    int compt_fps = 0;
    sf::Clock timer_fps;
    str_fps.SetScale(0.4f, 0.4f);
    str_fps.SetColor(sf::Color::White);
    str_fps.SetPosition(10, 10);

    _screen->PreserveOpenGLStates(true);

    while(continuer)
    {
        while(_screen->GetEvent(_event))
        {
///EVENT
            if(_event.Type == sf::Event::Closed)
                continuer = false;
            else if(_event.Type == sf::Event::MouseButtonReleased && click)
            {
                click = false;

                float xxx = _screen->GetInput().GetMouseX();
                float yyy = _screen->GetInput().GetMouseY();
                for(unsigned int i=0;i<_widget.size();i++)
                    _widget[i]->clicked(xxx, yyy);

                MouseReleased();
            }
            else if(_event.Type == sf::Event::MouseButtonPressed)
            {
                click = true;
                clickOnUI = false;

                previousX = _screen->GetInput().GetMouseX();
                previousY = _screen->GetInput().GetMouseY();
                for(unsigned int i=0;i<_widget.size();i++)
                {
                    if(_widget[i]->mouseOver(previousX, previousY))
                    {
                        clickOnUI = true;
                        break;
                    }
                }

                if(!clickOnUI)
                    _cam->SetMousePosition(previousX, previousY);

                MousePressed();
            }
            else if(_event.Type == sf::Event::MouseMoved)
            {
                _cam->OnMouseMotion(_screen->GetInput().GetMouseX(), _screen->GetInput().GetMouseY());
                _screen->SetCursorPosition(_screen->GetWidth()/2, _screen->GetHeight()/2);
                MouseMoved();
            }
            else if(_event.Type == sf::Event::MouseWheelMoved)
            {
                MouseWheel();
                _event.MouseWheel.Delta = 0;
            }
            else if(_event.Type == sf::Event::KeyPressed)
            {
                bool wigdetHasFocus = false;

                for(unsigned int i=0;i<_widget.size();i++)
                {
                    if(_widget[i]->injectKey(_event.Key.Code, true))
                    {
                        wigdetHasFocus = true;
                        break;
                    }
                }

                if(!wigdetHasFocus)
                {
                    keyboard = true;
                    _cam->OnKeyboard(_event);
                    KeyPressed();
                }
            }
            else if(_event.Type == sf::Event::KeyReleased)
            {
                for(unsigned int i=0;i<_widget.size();i++)
                    _widget[i]->injectKey(_event.Key.Code, false);
                //if(keyboard)
                {
                    keyboard = false;
                    _cam->OnKeyboard(_event);
                    KeyReleased();
                }
            }
        }
        glDisable(GL_LIGHTING);
        _cam->animate(int(camTimer.GetElapsedTime()*10000));
        camTimer.Reset();

        TimerManagement();
///DRAW
        _screen->SetActive();
        if(click && !clickOnUI)
            _screen->SetCursorPosition(previousX, previousY); //_screen->GetWidth()/2, _screen->GetHeight()/2);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glViewport(0, 0, _screen->GetWidth(), _screen->GetHeight());
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, float(_screen->GetWidth()) / float(_screen->GetHeight()), 0.1f, 5000.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _skydome.Draw();

        _cam->look();

        glPushMatrix();
        Draw();
        glPopMatrix();

        DrawUI();

        if(timer_fps.GetElapsedTime() > 1.0f)
        {
            str_fps.SetText("FPS : "+IntToString(compt_fps));
            compt_fps = 0;
            timer_fps.Reset();
        }
        compt_fps++;
        _screen->Draw(str_fps);

        _screen->Display();
    }
}

void C_Mod::AddWidget(C_Widget *wgt)
{
    _widget.push_back(wgt);
}

void C_Mod::DrawUI()
{
    for(unsigned int i=0;i<_widget.size();i++)
    {
        _widget[i]->Draw(_screen);
    }
}
