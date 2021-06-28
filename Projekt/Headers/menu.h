#pragma once

int menu(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples);
void controls(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples);
int set_difficulty(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples);
void points_table(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples);
void save_my_points(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, int& points);
void to_file_saver(std::string user_name, int points);

int menu(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer> &samples)                                      //0-exit, 1-easy, 2-medium, 3-hard, 4-controls, 5-points, 
{
    sf::RenderWindow menu_window(sf::VideoMode(360, 600), "Space Ball");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, menu_window.getSize().x, menu_window.getSize().y));

    sf::Text header("-----------------\n-- Space  Ball --\n-----------------", fonts[0]);
    header.setCharacterSize(24);

    std::vector<Button> options;
    options.emplace_back(fonts, textures, samples, "Play", 20, 300, 80, menu_window.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, samples, "Controls", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, samples, "Difficulty", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, samples, "Scores", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, samples, "Exit", 20, 300, 80, menu_window.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

    int difficulty = 2;

    //save_my_points(fonts, textures, samples, x);

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
                else if (options[2].step(sf::Mouse::getPosition(menu_window))) { difficulty = set_difficulty(fonts, textures, samples); }
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

void controls(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples)
{
    sf::RenderWindow controls(sf::VideoMode(380, 600), "Space Ball");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, controls.getSize().x, controls.getSize().y));

    sf::Text header("------------------\n---- Controls ----\n------------------", fonts[0]);
    header.setCharacterSize(24);

    std::vector <sf::Text> controls_body;
    controls_body.emplace_back("To move, use left and\nright arrow keys", fonts[0]);
    controls_body[0].setCharacterSize(18);
    controls_body[0].setPosition(controls.getSize().x / 2 - controls_body[0].getGlobalBounds().width / 2, 100);
    controls_body.emplace_back("To pause the game,\nuse ESCape key", fonts[0]);
    controls_body[1].setCharacterSize(18);
    controls_body[1].setPosition(controls_body[0].getGlobalBounds().left, controls_body[0].getGlobalBounds().top + 50);
    controls_body.emplace_back("Every level will\nstart paused, to play\nYou have to use SPACE key", fonts[0]);
    controls_body[2].setCharacterSize(18);
    controls_body[2].setPosition(controls_body[1].getGlobalBounds().left, controls_body[1].getGlobalBounds().top + 50);

    Button exit_Button(fonts, textures, samples, "Exit", 20, 300, 80, controls.getSize().x / 2, controls.getSize().y - 40);

    while (controls.isOpen())
    {
        sf::Event event;
        while (controls.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                controls.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (exit_Button.step(sf::Mouse::getPosition(controls))) { controls.close(); }
            }
        }

        controls.clear();

        //drawing and display place
        controls.draw(background);
        controls.draw(header);
        for (auto &body : controls_body) { controls.draw(body); }
        controls.draw(exit_Button);
        controls.draw(exit_Button.contain_text());

        controls.display();
    }
}

