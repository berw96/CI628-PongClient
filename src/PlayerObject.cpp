#include "PlayerObject.h"

Player::PlayerObject() {
    body = {
        0,
        0,
        30,
        30
    };
    turret = {
        0,
        0,
        body.w,
        body.h / 3
    };
};
Player::~PlayerObject() {};
