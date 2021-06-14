#pragma once

std::map<std::string, sf::Texture> get_textures()
{
    std::map<std::string, sf::Texture> textures;
    sf::Texture texture;

    texture.loadFromFile("Textures/background_brown.png");
    texture.setRepeated(true);
    textures["background"] = texture;

    texture.loadFromFile("Textures/ball_blue_large.png");
    texture.setSmooth(true);
    textures["blue_ball"] = texture;

    texture.loadFromFile("Textures/ball_red_large.png");
    texture.setSmooth(true);
    textures["red_ball"] = texture;

    texture.loadFromFile("Textures/block_large.png");
    textures["block"] = texture;

    texture.loadFromFile("Textures/block_locked_large.png");
    textures["locked_block"] = texture;

    texture.loadFromFile("Textures/button_yellow.png");
    textures["button"] = texture;

    texture.loadFromFile("Textures/laser.png");
    texture.setSmooth(true);
    textures["pad"] = texture;

    return textures;
}

std::vector <sf::Font> get_fonts()
{
    sf::Font font;
    std::vector <sf::Font> fonts;

    font.loadFromFile("Kenney_Blocks.ttf");
    fonts.emplace_back(font);

    return fonts;
}