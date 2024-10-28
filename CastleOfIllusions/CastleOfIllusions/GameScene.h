#ifndef _GAME_SCENE_INCLUDE
#define _GAME_SCENE_INCLUDE

#include "Scene.h"

class GameScene : public Scene {
public:
    void init() override;
    void update(int deltaTime) override;
    void render() override;

    void loadMap(const std::string& mapFile); // Load specific map based on level

private:
    // Additional attributes as needed
};

#endif // _GAME_SCENE_INCLUDE
