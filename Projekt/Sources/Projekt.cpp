#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "..\Headers\Player.h"
#include "..\Headers\Ball.h"
#include "..\Headers\Enemy_block.h"
#include "..\Headers\Button.h"
#include "..\Headers\menu.h"
#include "..\Headers\loader.h"
#include "..\Headers\game.h"

int main()              //0-exit, 1-easy, 2-medium, 3-hard, 4-controls, 5-points,
{
    std::vector <sf::Font> fonts = get_fonts();
    std::map <std::string, sf::Texture> textures = get_textures();
    std::map <std::string, sf::Texture> drops = get_drops();
    std::map <std::string, sf::SoundBuffer> samples = get_samples();

    sf::Music music;
    music.openFromFile("Samples/main_music.ogg");
    music.setVolume(25.f);
    music.setLoop(true);
    music.play();

    int menu_choose = 0;
    int level = 1;
    int points=0;
    menu_choose = menu(fonts, textures, samples);

    while (menu_choose!=0)
    {
        if (level == 4) { level = 1; }
        switch (menu_choose)
        {
            case 0:         //exit
            {
                return 0;
            }
            case 1:         //easy
            {
                int game_output=game(1, fonts, textures, drops, samples, level, points);
                if (game_output == 0) { menu_choose = 0; }                          //exit
                else if (game_output == 1) { menu_choose = menu_choose; }           //play_again
                else if (game_output == 2) { menu_choose = 10; }                    //open_menu
                else if (game_output == 3)
                {
                    level++;
                    if (level == 4) { menu_choose = 10; }
                    else { menu_choose = menu_choose; }
                }
                break;
            }
            case 2:         //meduim
            {
                int game_output = game(2, fonts, textures, drops, samples, level, points);
                if (game_output == 0) { menu_choose = 0; }                          //exit
                else if (game_output == 1) { menu_choose = menu_choose; }           //play_again
                else if (game_output == 2) { menu_choose = 10; }                    //open_menu
                else if (game_output == 3)
                {
                    level++;
                    if (level == 4) { menu_choose = 10; }
                    else { menu_choose = menu_choose; }
                }
                break;
            }
            case 3:         //hard
            {
                int game_output = game(3, fonts, textures, drops, samples, level, points);
                if (game_output == 0) { menu_choose = 0; }                          //exit
                else if (game_output == 1) { menu_choose = menu_choose; }           //play_again
                else if (game_output == 2) { menu_choose = 10; }                    //open_menu
                else if (game_output == 3) 
                {
                    level++; 
                    if (level == 4) { menu_choose = 10; }
                    else { menu_choose = menu_choose; }
                }  //next_level
                break;
            }
            case 4:         //controls
                controls(fonts, textures, samples);
                menu_choose = 10;
                break;
            case 5:         //points
            {
                points_table(fonts, textures, samples);
                menu_choose = 10;
                break;
            }
            case 10:        //menu again
            {
                menu_choose = menu(fonts, textures, samples);
                break;
            }
        }
    }
    return 0;
    
}