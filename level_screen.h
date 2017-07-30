#pragma once

#include "audio.h"
#include "graphics.h"
#include "screen.h"
#include "text.h"

#include "camera.h"
#include "game_state.h"
#include "map.h"
#include "parallax_backdrop.h"
#include "player.h"

class LevelScreen : public Screen {
  public:

    LevelScreen(GameState state);

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    void load_level(const std::string& level);

    Screen* next_screen() override;
    std::string get_music_track() const override;

  private:

    Text text_;
    ParallaxBackdrop backdrop_;
    GameState state_;
    Player player_;
    Camera camera_;
    Map map_;
};
