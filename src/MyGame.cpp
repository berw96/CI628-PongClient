#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y  = stoi(args.at(0));
            game_data.player2Y  = stoi(args.at(1));
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
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;
        case SDLK_a:
            send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
            break;
        case SDLK_d:
            send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
            break;
        case SDLK_i:
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            break;
        case SDLK_k:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            break;
        case SDLK_j:
            send(event.type == SDL_KEYDOWN ? "J_DOWN" : "J_UP");
            break;
        case SDLK_l:
            send(event.type == SDL_KEYDOWN ? "L_DOWN" : "L_UP");
            break;
        case SDLK_SPACE:
            send(event.type == SDL_KEYDOWN ? "SPACE_DOWN" : "SPACE_UP");
            break;
    }
}

void MyGame::update() {
#pragma region P1
    p1.body.x   = game_data.player1X;
    p1.turret.x = p1.body.x + (p1.body.w);
    p1.body.y   = game_data.player1Y;
    p1.turret.y = p1.body.y + (int)(p1.body.h/3);
#pragma endregion

#pragma region P2
    //TODO: refactor p2 x-alignment to not use a magic number (int 800 repping the window width)
    p2.body.x   = game_data.player2X + 800 - p2.body.w;
    p2.turret.x = p2.body.x - (p2.body.w);
    p2.body.y   = game_data.player2Y;
    p2.turret.y = p2.body.y + (int)(p2.body.h/3);
#pragma endregion
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &p1.body);
    SDL_RenderDrawRect(renderer, &p1.turret);
    SDL_RenderDrawRect(renderer, &p2.body);
    SDL_RenderDrawRect(renderer, &p2.turret);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &p1.healthBar);
    SDL_RenderDrawRect(renderer, &p2.healthBar);
}