#pragma once

#include <unordered_set>

class GameState {
  public:
    int power_cells = 4, plutonium = 0, level = 3;
    bool double_jump = false, slow_fall = false;

    int collected() const;
    bool grabbed(double x, double y) const;
    void grab(double x, double y);
    void spend(int number);

  private:
    class Hash {
      public:
        size_t operator()(std::pair<double, double> const& p) const;
    };

    std::unordered_set<std::pair<double, double>, Hash> grabbed_;
};
