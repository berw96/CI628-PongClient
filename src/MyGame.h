#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "PlayerObject.h"

// Data provided by the server
static struct GameData {
    int playerX         = 0;
    int enemyX          = 0;
    int playerScore     = 0;
    int enemyScore      = 0;
    int playerBallX     = 0;
    int playerBallY     = 0;
    int enemyBallX      = 0;
    int enemyBallY      = 0;
    int playerBallFlag  = 0;
    int enemyBallFlag   = 0;
} game_data;

class MyGame {
   
private:
    int texture_width   = 100;
    int texture_height  = 100;

    Player player                       = Player();
    Player enemy                        = Player();

    Mix_Chunk* bullet_hit_tank_sfx      = nullptr;
    Mix_Chunk* bullet_hit_wall_sfx      = nullptr;
    Mix_Chunk* player_fire_sfx          = nullptr;

    SDL_Surface* player_tank_surface    = nullptr;
    SDL_Surface* enemy_tank_surface     = nullptr;
    SDL_Surface* player_bullet_surface  = nullptr;
    SDL_Surface* enemy_bullet_surface   = nullptr;
    SDL_Surface* player_score_surface   = nullptr;
    SDL_Surface* enemy_score_surface    = nullptr;

    SDL_Texture* player_tank_texture    = nullptr;
    SDL_Texture* enemy_tank_texture     = nullptr;
    SDL_Texture* player_bullet_texture  = nullptr;
    SDL_Texture* enemy_bullet_texture   = nullptr;
    SDL_Texture* player_score_texture   = nullptr;
    SDL_Texture* enemy_score_texture    = nullptr;

    TTF_Font* score_font                = nullptr;

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    void renderTanks(SDL_Renderer* renderer);
    void renderBullets(SDL_Renderer* renderer);
    void renderText(SDL_Renderer* renderer);

    void loadResources();
    void initSpriteTextures(SDL_Renderer* renderer);
    void initTextSurfaces();
    void releaseResources();

    void playSound(Mix_Chunk* sound);
};

#endif