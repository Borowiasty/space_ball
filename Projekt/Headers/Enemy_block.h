#pragma once
#include <SFML/Graphics.hpp>


class Enemy_block : public sf::Sprite
{
protected:
    int life_;
    int points_;
    bool can_be_destroyed_ = true;
    bool colision_ = true;
    int gift_ = 1;               //!to_be_changed
    double drop_speed = 100;
public:
    Enemy_block() : Sprite() {}
    Enemy_block(const int index, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, double pos_x, double pos_y) : Sprite()
    {
        switch (index)
        {
        case 0:     //default
            life_ = 1;
            points_ = 5;
            setTexture(textures.at("block"));
            break;
        case 1:     //harder block
            life_ = 2;
            points_ = 20;
            setTexture(textures.at("locked_block"));
            break;
        case 2:     //turboharder block
            life_ = 3;
            points_ = 100;
            setTexture(textures.at("locked_block"));
            setColor(sf::Color::Red);
            break;
        case 3:     //indestroable block
            life_ = -1;
            points_ = 0;
            setTexture(textures.at("block"));
            setColor(sf::Color(128, 128, 128));
            can_be_destroyed_ = 1;
            break;
        case 4:     //gift block 1
            life_ = 1;
            gift_ = 1;
            points_ = 50;
            break;
        case 5:     //gift block 2
            life_ = 1;
            gift_ = 2;
            points_ = 50;
            break;
        case 6:     //gift block 3
            life_ = 1;
            gift_ = 3;
            points_ = 50;
            break;
        case 7:     //gift block 4
            life_ = 1;
            gift_ = 4;
            points_ = 50;
            break;
        }
        setScale(0.977, 0.977);
        setPosition(pos_x, pos_y);
    }

    std::tuple<double, double> bounce(std::map < std::string, sf::Texture> &drops)
    {
        if (gift_ != 0) { drop(drops); }
        else { drop(drops); }
        return std::make_tuple<double, double>(1, 1);
    }

    int points() { return points_; }
    bool colision() { return colision_; }
    int gift() { return gift_; }

    void drop(std::map < std::string, sf::Texture> &drops)
    {
        switch (gift_)
        {
        case 1:
        {
            colision_ = false;
            setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
            setTextureRect(sf::IntRect(0, 0, 92, 92));
            setTexture(drops.at("larger_pad"));
            setScale(0.6, 0.6);
            break;
        }
        case 2:
            setTexture(drops.at("smaller_pad"));
            break;
        case 3:
            setTexture(drops.at("faster_pad"));
            break;
        case 4:
            setTexture(drops.at("stop_pad"));
            break;
        case 5:
            setTexture(drops.at("faster_ball"));
            break;
        case 6:
            setTexture(drops.at("slower_ball"));
            break;
        case 7:
            setTexture(drops.at("no_lose"));
            break;
        case 8:
            setTexture(drops.at("multi_ball"));
            break;
        case 9:
            setTexture(drops.at("500_points"));
            break;
        }
    }

    void step(sf::Time time, Player &player, sf::Window &window)
    {
        move(0 ,drop_speed * time.asSeconds());
    }
};