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
    } 
    else if (cmd == "BALL_HIT_BAT1" || cmd == "BALL_HIT_BAT2") {
        std::cout << "Received: " << cmd << std::endl;
        Mix_PlayChannel(-1, bullet_hit_tank_sfx, 0);
    }
    else if (
        cmd == "HIT_WALL_DOWN"  ||
        cmd == "HIT_WALL_UP"    ||
        cmd == "HIT_WALL_LEFT"  ||
        cmd == "HIT_WALL_RIGHT"
        ) {
        std::cout << "Received: " << cmd << std::endl;
        Mix_PlayChannel(-1, bullet_hit_wall_sfx, 0);
    }
    else if (
        (cmd == "BAT1_FIRED_BALL" && game_data.playerBallFlag == 0) || 
        (cmd == "BAT2_FIRED_BALL" && game_data.enemyBallFlag == 0)) {
        std::cout << "Received: " << cmd << std::endl;
        Mix_PlayChannel(-1, player_fire_sfx, 0);
    }
    else if (cmd == "PLAYER1_CONNECT") {
        std::cout << "Received: " << cmd << std::endl;
        this->connectionNumber = 1;
    }
    else if (cmd == "PLAYER2_CONNECT") {
        std::cout << "Received: " << cmd << std::endl;
        this->connectionNumber = 2;
    }
    else if (cmd == "PLAYER1_QUIT") {
        std::cout << "Received: " << cmd << std::endl;
        SDL_Delay(200);
        exit(0);
    }
    else if (cmd == "PLAYER2_QUIT") {
        std::cout << "Received: " << cmd << std::endl;
        SDL_Delay(200);
        exit(0);
    }
    else {
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (this->connectionNumber) {
    case 1:
        switch (event.key.keysym.sym) {
        case SDLK_a:
            send(event.type == SDL_KEYDOWN ? "A_PLAYERDOWN" : "A_PLAYERUP");
            break;
        case SDLK_d:
            send(event.type == SDL_KEYDOWN ? "D_PLAYERDOWN" : "D_PLAYERUP");
            break;
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_PLAYERDOWN" : "W_PLAYERUP");
            break;
        case SDLK_ESCAPE:
            send("PLAYERQUIT");
            break;
        }
        break;
    case 2:
        switch (event.key.keysym.sym) {
        case SDLK_a:
            send(event.type == SDL_KEYDOWN ? "A_ENEMYDOWN" : "A_ENEMYUP");
            break;
        case SDLK_d:
            send(event.type == SDL_KEYDOWN ? "D_ENEMYDOWN" : "D_ENEMYUP");
            break;
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_ENEMYDOWN" : "W_ENEMYUP");
            break;
        case SDLK_ESCAPE:
            send("ENEMYQUIT");
            break;
        }
        break;
    }
    
}

void MyGame::update() {
#pragma region PLAYER
    player.body.x = game_data.playerX;
    player.body.y = 580 - (player.body.h);
    if (game_data.playerBallFlag == 1) {
        player.ball->body.x = game_data.playerBallX;
        player.ball->body.y = game_data.playerBallY;
    }
    player.score = game_data.playerScore;
#pragma endregion

#pragma region ENEMY
    enemy.body.x = game_data.enemyX;
    enemy.body.y = enemy.body.h - 80;
    if (game_data.enemyBallFlag == 1) {
        enemy.ball->body.x = game_data.enemyBallX;
        enemy.ball->body.y = game_data.enemyBallY;
    }
    enemy.score = game_data.enemyScore;
#pragma endregion
}

void MyGame::loadResources() {
    player_tank_surface     = IMG_Load("res/images/blue_tank.png");
    player_bullet_surface   = IMG_Load("res/images/blue_bullet.png");
    enemy_tank_surface      = IMG_Load("res/images/red_tank.png");
    enemy_bullet_surface    = IMG_Load("res/images/red_bullet.png");
    score_font              = TTF_OpenFont("res/fonts/UniversCondensed.ttf", 64);
    bullet_hit_tank_sfx     = Mix_LoadWAV("res/sfx/BULLET_HIT_TANK.wav");
    bullet_hit_wall_sfx     = Mix_LoadWAV("res/sfx/BULLET_HIT_WALL.wav");
    player_fire_sfx         = Mix_LoadWAV("res/sfx/FIRE.wav");

    if (player_tank_surface != nullptr) { std::cout << "Loaded tank image successfully\n"; }
    else { std::cout << "Could not load tank image\n"; }

    if (player_bullet_surface != nullptr) { std::cout << "Loaded bullet image successfully\n"; }
    else { std::cout << "Could not load bullet image\n"; }
    
    if (enemy_tank_surface != nullptr) { std::cout << "Loaded tank image successfully\n"; }
    else { std::cout << "Could not load tank image\n"; }

    if (enemy_bullet_surface != nullptr) { std::cout << "Loaded bullet image successfully\n"; }
    else { std::cout << "Could not load bullet image\n"; }

    if (score_font != nullptr) { std::cout << "Loaded font successfully\n"; } 
    else { std::cout << "Could not load font\n"; }

    if (bullet_hit_tank_sfx != nullptr) { std::cout << "Loaded WAV file successfully\n"; }
    else { std::cout << "Could not load WAV file\n"; }
    
    if (bullet_hit_wall_sfx != nullptr) { std::cout << "Loaded WAV file successfully\n"; }
    else { std::cout << "Could not load WAV file\n"; }
    
    if (player_fire_sfx != nullptr) { std::cout << "Loaded WAV file successfully\n"; }
    else { std::cout << "Could not load WAV file\n"; }
}

