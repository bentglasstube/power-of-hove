#include "game_state.h"

bool GameState::grabbed(double x, double y) const {
  const auto& i = grabbed_.find(std::make_pair(x, y));
  return i != grabbed_.end();
}

void GameState::grab(double x, double y) {
  grabbed_.emplace(std::make_pair(x, y));
  ++plutonium;
}

void GameState::spend(int amount) {
  plutonium -= amount;
}

// is this performant?  who fucking knows
size_t GameState::Hash::operator()(std::pair<double, double> const& p) const {
  size_t hash = 42;
  hash *= 15 + (int) p.first;
  hash *= 15 + (int) p.second;
  return hash;
}
