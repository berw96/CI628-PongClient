#ifndef _PLAYER_OBJECT_
#define _PLAYER_OBJECT_

#include "SDL.h"
class BallObject;

class PlayerObject {
    friend class MyGame;
    friend class BallObject;
private:
    int score = 0;
    bool hasFired = false;
    SDL_Rect body;
    BallObject* ball;

public:
    PlayerObject();
    ~PlayerObject();

};
typedef PlayerObject Player;

class BallObject {
    friend class MyGame;
    friend class BallObject;
private:
    int radius =  5;
    bool isActive;
    SDL_Rect body;

public:
    BallObject();
    ~BallObject();
};
typedef BallObject Ball;

#endif