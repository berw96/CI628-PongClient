#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.playerY   = stoi(args.at(0));
            game_data.enemyY    = stoi(args.at(1));
            game_data.ballX     = stoi(args.at(2));
            game_data.ballY     = stoi(args.at(3));
        }
    } else {
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
#pragma region PLAYER_CONTROL
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        break;
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
#pragma endregion
#pragma region UI_NAVIGATION
    case SDLK_RETURN:
        send(event.type == SDL_KEYDOWN ? "RETURN_DOWN" : "RETURN_UP");
        break;
    case SDLK_UP:
        send(event.type == SDL_KEYDOWN ? "UP_DOWN" : "UP_UP");
        break;
    case SDLK_DOWN:
        send(event.type == SDL_KEYDOWN ? "DOWN_DOWN" : "DOWN_UP");
        break;
#pragma endregion
    }
}

void MyGame::update() {
#pragma region player
    player.body.y   = game_data.playerY;
    player.turret.x = player.body.x + (player.body.w);
    player.turret.y = player.body.y + (int)(player.body.h/3);
#pragma endregion

#pragma region enemy
    //TODO: refactor enemy x-alignment to not use a magic number (int 800 repping the window width)
    enemy.body.x   = 800 - enemy.body.w;
    enemy.body.y   = game_data.enemyY;
    enemy.turret.x = enemy.body.x - (enemy.body.w);
    enemy.turret.y = enemy.body.y + (int)(enemy.body.h/3);
#pragma endregion
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player.body);
    SDL_RenderDrawRect(renderer, &player.turret);
    SDL_RenderDrawRect(renderer, &enemy.body);
    SDL_RenderDrawRect(renderer, &enemy.turret);
}