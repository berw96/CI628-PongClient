#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
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

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif