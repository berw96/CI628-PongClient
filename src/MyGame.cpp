#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            /*game_data.player1X  = stoi(args.at(0));
            game_data.player2X  = stoi(args.at(1));*/
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
        /*case SDLK_a:
            send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
            break;
        case SDLK_d:
            send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
            break;*/
    }
}

void MyGame::update() {
    p1.body.y   = game_data.player1Y;
    p1.turret.y = p1.body.y + (int)(p1.body.h/3);
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &p1.body);
    SDL_RenderDrawRect(renderer, &p1.turret);
}