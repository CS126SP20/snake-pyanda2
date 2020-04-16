// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef SNAKE_SNAKEAPP_H_
#define SNAKE_SNAKEAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>
#include <snake/engine.h>
#include <snake/leaderboard.h>
#include <snake/player.h>

#include <random>
#include <string>
#include <vector>

namespace snakeapp {

enum class GameState {
  kPlaying,
  kCountDown,
  kGameOver,
};

class SnakeApp : public cinder::app::App {
 public:
  SnakeApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawBackground() const;
  void DrawCountDown() const;
  void DrawFood();
  void DrawGameOver();
  void DrawSnake() const;
  float PercentageOver() const;
  void ResetGame();
  void BackgroundSound();
  void SnakeEatingSound();

 private:
  snake::Engine engine_;
  std::chrono::time_point<std::chrono::system_clock> last_intact_time_;
  std::chrono::time_point<std::chrono::system_clock> last_pause_time_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  snake::LeaderBoard leaderboard_;
  bool paused_;
  const std::string player_name_;
  bool printed_game_over_;
  const size_t size_;
  const size_t speed_;
  GameState state_;
  const size_t tile_size_;
  size_t time_left_;
  std::vector<snake::Player> top_players_;
  //current player's top scores
  std::vector<snake::Player> curr_player_scores_;
  //rgb values for snake's food (constantly changing)
  int r = 0;
  int g = 1;
  int b = 0;
  int snake_size = engine_.GetSnake().Size();
  //time since food last changed color
  std::chrono::time_point<std::chrono::system_clock> time_last_changed_color
  = std::chrono::system_clock::now();
  cinder::audio::VoiceRef background_sound;
  cinder::audio::VoiceRef nom_sound;
};

}  // namespace snakeapp

#endif  // SNAKE_SNAKEAPP_H_
