#pragma once

#include <memory>

#include "audio.h"
#include "backdrop.h"
#include "graphics.h"
#include "screen.h"
#include "text.h"

class OverworldScreen : public Screen {
  public:

    void init() override;
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
    static constexpr size_t kLevelCount = 5;
    static constexpr int kBoxSize = 8;

    std::unique_ptr<Text> text_;
    std::unique_ptr<Backdrop> backdrop_;

    size_t cursor_ = 3;
};

