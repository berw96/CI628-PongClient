#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "PlayerObject.h"

// Data provided by the server
static struct GameData {
    int playerX = 0;
    int enemyX = 0;
    int playerScore = 0;
    int enemyScore = 0;
    int playerBallX = 0;
    int playerBallY = 0;
    int enemyBallX = 0;
    int enemyBallY = 0;
} game_data;

class MyGame {
    private:
        Player player = Player();
        Player enemy = Player();
        int texture_width = 100;
        int texture_height = 100;

        SDL_Surface* tankSurface;
        SDL_Surface* bulletSurface;
        SDL_Surface* player_score_surface;
        SDL_Surface* enemy_score_surface;

        SDL_Texture* player_tank_texture;
        SDL_Texture* enemy_tank_texture;
        SDL_Texture* player_bullet_texture;
        SDL_Texture* enemy_bullet_texture;
        SDL_Texture* player_score_texture;
        SDL_Texture* enemy_score_texture;

        TTF_Font* scoreFont;
        SDL_Color fontColor = {255, 255, 255, 255};

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
        void loadResources();
        void releaseResources();
};

#endif