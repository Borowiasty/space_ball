#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Enemy_block : public sf::Sprite
{
protected:
    int life_;
    int points_;
    bool can_be_destroyed_ = true;
    bool colision_ = true;
    int gift_;
    double drop_speed = 160;
    bool am_i_alive_ = true;
    sf::Sound sample_on_touch_;
public:
    Enemy_block() : Sprite() {}
    Enemy_block(const int index, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, double pos_x, double pos_y);

    std::tuple<double, double> bounce(std::map < std::string, sf::Texture>& drops);

    int points();
    bool colision();
    int gift();

    void drop(std::map < std::string, sf::Texture>& drops);

    void step(sf::Time time, sf::Window& window);

    void disapear();

    bool am_i_alive();
};