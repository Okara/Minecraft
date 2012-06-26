#ifndef LINEEDIT_HPP_INCLUDED
#define LINEEDIT_HPP_INCLUDED

#include "widget.hpp"

class C_LineEdit : public C_Widget
{
    public:
        C_LineEdit();
        virtual ~C_LineEdit();

        virtual void Draw(sf::RenderWindow*);
        virtual void move(const float, const float);
        virtual void resize(const float, const float);
        virtual const bool clicked(const float, const float);
        virtual const bool injectKey(const sf::Key::Code&, const bool);

        void focus(const bool);

    protected:
        std::string _text;
        unsigned int _nbCaractMax;
        sf::String _sfText;

        bool _hasFocus, _writeMAJ;

        void PrepareBackground();
        void FocusReact();
};

#endif // LINEEDIT_HPP_INCLUDED
