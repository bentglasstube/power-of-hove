#pragma once

#include <unordered_set>

class GameState {
  public:
    int power_cells = 4, plutonium = 0;
    bool double_jump = false, slow_fall = false;

    bool grabbed(double x, double y) const;
    void grab(double x, double y);
    void spend(int number);

  private:
    struct Hash {
      // is this performant?  who fucking knows
      size_t operator()(std::pair<double, double> const& p) const {
        size_t hash = 42;
        hash *= 15 + (int) p.first;
        hash *= 15 + (int) p.second;
        return hash;
      }
    };

    std::unordered_set<std::pair<double, double>, Hash> grabbed_;
};