int set_difficulty(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples)       //1 - easy, 2 - medium, 3 - hard 
{
    sf::RenderWindow menu_difficulty(sf::VideoMode(380, 600), "Space Ball");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, menu_difficulty.getSize().x, menu_difficulty.getSize().y));

    sf::Text header("------------------\n--- Difficulty ---\n------------------", fonts[0]);
    header.setCharacterSize(24);

    std::vector<Button> options;
    options.emplace_back(fonts, textures, samples, "Easy", 20, 300, 80, menu_difficulty.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, samples, "Medium", 20, 300, 80, menu_difficulty.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);
    options.emplace_back(fonts, textures, samples, "Hard", 20, 300, 80, menu_difficulty.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

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

void points_table(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples)
{
    sf::RenderWindow scores_of_the_time(sf::VideoMode(360, 600), "Space Ball");

    sf::Sprite background(textures.at("background"));
    background.setTextureRect(sf::IntRect(0, 0, scores_of_the_time.getSize().x, scores_of_the_time.getSize().y));

    std::fstream table_of_points;
    table_of_points.open("scores.txt", std::ios::in);

    std::vector <sf::Text> scores;
    sf::Text header("-----------------\n-- High Scores --\n-----------------", fonts[0]);
    header.setCharacterSize(24);

    std::string line;

    int counter = 0;

    while (std::getline(table_of_points, line))
    {
        counter++;
        if(counter < 10) { scores.emplace_back("0" + std::to_string(counter) + ". " + line, fonts[0]); }
        else { scores.emplace_back(std::to_string(counter) + ". " + line, fonts[0]); }
        
        scores[scores.size() - 1].setCharacterSize(23);
    }

    for (int i = 0; i < scores.size(); i++)
    {
        if (i == 0) { scores[i].setPosition(scores_of_the_time.getSize().x / 2 - 170, 80); }
        else { scores[i].setPosition(scores_of_the_time.getSize().x / 2  - 170, scores[i-1].getGlobalBounds().top + scores[i-1].getGlobalBounds().height + 7); }
    }

    Button exit_Button(fonts, textures, samples, "Exit", 20, 300, 80, scores_of_the_time.getSize().x / 2, scores_of_the_time.getSize().y - 40);

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
        scores_of_the_time.draw(header);
        for (auto score : scores) { scores_of_the_time.draw(score); }
        scores_of_the_time.draw(exit_Button);
        scores_of_the_time.draw(exit_Button.contain_text());

        scores_of_the_time.display();

    }
    table_of_points.close();
}

