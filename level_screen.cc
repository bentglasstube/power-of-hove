#include "level_screen.h"

#include "overworld_screen.h"

LevelScreen::LevelScreen(GameState state) :
  text_("text.png"), backdrop_("forest.png", 128, 240, 4), state_(state), player_(state) {}

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
        // TODO add a plutonium
        audio.play_sample("plutonium.wav");
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
