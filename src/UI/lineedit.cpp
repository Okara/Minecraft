#include "lineedit.hpp"

C_LineEdit::C_LineEdit()
{
    _nbCaractMax = 255;

    _hasFocus = false;
    _writeMAJ = false;

    _sfText.SetColor(sf::Color::Black);
    _sfText.SetSize(15.0f);

    PrepareBackground();
}

C_LineEdit::~C_LineEdit()
{
}

void C_LineEdit::Draw(sf::RenderWindow *sc)
{
    C_Widget::Draw(sc);

    sc->Draw(_sfText);
}

void C_LineEdit::PrepareBackground()
{
    for(int i=0;i<width();i++)
    {
        _ima->SetPixel(i, 0, sf::Color::Red);
        _ima->SetPixel(i, height()-1, sf::Color::Red);

        for(int j=1;j<height()-1;j++)
            _ima->SetPixel(i, j, sf::Color(255, 255, 255, 128));
    }
    for(int i=0;i<height();i++)
    {
        _ima->SetPixel(0, i, sf::Color::Red);
        _ima->SetPixel(width()-1, i, sf::Color::Red);
    }

    _ima->CreateMaskFromColor(sf::Color(255, 255, 255));
}

void C_LineEdit::move(const float x, const float y)
{
    C_Widget::move(x, y);

    _sfText.SetPosition(x+5, y+5);
}

void C_LineEdit::resize(const float x, const float y)
{
    C_Widget::resize(x, y);
    PrepareBackground();
}

const bool C_LineEdit::clicked(const float x, const float y)
{
    if(mouseOver(x, y))
    {
        focus(true);
        return true;
    }
    focus(false);
    return false;
}

void C_LineEdit::focus(const bool b)
{
    _hasFocus = b;
    FocusReact();
}

void C_LineEdit::FocusReact()
{
    sf::Color color(sf::Color::Red);
    if(_hasFocus)
        color = sf::Color::Green;

    for(int i=0;i<width();i++)
    {
        _ima->SetPixel(i, 0, color);
        _ima->SetPixel(i, height()-1, color);
    }
    for(int i=0;i<height();i++)
    {
        _ima->SetPixel(0, i, color);
        _ima->SetPixel(width()-1, i, color);
    }
}

const bool C_LineEdit::injectKey(const sf::Key::Code & key, const bool entry)
{
    if(key == 258)
        _writeMAJ = entry;
    else if(entry && !_hasFocus && key == 278)
    {
        focus(true);
        return true;
    }
    if(_hasFocus && entry)
    {
        if(key == 256)
        {
            _text.clear();
            focus(false);
        }
        else if(key == 278)
        {
            _text.clear();
            focus(false);
        }
        else
        {
            if(key == 279)
            {
                if(_text.size() > 0)
                    _text.erase(_text.size()-1, 1);
            }
            else if(_text.size() < _nbCaractMax)
            {
                if(key >= 97 && key <= 122)
                {
                    if(_writeMAJ)
                        _text += static_cast<char>(key-32);
                    else
                        _text += static_cast<char>(key);
                }
                else if(key >= 48 && key <= 57)
                {
                    if(_writeMAJ)
                        _text += static_cast<char>(key);
                    else
                        _text += static_cast<char>(key-13);
                }
                else if(key >= 295 && key <= 304)
                    _text += static_cast<char>(key-247);
                else if(key == 277)
                    _text += " ";
            }
        }

        _sfText.SetText( _text );
        int i=1;
        while( (_sfText.GetRect().Right - _sfText.GetRect().Left) > (width()-10))
        {
            _sfText.SetText( _text.substr(i, _text.size()-1) );
            i++;
        }

        return true;
    }
    else
        return false;
}
