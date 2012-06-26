#include "game.hpp"

void C_Game::SetItemInHotkeys(const unsigned char item, const int pos)
{
    if(pos < 9)
    {
        _itemInHotkeys[pos] = item;
        _sprItemInHotkeys[pos].SetImage(*C_Resource::GetSingleton()->GetImage("data/texture/terrain.png"));

        float a, b;
        a = item % 16;
        a *= 16;
        b = (int)(item / 16);
        b *= 16;
        _sprItemInHotkeys[pos].SetSubRect(sf::IntRect(a,b, a+16, b+16  ));
    }
}
