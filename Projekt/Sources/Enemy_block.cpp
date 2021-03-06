#pragma once
#include "../Headers/Enemy_block.h"

Enemy_block::Enemy_block(const int index, const std::vector<sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map<std::string, sf::SoundBuffer>& samples, double pos_x, double pos_y) : Sprite()
{
    switch (index)
    {
    case 0:     //default
        life_ = 1;
        points_ = 5;
        gift_ = 0;
        setTexture(textures.at("block"));
        sample_on_touch_.setBuffer(samples.at("destroyed_normal_block"));
        break;
    case 1:     //harder block
        life_ = 2;
        points_ = 20;
        gift_ = 0;
        setTexture(textures.at("locked_block"));
        sample_on_touch_.setBuffer(samples.at("idestroyable_bounce"));
        break;
    case 2:     //turboharder block
        life_ = 3;
        points_ = 100;
        gift_ = 0;
        setTexture(textures.at("locked_block"));
        setColor(sf::Color::Red);
        sample_on_touch_.setBuffer(samples.at("destroyed_heavy_block"));
        break;
    case 3:     //indestroable block
        life_ = -1;
        can_be_destroyed_ = false;
        am_i_alive_ = false;
        points_ = 0;
        gift_ = 0;
        setTexture(textures.at("block"));
        setColor(sf::Color(128, 128, 128));
        sample_on_touch_.setBuffer(samples.at("idestroyable_bounce"));
        can_be_destroyed_ = 1;
        break;
    case 4:     //gift block larger pad
        life_ = 1;
        gift_ = 1;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 5:     //gift block smaller pad
        life_ = 1;
        gift_ = 2;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 6:     //gift block faster pad
        life_ = 1;
        gift_ = 3;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 7:     //gift block stop pad
        life_ = 1;
        gift_ = 4;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 8:     //gift block faster ball
        life_ = 1;
        gift_ = 5;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 9:     //gift block slower ball
        life_ = 1;
        gift_ = 6;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 10:     //gift block no loose
        life_ = 1;
        gift_ = 7;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 11:     //gift block multi ball
        life_ = 1;
        gift_ = 8;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    case 12:     //gift block 500 points
        life_ = 1;
        gift_ = 9;
        points_ = 50;
        setTexture(textures.at("block_gift"));
        //setColor(sf::Color(255, 228, 20));
        sample_on_touch_.setBuffer(samples.at("destroyed_gift"));
        break;
    }
    setScale(0.977, 0.977);
    setPosition(pos_x, pos_y);
}

std::tuple<double, double> Enemy_block::bounce(std::map<std::string, sf::Texture>& drops)
{
    if (can_be_destroyed_) { life_--; }
    sample_on_touch_.play();
    if (gift_ != 0) { drop(drops); }
    else
    {
        if (life_ == 0) { disapear(); }
    }
    return std::make_tuple<double, double>(-1, -1);
}

int Enemy_block::points() { return points_; }

bool Enemy_block::colision() { return colision_; }

int Enemy_block::gift() { return gift_; }

void Enemy_block::drop(std::map<std::string, sf::Texture>& drops)
{
    am_i_alive_ = false;
    switch (gift_)
    {
    case 1:
    {
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("larger_pad"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    }
    case 2:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("smaller_pad"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 3:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("faster_pad"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 4:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("stop_pad"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 5:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("faster_ball"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 6:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("slower_ball"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 7:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("no_lose"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 8:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("multi_ball"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    case 9:
        colision_ = false;
        setPosition(getGlobalBounds().left + (getGlobalBounds().width / 4), getGlobalBounds().top);
        setTextureRect(sf::IntRect(0, 0, 92, 92));
        setTexture(drops.at("500_points"));
        setColor(sf::Color::White);
        setScale(0.6, 0.6);
        break;
    }
}

void Enemy_block::step(sf::Time time, sf::Window& window)
{
    move(0, drop_speed * time.asSeconds());
    if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y) { disapear(); }
}

void Enemy_block::disapear()
{
    setScale(0, 0);
    setPosition(2000, 2000);
    colision_ = true;
    am_i_alive_ = false;
}

bool Enemy_block::am_i_alive() { return am_i_alive_; }