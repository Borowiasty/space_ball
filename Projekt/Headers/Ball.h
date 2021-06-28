#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Enemy_block.h"

class Ball : public sf::Sprite
{
protected:
    double speed_x_ = 300;
    double speed_y_ = 300;
    double begin_speed_ = sqrt(pow(speed_x_, 2) + pow(speed_y_, 2));
    int changed_speed_ = 0;
    double timer_changed_speed_ = 0.0;
    bool do_loose_on_bottom_bounce_ = 1; 
    double timer_no_loose_ = 0.0;
    sf::Sound sample_on_touch_;

    void what_to_do_loose_on_bottom_bounce_(bool arg) { do_loose_on_bottom_bounce_ = arg; }
public:
    Ball() : Sprite() {}

    Ball(const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, sf::Window& window, const int difficulty);

    bool step(sf::Time time, const sf::Window& window, Player& player, std::vector <Enemy_block>& enemy_blocks, std::map < std::string, sf::Texture>& drops, int& points);

    bool handle_bottom_touch();

    double speed_x();
    double speed_y();
    void set_no_lose();
    double get_timer_no_loose();
    bool get_loose_is_changed();

    int changed_speed();
    double get_timer_changed_speed();

    void make_it_faster_();
    void make_it_slower_();
};