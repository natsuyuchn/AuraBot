#include "ReplayEngine.hpp"

void ReplayEngine::recordAction(bool player1, int frame, bool holding, int button, PlayerData p1, PlayerData p2) {
    actions.push_back({ player1, frame, button, holding, p1, p2 });
};

int ReplayEngine::currentFrame() {
    int trueFPS = android ? 240 : fps;
    return PlayLayer::get()->m_gameState.m_currentProgress * (trueFPS / 240);
}