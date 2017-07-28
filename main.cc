#include "game.h"

int main(int, char**) {
  Game::Config config;

  config.graphics.title = "ld39";
  config.graphics.width = 256;
  config.graphics.height = 240;
  config.graphics.fullscreen = true;

  Game game(config);
  game.loop(nullptr);

  return 0;
}