// deletes raw pointers used for resources during exit
void MyGame::releaseResources() {
    delete player_tank_surface;
    delete player_bullet_surface;
    delete enemy_tank_surface;
    delete enemy_bullet_surface;
    delete score_font;
    delete player_score_surface;
    delete enemy_score_surface;
    delete player_score_texture;
    delete enemy_score_texture;
    delete player_tank_texture;
    delete enemy_tank_texture;
    delete player_bullet_texture;
    delete enemy_bullet_texture;

    Mix_FreeChunk(bullet_hit_tank_sfx);
    Mix_FreeChunk(bullet_hit_wall_sfx);
    Mix_FreeChunk(player_fire_sfx);

    delete bullet_hit_tank_sfx;
    delete bullet_hit_wall_sfx;
    delete player_fire_sfx;
}

void MyGame::initSpriteTextures(SDL_Renderer* renderer) {
    player_tank_texture = SDL_CreateTextureFromSurface(renderer, player_tank_surface);
    SDL_FreeSurface(player_tank_surface);
    enemy_tank_texture = SDL_CreateTextureFromSurface(renderer, enemy_tank_surface);
    SDL_FreeSurface(enemy_tank_surface);

    player_bullet_texture = SDL_CreateTextureFromSurface(renderer, player_bullet_surface);
    SDL_FreeSurface(player_bullet_surface);
    enemy_bullet_texture = SDL_CreateTextureFromSurface(renderer, enemy_bullet_surface);
    SDL_FreeSurface(enemy_bullet_surface);
}

void MyGame::playSound(Mix_Chunk* sound) {
    if (sound != nullptr) { Mix_PlayChannel(-1, sound, 0); }
    else { std::cout << "Cannot play sound\n"; }
}

void MyGame::initTextSurfaces() {
    SDL_Color player_score_color {58, 159, 255, 255};
    std::string player_score_text = "Player 1: " + std::to_string(game_data.playerScore);
    player_score_surface = TTF_RenderText_Blended(
        score_font,
        player_score_text.c_str(),
        player_score_color
    );

    SDL_Color enemy_score_color{ 255, 93, 58, 255 };
    std::string enemy_score_text = "Player 2: " + std::to_string(game_data.enemyScore);
    enemy_score_surface = TTF_RenderText_Blended(
        score_font,
        enemy_score_text.c_str(),
        enemy_score_color
    );
}

void MyGame::renderTanks(SDL_Renderer* renderer) {
#pragma region TANKS
    // Render SDL_Rects if textures cannot be loaded
    if (player_tank_texture == nullptr) { SDL_RenderDrawRect(renderer, &player.body); }
    else { SDL_RenderCopyEx(renderer, player_tank_texture, NULL, &player.body, 0.f, new SDL_Point(), SDL_FLIP_VERTICAL); }

    if (enemy_tank_texture == nullptr) { SDL_RenderDrawRect(renderer, &enemy.body); }
    else { SDL_RenderCopy(renderer, enemy_tank_texture, NULL, &enemy.body); }
#pragma endregion
}

void MyGame::renderBullets(SDL_Renderer* renderer) {
#pragma region BULLETS
    // balls render conditonally based on their respective flags
    if (game_data.playerBallFlag == 1)
        if (player_bullet_texture == nullptr) { SDL_RenderDrawRect(renderer, &player.ball->body); }
        else { SDL_RenderCopy(renderer, player_bullet_texture, NULL, &player.ball->body); }

    if (game_data.enemyBallFlag == 1)
        if (enemy_bullet_texture == nullptr) { SDL_RenderDrawRect(renderer, &enemy.ball->body); }
        else { SDL_RenderCopy(renderer, enemy_bullet_texture, NULL, &enemy.ball->body); }
#pragma endregion
}

void MyGame::renderText(SDL_Renderer* renderer) {
#pragma region SCORE_TEXT
    initTextSurfaces();

    if (player_score_surface == nullptr) { std::cout << "Could not create surface from font\n"; }
    else {
        player_score_texture = SDL_CreateTextureFromSurface(renderer, player_score_surface);
        SDL_FreeSurface(player_score_surface);
    }

    if (enemy_score_surface == nullptr) { std::cout << "Could not create surface from font\n"; }
    else {
        enemy_score_texture = SDL_CreateTextureFromSurface(renderer, enemy_score_surface);
        SDL_FreeSurface(enemy_score_surface);
    }

    if (player_score_texture == nullptr) { std::cout << "P1 SCORE: " << game_data.playerScore << std::endl; }
    else {
        int player_score_width, player_score_height;

        SDL_QueryTexture(
            player_score_texture,
            NULL,
            NULL,
            &player_score_width,
            &player_score_height
        );

        SDL_Rect player_score_dst = {
        20,
        0,
        player_score_width / 2,
        player_score_height / 2
        };

        SDL_RenderCopy(renderer, player_score_texture, NULL, &player_score_dst);
        SDL_DestroyTexture(player_score_texture);
    }

    if (enemy_score_texture == nullptr) { std::cout << "P2 SCORE: " << game_data.enemyScore << std::endl; }
    else {
        int enemy_score_width, enemy_score_height;

        SDL_QueryTexture(
            enemy_score_texture,
            NULL,
            NULL,
            &enemy_score_width,
            &enemy_score_height
        );

        SDL_Rect enemy_score_dst = {
        650,
        560,
        enemy_score_width / 2,
        enemy_score_height / 2
        };

        SDL_RenderCopy(renderer, enemy_score_texture, NULL, &enemy_score_dst);
        SDL_DestroyTexture(enemy_score_texture);
    }
#pragma endregion
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    renderTanks(renderer);
    renderBullets(renderer);
    renderText(renderer);
}
