#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button : public sf::Sprite
{
protected:
    sf::Text contain_text_;
    sf::Sound sample_on_click_;
public:
    Button(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, const std::string text, const int size, int width, int height, const int position_x, const int position_y);

    bool step(sf::Vector2i mouse_pos);

    sf::Text contain_text();
};