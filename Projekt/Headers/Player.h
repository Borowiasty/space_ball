#pragma once
#include <SFML/Graphics.hpp>

struct Player_part : public sf::Sprite
{
    int index_;

    Player_part(const std::map<std::string, sf::Texture>& textures, int index, double pos_x, double pos_y) : Sprite()
    {
        index_ = index;
        setTexture(textures.at("pad"));
        switch (index_)
        {
        case 0:
            setTextureRect(sf::IntRect(0, 0, 10, getGlobalBounds().height));
            break;
        case 1:
            setTextureRect(sf::IntRect(13, 0, 33, getGlobalBounds().height));
            break;
        case 2:
            setTextureRect(sf::IntRect(13, 0, 60, getGlobalBounds().height));
            break;
        case 3:
            setTextureRect(sf::IntRect(13, 0, 33, getGlobalBounds().height));
            break;
        case 4:
            setTextureRect(sf::IntRect(getGlobalBounds().width - 10, 0, 10, getGlobalBounds().height));
            break;
        }
        setScale({ 1.5,1.5 });
        setPosition(sf::Vector2f(pos_x, pos_y));
    }

    std::tuple<double, double> bounce(double speed_x, double speed_y, int shoud_be) const
    {
        switch (index_)
        {
        case 0:
            if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * -1.5, speed_y * -0.5); }
            else { return std::make_tuple<double, double>(speed_x * 1.5, -0.5); }
            break;
        case 1:
            if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * -1.2, speed_y * -0.8); }
            else { return std::make_tuple<double, double>(speed_x * 1.1, speed_y * -0.9); }
            break;
        case 2:
            if (abs(speed_x) < abs(speed_y)) { return std::make_tuple<double, double>(((shoud_be * 1.0) - 10) * (speed_x / abs(speed_x)), shoud_be + 10*(-1.0)); }
            else if (abs(speed_x) > abs(speed_y)) { return std::make_tuple<double, double>(((shoud_be * 1.0) + 10) * (speed_x / abs(speed_x)), shoud_be - 10 * (-1.0)); }
            else { return std::make_tuple<double, double>((shoud_be * 1.0) * (speed_x / abs(speed_x)), shoud_be * (-1.0)); }
            break;
        case 3:
            if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * 1.2, speed_y * -0.8); }
            else { return std::make_tuple<double, double>(speed_x * -1.1, speed_y * -0.9); }
            break;
        case 4:
            if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * 1.5, speed_y * -0.5); }
            else { return std::make_tuple<double, double>(speed_x * -1.5, speed_y * -0.5); }
            break;
        default:
            return std::make_tuple<double, double>(speed_x *1.0, speed_y*1.0);
        }
    }
};

class Player
{
protected:
    std::vector <Player_part> pad_;
    int speed_ = 700;
public:
    Player() {}
    Player(const std::map<std::string, sf::Texture>& textures, double pos_x, double pos_y)
    {
        pad_.emplace_back(textures, 0, pos_x, pos_y);
        pad_.emplace_back(textures, 1, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
        pad_.emplace_back(textures, 2, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
        pad_.emplace_back(textures, 3, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
        pad_.emplace_back(textures, 4, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
    }

    const Player_part &pad(int index) { return pad_[index]; }
    int pad_size() { return pad_.size(); }

    void step(sf::Time time, const sf::Window& window)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width < window.getSize().x)
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(speed_ * time.asSeconds(), 0);
                }
            }
            else
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(-0.5, 0);
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (pad_[0].getGlobalBounds().left > 0)
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(-speed_ * time.asSeconds(), 0);
                }
            }
            else
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(0.5, 0);
                }
            }
        }
    }
};