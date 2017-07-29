#include "title_screen.h"

#include "level_screen.h"

#include <cmath>

void TitleScreen::init() {
  text_.reset(new Text("text.png"));
  backdrop_.reset(new Backdrop("title.png"));
  board_.reset(new Sprite("board.png", 0, 0, 48, 16));
  frames_ = 0;
}

bool TitleScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  frames_ += elapsed;
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  const int y = 120 + 3 * std::sin(frames_ / 150.0);

  backdrop_->draw(graphics);
  board_->draw(graphics, 104, y);
  text_->draw(graphics, "Press any key", 128, 208, Text::Alignment::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new LevelScreen();
}

std::string TitleScreen::get_music_track() const {
  return "";
}
