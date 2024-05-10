#ifndef NBODY_SRC_CORE_GAME_
#define NBODY_SRC_CORE_GAME_

class Game {
private:
  unsigned int width_;
  unsigned int height_;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();

  void ProcessInput(float delta_time);
  void Update(float delta_time);
  void Render();
};

#endif // NBODY_SRC_CORE_GAME_
