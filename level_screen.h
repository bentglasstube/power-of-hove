#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"

#include "camera.h"
#include "map.h"
#include "parallax_backdrop.h"
#include "player.h"

class LevelScreen : public Screen {
  public:

    void init() override;
    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() override;
    std::string get_music_track() const override;

  private:

    std::unique_ptr<Text> text_;
    std::unique_ptr<ParallaxBackdrop> backdrop_;

    Camera camera_;
    Map map_;
    Player player_;
};
