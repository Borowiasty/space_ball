#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button : public sf::Sprite
{
protected:
    sf::Text contain_text_;
    sf::Sound sample_on_click_;
public:
    Button(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, const std::string text, const int size, int width, int height, const int position_x, const int position_y)
    {

        setTexture(textures.at("button"));

        setScale({ 2.3,1.2 });
        setOrigin(width / 2 - 85, height / 2 - 17);

        setPosition(position_x, position_y);
        contain_text_.setString(text);
        contain_text_.setFont(fonts[0]);
        contain_text_.setCharacterSize(size);
        contain_text_.setOrigin({ contain_text_.getGlobalBounds().width / 2 - 2, contain_text_.getGlobalBounds().height / 2 + 3 });
        contain_text_.setPosition(position_x, position_y);
        sample_on_click_.setBuffer(samples.at("button_touch"));
    }

    bool step(sf::Vector2i mouse_pos)
    {
        if (getGlobalBounds().contains({ static_cast<float> (mouse_pos.x), static_cast<float> (mouse_pos.y) })) 
        {
            sample_on_click_.play();
            return true; 
        }
        else { return false; }
    }

    sf::Text contain_text() { return contain_text_; }
};