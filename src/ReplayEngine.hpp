#pragma once

#include <iostream>
#include <vector>
#include <Geode/modify/PlayLayer.hpp>

enum ReplayState {
    Disabled,
    Recording,
    Playing
};

struct PlayerData {
    float xPos;
    float yPos;
    bool upsideDown;
    float rotation;
    double xSpeed;
    double ySpeed;
};

struct Action {
    bool player1;
    int frame;
    int button;
    bool holding;
    PlayerData p1;
    PlayerData p2;
};

class ReplayEngine {
    public:
        std::string macroName;
        std::vector<Action> actions;
        int currentAction = 0;
        ReplayState state = Disabled;
        bool android = false;
        int fps = 0;

        void recordAction(bool player1, int frame, bool holding, int button, PlayerData p1, PlayerData p2);
        int currentFrame();
};