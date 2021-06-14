#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Enemy_block.h"

class Ball : public sf::Sprite
{
protected:
    double speed_x_ = 200;
    double speed_y_ = 200;
    double begin_speed_ = sqrt(pow(300, 2) * pow(300, 2));
public:
    Ball() : Sprite() {}

    Ball(const std::map<std::string, sf::Texture>& textures, sf::Window& window) : Sprite()
    {
        setTexture(textures.at("blue_ball"));
        setScale(0.5, 0.5);
        setPosition(window.getSize().x / 2 - getGlobalBounds().width / 2, window.getSize().y / 2 - getGlobalBounds().height / 2);
    }

    bool step(sf::Time time, const sf::Window& window, Player& player, std::vector <Enemy_block>& enemy_blocks)
    {
        if (getGlobalBounds().left <= 0) { speed_x_ *= -1; move(0.1, 0); }
        else if (getGlobalBounds().left + getGlobalBounds().width >= window.getSize().x) { speed_x_ *= -1; move(-0.1, 0); }

        if (getGlobalBounds().top <= 0) { speed_y_ *= -1; move(0, 0.1); }
        else if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y) { return true; }

        for (int i = 0; i < player.pad_size(); i++)
        {
            if (getGlobalBounds().intersects(player.pad(i).getGlobalBounds()))
            {
                double x, y;
                std::tie(x, y) = player.pad(i).bounce(speed_x_, speed_y_);
                move(x / 100, y / 100);
                speed_x_ = x;
                speed_y_ = y;

                while (sqrt(pow(speed_x_, 2) * pow(speed_y_, 2)) > begin_speed_)
                {
                    if (speed_x_ > 0) { speed_x_ -= 0.2; }
                    else { speed_x_ += 0.2; }
                    if (speed_y_ > 0) { speed_y_ -= 0.2; }
                    else { speed_y_ += 0.2; }
                }
                std::cout << speed_x_ << " " << speed_y_ << std::endl;
                break;
            }
        }

        for (auto& enemy_block : enemy_blocks)
        {
            if (getGlobalBounds().intersects(enemy_block.getGlobalBounds())) 
            {
                double approxima = 1.5;
                if (getGlobalBounds().left <= enemy_block.getGlobalBounds().left + enemy_block.getGlobalBounds().width && getGlobalBounds().left >= enemy_block.getGlobalBounds().left + enemy_block.getGlobalBounds().width - approxima) { speed_x_ *= -1; }
                else if (getGlobalBounds().left + getGlobalBounds().width >= enemy_block.getGlobalBounds().left && getGlobalBounds().left + getGlobalBounds().width <= enemy_block.getGlobalBounds().left + approxima) { speed_y_ *= -1; }
                else if (getGlobalBounds().top <= enemy_block.getGlobalBounds().top + enemy_block.getGlobalBounds().height && getGlobalBounds().top >= enemy_block.getGlobalBounds().top + enemy_block.getGlobalBounds().height - approxima) { speed_y_ *= -1; }
                else if (getGlobalBounds().top + getGlobalBounds().height >= enemy_block.getGlobalBounds().top && getGlobalBounds().top + getGlobalBounds().height <= enemy_block.getGlobalBounds().top + approxima) { speed_y_ *= -1; }

                enemy_block.bounce(); 
                break;
            }
        }

        move(speed_x_ * time.asSeconds(), speed_y_ * time.asSeconds());
        return false;
    }

    double speed_x() { return speed_x_; }
    double speed_y() { return speed_y_; }

};