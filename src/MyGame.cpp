#include "MyGame.h"

//Processes output from the server.
void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        switch (args.size()) {
        case 4:
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            break;
            // this particular case has a problem - it only registers player balls, not enemy balls
        case 6:
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            game_data.playerBallX = stoi(args.at(4));
            game_data.playerBallY = stoi(args.at(5));
            break;
        case 8:
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            game_data.playerBallX = stoi(args.at(4));
            game_data.playerBallY = stoi(args.at(5));
            game_data.enemyBallX = stoi(args.at(6));
            game_data.enemyBallY = stoi(args.at(7));
            break;
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
    case SDLK_a:
        send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
        break;
    case SDLK_d:
        send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
        break;
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
#pragma endregion
    case SDLK_ESCAPE:
        exit(0);
    }
}

void MyGame::update() {
#pragma region PLAYER
    player.body.x = game_data.playerX;
    player.body.y = 580 - (player.body.h);
    player.ball->body.x = game_data.playerBallX;
    player.ball->body.y = game_data.playerBallY;
    player.score = game_data.playerScore;
#pragma endregion

#pragma region ENEMY
    enemy.body.x = game_data.enemyX;
    enemy.body.y = enemy.body.h - 80;
    enemy.ball->body.x = game_data.enemyBallX;
    enemy.ball->body.y = game_data.enemyBallY;
    enemy.score = game_data.enemyScore;
#pragma endregion
}

void MyGame::loadResources() {
    tankSurface     = IMG_Load("res/images/tank.png");
    bulletSurface   = IMG_Load("res/images/bullet.png");
    scoreFont       = TTF_OpenFont("res/fonts/UniversCondensed.ttf", 12);

    if (tankSurface != nullptr) {
        std::cout << "Loaded tank.png successfully\n";
    }
    else {
        std::cout << "Could not load tank.png\n";
    }
    if (bulletSurface != nullptr) {
        std::cout << "Loaded bullet.png successfully\n";
    }
    else {
        std::cout << "Could not load bullet.png\n";
    }
    if (scoreFont != nullptr) {
        std::cout << "Loaded font successfully.\n";
    } 
    else {
        std::cout << "Could not load font";
    }
}

void MyGame::releaseResources() {
    delete tankSurface;
    delete bulletSurface;
    delete scoreFont;
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (player_tank_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &player.body);
    }
    if (enemy_tank_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &enemy.body);
    }

    player_tank_texture     = SDL_CreateTextureFromSurface(renderer, tankSurface);
    enemy_tank_texture      = SDL_CreateTextureFromSurface(renderer, tankSurface);
    player_bullet_texture   = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    enemy_bullet_texture    = SDL_CreateTextureFromSurface(renderer, bulletSurface);

    SDL_RenderCopyEx(renderer, player_tank_texture, NULL, &player.body, 0.f, new SDL_Point(), SDL_FLIP_VERTICAL);
    SDL_RenderCopy(renderer, enemy_tank_texture, NULL, &enemy.body);

    //bullets need to be rendered conditionally based on whether they're spawned on the server.
}