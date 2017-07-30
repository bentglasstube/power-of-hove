#pragma once

#include "audio.h"
#include "graphics.h"
#include "screen.h"
#include "spritemap.h"

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

    ParallaxBackdrop backdrop_;
    SpriteMap digits_, plutonium_;
    GameState state_;
    Player player_;
    Map map_;
    Camera camera_;
};
