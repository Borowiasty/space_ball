#pragma once

int menu(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures);
void controls(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures);
int set_difficulty(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures);
void points_table(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures);

int menu(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)                                      //0-exit, 1-easy, 2-medium, 3-hard, 4-controls, 5-points, 
{
    sf::RenderWindow menu_window(sf::VideoMode(360, 600), "Menu");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, menu_window.getSize().x, menu_window.getSize().y));

    sf::Text header("------------------------\n----- Space Ball -----\n------------------------", fonts[0]);
    header.setCharacterSize(24);

    std::vector<Button> options;
    options.emplace_back(fonts, textures, "Play", 20, 300, 80, menu_window.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, "Controls", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Difficulty", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Scores of the time", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Exit", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

    int difficulty = 2;

    while (menu_window.isOpen())
    {
        sf::Event event;
        while (menu_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                menu_window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (options[0].step(sf::Mouse::getPosition(menu_window))) { menu_window.close(); return difficulty; }
                else if (options[1].step(sf::Mouse::getPosition(menu_window))) { menu_window.close(); return 4; }
                else if (options[2].step(sf::Mouse::getPosition(menu_window))) { difficulty = set_difficulty(fonts, textures); }
                else if (options[3].step(sf::Mouse::getPosition(menu_window))) { menu_window.close(); return 5; }
                else if (options[4].step(sf::Mouse::getPosition(menu_window))) { menu_window.close(); return 0; }
            }
        }


        menu_window.clear();

        //drawing and display place

        menu_window.draw(background);
        menu_window.draw(header);
        for (auto option : options)
        {
            menu_window.draw(option);
            menu_window.draw(option.contain_text());
        }

        menu_window.display();

    }
    menu_window.close();
}

void controls(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)
{

}

int set_difficulty(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)       //1 - easy, 2 - medium, 3 - hard 
{
    sf::RenderWindow menu_difficulty(sf::VideoMode(360, 600), "Diffuiculty");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, menu_difficulty.getSize().x, menu_difficulty.getSize().y));

    sf::Text header("------------------------\n----- Space Ball -----\n------------------------", fonts[0]);
    header.setCharacterSize(24);

    std::vector<Button> options;
    options.emplace_back(fonts, textures, "Easy", 20, 300, 80, menu_difficulty.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, "Medium", 20, 300, 80, menu_difficulty.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, "Hard", 20, 300, 80, menu_difficulty.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

    while (menu_difficulty.isOpen())
    {
        sf::Event event;
        while (menu_difficulty.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                menu_difficulty.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (options[0].step(sf::Mouse::getPosition(menu_difficulty))) { menu_difficulty.close(); return 1; }
                else if (options[1].step(sf::Mouse::getPosition(menu_difficulty))) { menu_difficulty.close(); return 2; }
                else if (options[2].step(sf::Mouse::getPosition(menu_difficulty))) { menu_difficulty.close(); return 3; }
            }
        }


        menu_difficulty.clear();

        //drawing and display place

        menu_difficulty.draw(background);
        menu_difficulty.draw(header);
        for (auto option : options)
        {
            menu_difficulty.draw(option);
            menu_difficulty.draw(option.contain_text());
        }

        menu_difficulty.display();

    }
    menu_difficulty.close();
}

void points_table(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures)
{
    sf::RenderWindow scores_of_the_time(sf::VideoMode(360, 600), "Scores of the time");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, scores_of_the_time.getSize().x, scores_of_the_time.getSize().y));

    std::fstream table_of_points;
    table_of_points.open("scores.txt", std::ios::in);

    std::vector <sf::Text> scores;

    std::string line;

    scores.emplace_back("------------------------\n--- Scores  of  the  time ---\n------------------------", fonts[0]);
    scores[0].setCharacterSize(20);

    while (std::getline(table_of_points, line))
    {
        scores.emplace_back(line, fonts[0]);
        if (scores.size() == 1)
        {
            scores[0].setPosition(0, 50);
        }
        else
        {
            scores[scores.size() - 1].setPosition(sf::Vector2f(0, scores[scores.size() - 2].getGlobalBounds().top + scores[scores.size() - 2].getGlobalBounds().height + 7));
            scores[scores.size() - 1].setCharacterSize(20);
        }
    }

    Button exit_Button(fonts, textures, "Exit", 20, 300, 80, scores_of_the_time.getSize().x / 2, scores_of_the_time.getSize().y - 30);

    while (scores_of_the_time.isOpen())
    {
        sf::Event event;
        while (scores_of_the_time.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                scores_of_the_time.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (exit_Button.step(sf::Mouse::getPosition(scores_of_the_time))) { scores_of_the_time.close(); }
            }
        }


        scores_of_the_time.clear();

        //drawing and display place
        scores_of_the_time.draw(background);
        for (auto score : scores) { scores_of_the_time.draw(score); }
        scores_of_the_time.draw(exit_Button);
        scores_of_the_time.draw(exit_Button.contain_text());

        scores_of_the_time.display();

    }
    table_of_points.close();
}