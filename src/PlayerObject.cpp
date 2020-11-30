#include "PlayerObject.h"

Player::PlayerObject() {
    body = {
        0,
        0,
        100,
        100
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
