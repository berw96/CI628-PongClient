#include "PlayerObject.h"

Player::PlayerObject() {
    body = {
        0,
        0,
        30,
        30
    };

    ball = new BallObject();
};
Player::~PlayerObject() {};

Ball::BallObject() {
    body = {
        0,
        0,
        15,
        15
    };
};
Ball::~BallObject() {};
