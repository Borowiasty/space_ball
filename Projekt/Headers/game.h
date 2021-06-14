#pragma once

std::tuple<std::vector <Enemy_block>, Player, Ball> level_1(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, sf::Window& window)
{
    Player player(textures, window.getSize().x / 2 - 96, window.getSize().y - 50);
    Ball ball(textures, window);
    std::vector <Enemy_block> enemy_blocks;
    enemy_blocks.emplace_back(0, fonts, textures, 0, 0);
    double sizer = enemy_blocks[0].getGlobalBounds().width;

    int amounmt_of = 8;

    enemy_blocks[0].setPosition((window.getSize().x - (amounmt_of * sizer)) / 2, 0);

    for (int i = 1; i <= 4; i++)
    {
        if (i != 1)
            enemy_blocks.emplace_back(0, fonts, textures, enemy_blocks[0].getGlobalBounds().left, (enemy_blocks[0].getGlobalBounds().top + enemy_blocks[0].getGlobalBounds().height) * (i - 1));

        for (int j = 1; j < amounmt_of; j++)
        {
            enemy_blocks.emplace_back(0, fonts, textures, enemy_blocks[enemy_blocks.size() - 1].getGlobalBounds().left + enemy_blocks[enemy_blocks.size() - 1].getGlobalBounds().width, enemy_blocks[enemy_blocks.size() - 1].getGlobalBounds().top);
        }
    }

    return std::tuple<std::vector <Enemy_block>, Player, Ball>(enemy_blocks, player, ball);
}

//std::tuple<std::vector <Enemy_block>, Player, Ball> level_2(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, sf::Window& window)
//{
//    Player player(textures, window.getSize().x / 2 - 96, window.getSize().y - 50);
//    Ball ball(textures, window);
//    std::vector <Enemy_block> enemy_blocks;
//    enemy_blocks.emplace_back(0, fonts, textures, 100, 100);
//}
//
//std::tuple<std::vector <Enemy_block>, Player, Ball> level_3(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, sf::Window& window)
//{
//    Player player(textures, window.getSize().x / 2 - 96, window.getSize().y - 50);
//    Ball ball(textures, window);
//    std::vector <Enemy_block> enemy_blocks;
//    enemy_blocks.emplace_back(0, fonts, textures, 100, 100);
//}
//
//std::tuple<std::vector <Enemy_block>, Player, Ball> level_4(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, sf::Window& window)
//{
//    Player player(textures, window.getSize().x / 2 - 96, window.getSize().y - 50);
//    Ball ball(textures, window);
//    std::vector <Enemy_block> enemy_blocks;
//    enemy_blocks.emplace_back(0, fonts, textures, 100, 100);
//}
//
//std::tuple<std::vector <Enemy_block>, Player, Ball> level_5(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, sf::Window& window)
//{
//    Player player(textures, window.getSize().x / 2 - 96, window.getSize().y - 50);
//    Ball ball(textures, window);
//    std::vector <Enemy_block> enemy_blocks;
//    enemy_blocks.emplace_back(0, fonts, textures, 100, 100);
//}

int in_game_menu_pause(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, int points)     //0 - normal, 1 - replay, 2 - exit_to_menu, 3 - exit_to_dekstop
{
    sf::RenderWindow pause_window(sf::VideoMode(360, 600), "Pause");
    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, pause_window.getSize().x, pause_window.getSize().y));

    std::vector<Button> options;
    options.emplace_back(fonts, textures, "Continue", 20, 300, 80, pause_window.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, "Replay", 20, 300, 80, pause_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Exit to menu", 20, 300, 80, pause_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Exit to desktop", 20, 300, 80, pause_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

    sf::Text visual_points(std::to_string(points), fonts[0], 50);
    visual_points.setOrigin(visual_points.getGlobalBounds().width / 2, visual_points.getGlobalBounds().height / 2);
    visual_points.setPosition(sf::Vector2f(pause_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50));

    sf::Clock clock;
    //gaming
    while (pause_window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        //check event
        sf::Event event;
        while (pause_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                pause_window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (options[0].step(sf::Mouse::getPosition(pause_window))) { pause_window.close(); return 0; }
                else if (options[1].step(sf::Mouse::getPosition(pause_window))) { pause_window.close(); return 1; }
                else if (options[2].step(sf::Mouse::getPosition(pause_window))) { pause_window.close(); return 2; }
                else if (options[3].step(sf::Mouse::getPosition(pause_window))) { pause_window.close(); return 3; }
            }
        }

        //window clear
        pause_window.clear();

        //drawing and display place
        pause_window.draw(background);
        pause_window.draw(visual_points);
        for (auto& option : options)
        {
            pause_window.draw(option);
            pause_window.draw(option.contain_text());
        }


        pause_window.display();
    }
}

//int in_game_menu_win(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)
//{
//
//}
//
//int in_game_menu_loose(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)
//{
//
//}

int game(const int difficulty, const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, std::map < std::string, sf::Texture> &drops, const int level, int points)                  //0-stop, 1-play_again, 2-open_menu
{
    sf::RenderWindow game_window(sf::VideoMode(1000, 700), "Space Ball");
    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, game_window.getSize().x, game_window.getSize().y));
    //render game
    std::vector <Enemy_block> enemy_blocks;
    Player player;
    Ball ball;
    bool game_working = false;
    bool win = false;
    switch (level)
    {
    case 1:
    {
        std::tie(enemy_blocks, player, ball) = level_1(difficulty, fonts, textures, game_window);
        break;
    }
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }


    sf::Clock clock;
    //gaming
    while (game_window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        //check event
        sf::Event event;
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game_window.close();
                return 0;
            }

            if (!game_working)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space) { game_working = true; }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    switch (in_game_menu_pause(fonts, textures, points))
                    {
                    case 0:
                        break;
                    case 1:
                        game_window.close();
                        return 1;
                        break;
                    case 2:
                        game_window.close();
                        return 2;
                        break;
                    case 3:
                        game_window.close();
                        return 0;
                        break;
                    }
                    clock.restart();
                }
            }
        }

        //window clear
        game_window.clear();

        //actions
        if (game_working)
        {
            player.step(elapsed, game_window);
            if (ball.step(elapsed, game_window, player, enemy_blocks, drops, points))
            {
                win = false;
                break;
            }
            for (auto &drop : enemy_blocks)
            {
                if (!drop.colision())
                {
                    std::cerr << "UwU" << std::endl;
                    drop.step(elapsed, player, game_window);
                }
            }
        }

        //drawing and display place
        sf::Text visible_points(std::to_string(points), fonts[0], 50);
        visible_points.setPosition(10, 10);
        game_window.draw(background);
        for (int i = 0; i <= player.pad_size() - 1; i++)
        {
            game_window.draw(player.pad(i));
        }
        for (auto& enemy_block : enemy_blocks)
        {
            game_window.draw(enemy_block);
        }
        game_window.draw(ball);
        game_window.draw(visible_points);
        game_window.display();
    }
    if (win) {}
    //else { in_game_menu_loose(fonts, textures); }
}