#ifndef _PLAYER_OBJECT_
#define _PLAYER_OBJECT_

#include "SDL.h"

class PlayerObject {
    friend class MyGame;
private:
    enum Team {
        RED, BLUE
    };
    int score = 0;
    int health = 2;
    int ammo = 5;
    bool hasFired = false;
    Team team;
    SDL_Rect body;
    SDL_Rect turret;
    SDL_Color color;

public:
    PlayerObject();
    ~PlayerObject();

};
typedef PlayerObject Player;


#endif