void save_my_points(const std::vector <sf::Font>& fonts, const std::map<std::string, sf::Texture>& textures, const std::map <std::string, sf::SoundBuffer>& samples, int& points)
{
    sf::RenderWindow save_points(sf::VideoMode(460, 600), "Space Ball");
    sf::Sprite background(textures.at("background"));
    sf::Text header;
    header.setCharacterSize(30);
    header.setFont(fonts[0]);
    header.setString("Save your points");
    header.setOrigin(header.getGlobalBounds().width / 2, header.getGlobalBounds().height / 2);
    header.setPosition(save_points.getSize().x / 2, header.getGlobalBounds().height / 2 + 20);
    background.setTextureRect(sf::IntRect(0, 0, save_points.getSize().x, save_points.getSize().y));

    std::vector<Button> options;
    options.emplace_back(fonts, textures, samples, "Save", 20, 300, 80, save_points.getSize().x / 2, 150);
    options.emplace_back(fonts, textures, samples, "Exit", 20, 300, 80, save_points.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50);

    sf::Text visual_points(std::to_string(points), fonts[0], 50);
    visual_points.setOrigin(visual_points.getGlobalBounds().width / 2, visual_points.getGlobalBounds().height / 2);
    visual_points.setPosition(sf::Vector2f(save_points.getSize().x / 2, options[options.size() - 1].getGlobalBounds().top + options[options.size() - 1].getGlobalBounds().height + 50));

    std::string user_name = "___";
    int actual = 0;

    sf::Clock clock;
    while (save_points.isOpen())
    {
        sf::Time elapsed = clock.restart();
        //check event
        sf::Event event;
        while (save_points.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                save_points.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (options[0].step(sf::Mouse::getPosition(save_points))) { if (actual == 3) { to_file_saver(user_name, points); save_points.close(); } }
                else if (options[1].step(sf::Mouse::getPosition(save_points))) { save_points.close(); }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q) { if (actual != 3) { user_name = user_name.substr(0, actual) + "Q" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::W) { if (actual != 3) { user_name = user_name.substr(0, actual) + "W" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::E) { if (actual != 3) { user_name = user_name.substr(0, actual) + "E" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::R) { if (actual != 3) { user_name = user_name.substr(0, actual) + "R" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::T) { if (actual != 3) { user_name = user_name.substr(0, actual) + "T" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::Y) { if (actual != 3) { user_name = user_name.substr(0, actual) + "Y" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::U) { if (actual != 3) { user_name = user_name.substr(0, actual) + "U" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::I) { if (actual != 3) { user_name = user_name.substr(0, actual) + "I" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::O) { if (actual != 3) { user_name = user_name.substr(0, actual) + "O" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::P) { if (actual != 3) { user_name = user_name.substr(0, actual) + "P" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::A) { if (actual != 3) { user_name = user_name.substr(0, actual) + "A" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::S) { if (actual != 3) { user_name = user_name.substr(0, actual) + "S" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::D) { if (actual != 3) { user_name = user_name.substr(0, actual) + "D" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::F) { if (actual != 3) { user_name = user_name.substr(0, actual) + "F" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::G) { if (actual != 3) { user_name = user_name.substr(0, actual) + "G" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::H) { if (actual != 3) { user_name = user_name.substr(0, actual) + "H" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::J) { if (actual != 3) { user_name = user_name.substr(0, actual) + "J" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::K) { if (actual != 3) { user_name = user_name.substr(0, actual) + "K" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::L) { if (actual != 3) { user_name = user_name.substr(0, actual) + "L" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::Z) { if (actual != 3) { user_name = user_name.substr(0, actual) + "Z" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::X) { if (actual != 3) { user_name = user_name.substr(0, actual) + "X" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::C) { if (actual != 3) { user_name = user_name.substr(0, actual) + "C" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::V) { if (actual != 3) { user_name = user_name.substr(0, actual) + "V" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::B) { if (actual != 3) { user_name = user_name.substr(0, actual) + "B" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::N) { if (actual != 3) { user_name = user_name.substr(0, actual) + "N" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::M) { if (actual != 3) { user_name = user_name.substr(0, actual) + "M" + user_name.substr(actual + 1, 3 - actual); actual++; } }
                else if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Backspace) { if (actual != 0) { user_name = user_name.substr(0, actual - 1) + "_" + user_name.substr(actual, 3 - actual); actual--; } }
                else if (event.key.code == sf::Keyboard::Enter) { if (actual == 3) { to_file_saver(user_name, points); save_points.close(); } }
            }
        }

        sf::Text visible_user_name(user_name + " : " + std::to_string(points), fonts[0]);
        visible_user_name.setOrigin(visible_user_name.getGlobalBounds().width / 2, visible_user_name.getGlobalBounds().height / 2);
        visible_user_name.setPosition(save_points.getSize().x / 2, header.getGlobalBounds().top + header.getGlobalBounds().height + 20);

        //window clear
        save_points.clear();

        //drawing and display place
        save_points.draw(background);
        save_points.draw(header);
        save_points.draw(visible_user_name);
        for (auto& option : options)
        {
            save_points.draw(option);
            save_points.draw(option.contain_text());
        }


        save_points.display();
    }
}

void to_file_saver(std::string user_name, int points)
{
    struct points_data
    {
        points_data(std::string name_arg, int points_arg)
        {
            name = name_arg;
            points = points_arg;
        }
        std::string name;
        int points;
    };

    std::string line;
    std::fstream output_file_body, output_file;
    output_file_body.open("scores.txt", std::ios::in);

    std::vector <points_data> output;
    while (std::getline(output_file_body, line))
    {
        output.emplace_back(line.substr(0, 3), std::stoi(line.substr(6)));
    }
    output.emplace_back(user_name, points);
    output_file_body.close();

    for (int i = 0; i < output.size(); i++)
    {
        int biggest_index = i;
        for (int j = i; j < output.size(); j++)
        {
            if (output[j].points > output[biggest_index].points) { biggest_index = j; }
        }
        std::swap(output[i], output[biggest_index]);
    }

    output_file.open("scores.txt", std::ios::out);

    for (int i = 0; i < 14; i++)
    {
        output_file << output[i].name + " : " + std::to_string(output[i].points);
        if (i != output.size() - 1) { output_file << std::endl; }
    }
    output_file.close();
}