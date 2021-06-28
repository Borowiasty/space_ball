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

    texture.loadFromFile("Textures/block_gift.png");
    textures["block_gift"] = texture;

    texture.loadFromFile("Textures/button_yellow.png");
    textures["button"] = texture;

    texture.loadFromFile("Textures/laser.png");
    texture.setSmooth(true);
    textures["pad"] = texture;

    return textures;
}

std::map < std::string, sf::Texture> get_drops()
{
    std::map<std::string, sf::Texture> drops;
    sf::Texture drop;

    drop.loadFromFile("Textures/drop_textures/larger_pad.png");
    drop.setSmooth(true);
    drops["larger_pad"] = drop;

    drop.loadFromFile("Textures/drop_textures/smaller_pad.png");
    drop.setSmooth(true);
    drops["smaller_pad"] = drop;

    drop.loadFromFile("Textures/drop_textures/faster_pad.png");
    drop.setSmooth(true);
    drops["faster_pad"] = drop;

    drop.loadFromFile("Textures/drop_textures/stop_pad.png");
    drop.setSmooth(true);
    drops["stop_pad"] = drop;

    drop.loadFromFile("Textures/drop_textures/faster_ball.png");
    drop.setSmooth(true);
    drops["faster_ball"] = drop;

    drop.loadFromFile("Textures/drop_textures/slower_ball.png");
    drop.setSmooth(true);
    drops["slower_ball"] = drop;

    drop.loadFromFile("Textures/drop_textures/no_lose.png");
    drop.setSmooth(true);
    drops["no_lose"] = drop;

    drop.loadFromFile("Textures/drop_textures/multi_ball.png");
    drop.setSmooth(true);
    drops["multi_ball"] = drop;

    drop.loadFromFile("Textures/drop_textures/500_points.png");
    drop.setSmooth(true);
    drops["500_points"] = drop;

    return drops;
}

std::vector <sf::Font> get_fonts()
{
    sf::Font font;
    std::vector <sf::Font> fonts;

    font.loadFromFile("Topaz8-xxO8.ttf");
    fonts.emplace_back(font);

    return fonts;
}

std::map<std::string, sf::SoundBuffer> get_samples()
{
    sf::SoundBuffer sample;
    std::map <std::string, sf::SoundBuffer> samples;

    sample.loadFromFile("Samples/button_touch.ogg");
    samples["button_touch"] = sample;

    sample.loadFromFile("Samples/destroyed_gift.ogg");
    samples["destroyed_gift"] = sample;

    sample.loadFromFile("Samples/destroyed_heavy_block.ogg");
    samples["destroyed_heavy_block"] = sample;

    sample.loadFromFile("Samples/destroyed_normal_block.ogg");
    samples["destroyed_normal_block"] = sample;

    sample.loadFromFile("Samples/idestroyable_bounce.ogg");
    samples["idestroyable_bounce"] = sample;

    sample.loadFromFile("Samples/pad_bounce.ogg");
    samples["pad_bounce"] = sample;

    return samples;
}