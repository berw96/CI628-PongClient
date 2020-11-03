#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "PlayerObject.h"

static struct GameData {
    int playerY     = 0;
    int enemyY      = 0;
    int playerX     = 0;
    int enemyX      = 0;
    int ballX       = 0;
    int ballY       = 0;
} game_data;

class MyGame {
    private:
        Player player = Player();
        Player enemy = Player();

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif