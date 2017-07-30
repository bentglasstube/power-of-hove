#pragma once

#include "audio.h"
#include "backdrop.h"
#include "graphics.h"
#include "screen.h"
#include "text.h"

#include "game_state.h"

class OverworldScreen : public Screen {
  public:

    OverworldScreen(GameState state);

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() override;
    std::string get_music_track() const override;

  private:

    struct Level {
      int x, y;
      std::string file, description;
    };

    static const Level levels_[];
    static constexpr int kLevelCount = 5;
    static constexpr int kBoxSize = 8;

    Text text_;
    Backdrop backdrop_;
    GameState state_;
};

