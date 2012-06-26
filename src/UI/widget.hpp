#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include <SFML/graphics.hpp>
#include <iostream>

class C_Widget
{
    public:
        C_Widget();
        virtual ~C_Widget();

        virtual void Draw(sf::RenderWindow*);
        virtual void move(const float, const float);
        virtual void resize(const float, const float);
        virtual const float width() const;
        virtual const float height() const;
        virtual const bool clicked(const float, const float);
        virtual const bool mouseOver(const float, const float);
        virtual const bool injectKey(const sf::Key::Code&, const bool);

    protected:
        sf::Image *_ima;
        sf::Sprite *_spr;
};

#endif // WIDGET_HPP_INCLUDED
