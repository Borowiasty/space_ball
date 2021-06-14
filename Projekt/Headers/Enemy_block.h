#pragma once
#include <SFML/Graphics.hpp>


class Enemy_block : public sf::Sprite
{
protected:
    int life;
    bool can_be_destroyed = true;
    bool gift = false;
public:
    Enemy_block() : Sprite() {}
    Enemy_block(const int index, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, double pos_x, double pos_y) : Sprite()
    {
        switch (index)
        {
        case 0:     //default
            life = 1;
            setTexture(textures.at("block"));
            break;
        case 1:     //harder block
            life = 2;
            setTexture(textures.at("locked_block"));
            break;
        case 2:     //turboharder block
            life = 3;
            setTexture(textures.at("locked_block"));
            setColor(sf::Color::Red);
            break;
        case 3:     //indestroable block
            life = -1;
            setTexture(textures.at("block"));
            setColor(sf::Color(128, 128, 128));
            can_be_destroyed = 1;
            break;
        case 4:     //gift block 1
            life = 1;
            gift = 1;
            break;
        case 5:     //gift block 2
            life = 1;
            gift = 1;
            break;
        case 6:     //gift block 3
            life = 1;
            gift = 1;
            break;
        case 7:     //gift block 4
            life = 1;
            gift = 1;
            break;
        }
        setScale(0.977, 0.977);
        setPosition(pos_x, pos_y);
    }

    std::tuple<double, double> bounce()
    {
        if (gift) { drop(); }
        setScale(0, 0);
        return std::make_tuple<double, double>(1, 1);
    }

    void drop()
    {

    }

    void step()
    {

    }
};