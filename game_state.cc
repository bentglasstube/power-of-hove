#include "game_state.h"

bool GameState::grabbed(double x, double y) const {
  const auto& i = grabbed_.find(std::make_pair(x, y));
  return i != grabbed_.end();
}

void GameState::grab(double x, double y) {
  grabbed_.emplace(std::make_pair(x, y));
}

