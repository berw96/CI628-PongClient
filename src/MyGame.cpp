#include "MyGame.h"

//Processes output from the server.
void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        switch (args.size()) {
        case 6:
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            game_data.playerBallFlag = stoi(args.at(4));
            game_data.enemyBallFlag = stoi(args.at(5));
            break;
        case 8:
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            game_data.playerBallFlag = stoi(args.at(4));
            game_data.enemyBallFlag = stoi(args.at(5));
            // detects WHICH ball is active and sets data accordingly
            if (game_data.playerBallFlag == 1) {
                game_data.playerBallX = stoi(args.at(6));
                game_data.playerBallY = stoi(args.at(7));
            }
            if (game_data.enemyBallFlag == 1) {
                game_data.enemyBallX = stoi(args.at(6));
                game_data.enemyBallY = stoi(args.at(7));
            }
            break;
        case 10:
            // case where everything is active
            game_data.playerX = stoi(args.at(0));
            game_data.enemyX = stoi(args.at(1));
            game_data.playerScore = stoi(args.at(2));
            game_data.enemyScore = stoi(args.at(3));
            game_data.playerBallFlag = stoi(args.at(4));
            game_data.enemyBallFlag = stoi(args.at(5));
            game_data.playerBallX = stoi(args.at(6));
            game_data.playerBallY = stoi(args.at(7));
            game_data.enemyBallX = stoi(args.at(8));
            game_data.enemyBallY = stoi(args.at(9));
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
    scoreFont       = TTF_OpenFont("res/fonts/UniversCondensed.ttf", 64);

    if (tankSurface != nullptr) {
        std::cout << "Loaded tank image successfully\n";
    }
    else {
        std::cout << "Could not load tank image\n";
    }
    if (bulletSurface != nullptr) {
        std::cout << "Loaded bullet image successfully\n";
    }
    else {
        std::cout << "Could not load bullet image\n";
    }
    if (scoreFont != nullptr) {
        std::cout << "Loaded font successfully\n";
    } 
    else {
        std::cout << "Could not load font\n";
    }
}

void MyGame::releaseResources() {
    delete tankSurface;
    delete bulletSurface;
    delete scoreFont;
    delete player_score_surface;
    delete enemy_score_surface;
    delete player_score_texture;
    delete enemy_score_texture;
    delete player_tank_texture;
    delete enemy_tank_texture;
    delete player_bullet_texture;
    delete enemy_bullet_texture;
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Render SDL_Rects if textures cannot be loaded
    if (player_tank_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &player.body);
    }
    if (enemy_tank_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &enemy.body);
    }
    if (player_bullet_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &player.ball->body);
    }
    if (enemy_bullet_texture == nullptr) {
        SDL_RenderDrawRect(renderer, &enemy.ball->body);
    }

    player_score_surface = TTF_RenderText_Blended(
        scoreFont,
        std::to_string(game_data.playerScore).c_str(),
        fontColor
    );

    enemy_score_surface = TTF_RenderText_Blended(
        scoreFont,
        std::to_string(game_data.enemyScore).c_str(),
        fontColor
    );

    int player_score_width, player_score_height;
    int enemy_score_width, enemy_score_height;

    SDL_QueryTexture(
        player_score_texture,
        NULL,
        NULL,
        &player_score_width,
        &player_score_height
    );

    SDL_QueryTexture(
        enemy_score_texture,
        NULL,
        NULL,
        &enemy_score_width,
        &enemy_score_height
    );

    SDL_Rect player_score_dst = {
        100,
        100,
        player_score_width,
        player_score_height
    };

    SDL_Rect enemy_score_dst = {
        700,
        100,
        enemy_score_width,
        enemy_score_height
    };

    player_tank_texture     = SDL_CreateTextureFromSurface(renderer, tankSurface);
    enemy_tank_texture      = SDL_CreateTextureFromSurface(renderer, tankSurface);
    player_bullet_texture   = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    enemy_bullet_texture    = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    player_score_texture    = SDL_CreateTextureFromSurface(renderer, player_score_surface);
    enemy_score_texture    = SDL_CreateTextureFromSurface(renderer, enemy_score_surface);

    SDL_RenderCopyEx(renderer, player_tank_texture, NULL, &player.body, 0.f, new SDL_Point(), SDL_FLIP_VERTICAL);
    SDL_RenderCopy(renderer, enemy_tank_texture, NULL, &enemy.body);
    // balls render conditonally based on their respective flags
    if (game_data.playerBallFlag == 1)
        SDL_RenderCopy(renderer, player_bullet_texture, NULL, &player.ball->body);
    if (game_data.enemyBallFlag == 1)
        SDL_RenderCopy(renderer, enemy_bullet_texture, NULL, &enemy.ball->body);
    SDL_RenderCopy(renderer, player_score_texture, NULL, &player_score_dst);
    SDL_RenderCopy(renderer, enemy_score_texture, NULL, &enemy_score_dst);
}