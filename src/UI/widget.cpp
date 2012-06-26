#include "widget.hpp"

C_Widget::C_Widget()
{
    _ima = new sf::Image(100, 45, sf::Color::White);
    _ima->SetSmooth(false);

    _spr = new sf::Sprite();
    _spr->SetImage(*_ima);
}

C_Widget::~C_Widget()
{
    if(_ima != NULL)
        delete _ima;
    _ima = NULL;
    if(_spr != NULL)
        delete _spr;
    _spr = NULL;
}

void C_Widget::Draw(sf::RenderWindow *sc)
{
    sc->Draw(*_spr);
}

void C_Widget::move(const float x, const float y)
{
    _spr->SetPosition(x, y);
}

void C_Widget::resize(const float x, const float y)
{
    float xprec = _spr->GetPosition().x;
    float yprec = _spr->GetPosition().y;

    delete _ima;
    _ima = new sf::Image(x, y, sf::Color::White);
    _ima->SetSmooth(false);

    delete _spr;
    _spr = new sf::Sprite();
    _spr->SetImage(*_ima);
    _spr->SetPosition(xprec, yprec);
}

const float C_Widget::width() const
{
    return _ima->GetWidth();
}

const float C_Widget::height() const
{
    return _ima->GetHeight();
}

const bool C_Widget::mouseOver(const float x, const float y)
{
    float xspr = _spr->GetPosition().x;
    float yspr = _spr->GetPosition().y;

    if(x > xspr && y > yspr && x < ( xspr + width()) && y < ( yspr + height()))
        return true;
    return false;
}

const bool C_Widget::clicked(const float x, const float y)
{
    if(mouseOver(x, y))
    {
        std::cout<<"clicked on "<<this<<std::endl;
        return true;
    }
    return false;
}

const bool C_Widget::injectKey(const sf::Key::Code & key, const bool entry)
{
    return false;
}
