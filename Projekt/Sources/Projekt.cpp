#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <string>

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

    /*sf::Sound music;
    music.setBuffer(samples.at("button_touch"));
    music.setLoop(true);
    music.play();*/

    int menu_choose = 0;

    menu_choose = menu(fonts, textures, samples);

    while (menu_choose!=0)
    {
        switch (menu_choose)
        {
            case 0:         //exit
            {
                return 0;
            }
            case 1:         //easy
            {
                int game_output=game(1, fonts, textures, drops, samples, 1, 0);
                if (game_output == 0) { menu_choose = 0; }                  //exit
                else if (game_output == 1) { menu_choose = menu_choose; }   //play_again
                else if (game_output == 2) { menu_choose = 10; }            //open_menu
                break;
            }
            case 2:         //meduim
            {
                int game_output = game(2, fonts, textures, drops, samples, 1, 0);
                if (game_output == 0) { menu_choose = 0; }                  //exit
                else if (game_output == 1) { menu_choose = menu_choose; }   //play_again
                else if (game_output == 2) { menu_choose = 10; }            //open_menu
                break;
            }
            case 3:         //hard
            {
                int game_output = game(3, fonts, textures, drops, samples, 1, 0);
                if (game_output == 0) { menu_choose = 0; }                  //exit
                else if (game_output == 1) { menu_choose = menu_choose; }   //play_again
                else if (game_output == 2) { menu_choose = 10; }            //open_menu
                break;
            }
            case 4:         //controls
                controls(fonts, textures, samples);
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