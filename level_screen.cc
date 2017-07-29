#include "level_screen.h"

void LevelScreen::init() {
  text_.reset(new Text("text.png"));
}

bool LevelScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  player_.update(input, map_, elapsed);
  return true;
}

void LevelScreen::draw(Graphics& graphics) const {
  map_.draw(graphics, 0, 0);
  player_.draw(graphics, 0, 0);
}

Screen* LevelScreen::next_screen() {
  return nullptr;
}

std::string LevelScreen::get_music_track() const {
  return "";
}
