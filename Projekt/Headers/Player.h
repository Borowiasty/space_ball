#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy_block.h"

struct Player_part : public sf::Sprite
{
    int index_;

    Player_part(const std::map<std::string, sf::Texture>& textures, int index, double pos_x, double pos_y);

    std::tuple<double, double> bounce(double speed_x, double speed_y, int shoud_be) const;
};

class Player
{
protected:
    std::vector <Player_part> pad_;
    std::vector <double> speed_{ 700.0, 0.0 };
    std::vector <double> changing_size_{ 0.0, 0.0 };
    std::vector <double> stop_{ 0.0, 0.0 };
public:
    Player() {}
    Player(const std::map<std::string, sf::Texture>& textures, double pos_x, double pos_y);

    const Player_part& pad(int index);
    int pad_size();

    void step(sf::Time time, const sf::Window& window);

    int cached_gift(std::vector <Enemy_block>& enemy_blocks);

    void make_it_bigger();

    void make_it_smaller();

    void make_it_faster();

    void make_it_slower();

    void make_it_stop();

    void make_it_move();

    bool get_speed_is_changed();
    double get_speed_time();

    bool get_size_is_changed();
    double get_changing_size_time();

    bool get_stop_is_changed();
    double get_stop_time();
};