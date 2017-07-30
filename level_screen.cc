#include "level_screen.h"

#include "overworld_screen.h"

LevelScreen::LevelScreen(GameState state) :
  backdrop_("forest.png", 128, 240, 4),
  digits_("digits.png", 10, 8, 8),
  plutonium_("objects.png", 8, 8, 8),
  state_(state), player_(state), map_(state), camera_() {}

bool LevelScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (input.key_held(SDL_SCANCODE_A)) {
    player_.move_left();
  } else if (input.key_held(SDL_SCANCODE_D)) {
    player_.move_right();
  } else {
    player_.stop_moving();
  }

  if (input.key_pressed(SDL_SCANCODE_SPACE)) {
    player_.jump(audio);
  }

  player_.update(audio, map_, elapsed);
  camera_.update(player_, map_, elapsed);

  const Item* i = map_.item(player_.xpos(), player_.ypos());
  if (i) {
    switch (i->type()) {
      case Item::ItemType::Battery:
        player_.add_power();
        audio.play_sample("battery.wav");
        break;

      case Item::ItemType::Plutonium:
        audio.play_sample("plutonium.wav");
        state_.grab(i->xpos(), i->ypos());
        break;
    }

    map_.remove_item(i);
  }

  return !map_.out_of_bounds(player_.xpos(), player_.ypos());
}

void LevelScreen::draw(Graphics& graphics) const {
  const double cx = camera_.xoffset();
  const double cy = camera_.yoffset();

  backdrop_.draw(graphics, cx, cy);
  map_.draw(graphics, cx, cy);
  player_.draw(graphics, cx, cy);

  player_.draw_power(graphics, 0, 0);
  plutonium_.draw(graphics, 8 + SDL_GetTicks() / 100 % 8, graphics.width() - 16, 0);
  digits_.draw(graphics, state_.plutonium, graphics.width() - 8, 0);
}

void LevelScreen::load_level(const std::string& level) {
  map_.load(level);
  player_.set_pos(map_.startx(), map_.starty());
}

Screen* LevelScreen::next_screen() {
  return std::move(new OverworldScreen(state_));
}

std::string LevelScreen::get_music_track() const {
  return "";
}
