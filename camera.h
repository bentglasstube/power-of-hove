#pragma once

#include "map.h"
#include "player.h"

class Camera {
  public:
    Camera();

    void update(const Player& player, const Map& map, unsigned int elapsed);
    double xoffset() const;
    double yoffset() const;

  private:
    // TODO get height and width from graphics somehow
    static constexpr int kWidth = 256;
    static constexpr int kHeight = 240;
    static constexpr double kMaxSpeed = 1.0;

    double ox_, oy_;
};
