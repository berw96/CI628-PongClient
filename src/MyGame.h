#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

static struct GameData {
    int player1X        = 0;
    int player2X        = 0;
    int player1Y        = 0;
    int player2Y        = 0;
    int player1Health   = 0;
    int player2Health   = 0;
    int ballX           = 0;
    int ballY           = 0;
} game_data;

struct PlayerObject {
    SDL_Rect body   = {
        0, 
        0, 
        30, 
        30
    };
    SDL_Rect turret = {
        body.w,
        0,
        body.w,
        body.h / 3
    };
    SDL_Rect healthBar = {
        0,
        0,
        50,
        10
    };
    int score       = 0;
    bool hasFired   = false;
};
typedef PlayerObject Player;

class MyGame {

    private:
        Player p1 = Player();

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif