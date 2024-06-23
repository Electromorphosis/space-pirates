#include <SDL2/SDL.h>
#include <vector>
#include "Window.h"
#include "MovementUtility.h"
#include "Player.h"
#include "Rock.h"

#include "Particle.h"
#include "LaserBeam.h"
#include <memory>
#include <random>


int main(int , char **) {
  using namespace std;
  MovementUtility* movementUtility = new MovementUtility();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrPartGen(0, 3);
    std::uniform_int_distribution<> distrRockGen(0, 100);
    bool playerAccel = false;
    bool spawnPlayerLaser = false;
    int ANIM_DELAY = 5; // How often should animation state tick relative to the main framerate; AKA lazy animator relief
    int ANIM_COUNTER = 0;
  const int width = 500;
  const int height = 500;
    std::uniform_int_distribution<> distrHeightGen(0, height);
    std::uniform_int_distribution<> distrWidthGen(0, width);
    std::uniform_int_distribution<> distrAngleGen(0, 180);
    std::uniform_int_distribution<> distrFaceGen(0, 3); // 0 - up, 1 - right, 2 - down, 3 - left
    Window window(width, height);

//Player player(&window);
//std::unique_ptr<Player> player(new Player(&window));
Player* player = new Player(&window);
    window.player = std::unique_ptr<Player>(player);

////    Player& player;
//    if (window.gameObjectsVector.at(0)) { // Check if the vector is not empty
//        Player* playerPtr = static_cast<Player*>(window.gameObjectsVector.at(0).get());
////        player = *playerPtr; // Dereference the pointer and assign to the reference
//    }

//    for (int i = 0; i < 8; i++) {
//        window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, "random"));
//    }

    Uint32 lastFrameTime = SDL_GetTicks();

    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60
    const Uint32 SHOOT_COOLDOWN_MS = 1000;
    Uint32 lastShootTime = 0;

//    window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, 0, 180, 250, "asteroid"));


  for (bool game_active = true; game_active;) {


    SDL_Event event;
    while (SDL_PollEvent(&event)) { // check if there are some events
      if (event.type == SDL_QUIT)
        game_active = false;

    }

      const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
playerAccel = false;
// Todo: Add velocity vector which is applied at the end of the scan, so that <<possibly>> it will work for multi-key combos

//    player->currentAnimationState = Player::IDLE;

    if (keyboardState[SDL_SCANCODE_W]) {
        player->velocity += 0.1;
        playerAccel = true;
        player->currentAnimationState = Player::FORWARD;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        player->velocity -= 0.1;
        playerAccel = true;
        player->currentAnimationState = Player::BACKWARDS;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        player->angle-=1;
        player->currentAnimationState = Player::COUNTER_TURN;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        player->angle+=1;
        player->currentAnimationState = Player::CLOCKWISE_TURN;
    }

    if (keyboardState[SDL_SCANCODE_SPACE] && lastFrameTime - lastShootTime >= SHOOT_COOLDOWN_MS) {
        player->isShooting = true;
        lastShootTime = lastFrameTime; // Update the last shoot time
        player->currentAnimationState = Player::SHOOT;
        spawnPlayerLaser = true;
    }
//
//      if (event.type == SDL_KEYDOWN && keyboardState[SDL_SCANCODE_SPACE]) {
//          playerShoots = true;
//      }

//        SDL_Log("Velocity: %f", player.velocity);
//      SDL_Log("Angle: %i*", player.angle);
    if (player->velocity < -0.5) player->velocity = -0.5;
    if (player->velocity > 1) {
        player->velocity = 1;
//        playerAccel = false;
    }


      // Particle effects
    if (playerAccel) {

        int partRoll = distrPartGen(gen);
        if (player->velocity != 0 && partRoll == 1) { // Some random colored particles, but most pale
            window.particleEffectsVector.push_back(std::make_unique<Particle>(&window, player->positionX, player->positionY, 10,  "random", true));
    //      SDL_Log("At x:%i, y:%i particle was generated!", window.gameObjectsVector.back()->renderPosX, window.gameObjectsVector.back()->renderPosY);
        } else {
            window.particleEffectsVector.push_back(std::make_unique<Particle>(&window, player->positionX, player->positionY, 10,  "random", false));
        }

    }


      // Position update for movement objects
    std::vector<float> newMovementVector = movementUtility->calculate(player->angle);
//      SDL_Log("%f, %f", newMovementVector.at(0), newMovementVector.at(1));
    player->positionX += newMovementVector.at(0) * player->velocity;
    player->positionY -= newMovementVector.at(1) * player->velocity;

    player->renderPosX = static_cast<int>(player->positionX);
    player->renderPosY = static_cast<int>(player->positionY);
//      SDL_Log("Player coordinates (render): {%i, %i}", player->renderPosX, player->renderPosY);

//      window.projectilesVector.push_back(std::make_unique<LaserBeam>(&window, player->positionX, player->positionY, player->angle));


    if(spawnPlayerLaser) {
        window.projectilesVector.push_back(std::make_unique<LaserBeam>(&window, player->positionX, player->positionY, player->angle));
//        SDL_Log("Player coordinates (float): {%f, %f}", player->positionX, player->positionY);
    spawnPlayerLaser = false;
    }

    for (auto& projectile : window.projectilesVector) {
        if (projectile) {
            std::vector<float> projectileNewMovementVector = movementUtility->calculate(projectile->angle);
//            SDL_Log("Vector calculated: { %f, %f }", projectileNewMovementVector.at(0), projectileNewMovementVector.at(1));
//              SDL_Log("Projectile coordinates before re-calculate (float): {%f, %f}", projectile->positionX, projectile->positionY);

            projectile->positionX += projectileNewMovementVector.at(0) * 5;
            projectile->positionY -= projectileNewMovementVector.at(1) * 5;
            projectile->renderPosX = static_cast<int>(projectile->positionX);
            projectile->renderPosY = static_cast<int>(projectile->positionY);
//              SDL_Log("Projectile coordinates after re-calculate (float): {%f, %f}", projectile->positionX, projectile->positionY);
        }
    }

      for (auto& gameObject : window.gameObjectsVector) {
          if (gameObject && gameObject->movable) {
              std::vector<float> gameObjectNewMovementVector = movementUtility->calculate(gameObject->angle);
//            SDL_Log("Vector calculated: { %f, %f }", gameObjectNewMovementVector.at(0), gameObjectNewMovementVector.at(1));
//              SDL_Log("GameObject coordinates before re-calculate (float): {%f, %f}", gameObject->positionX, gameObject->positionY);

              gameObject->positionX += gameObjectNewMovementVector.at(0);
              gameObject->positionY -= gameObjectNewMovementVector.at(1);
              gameObject->renderPosX = static_cast<int>(gameObject->positionX);
              gameObject->renderPosY = static_cast<int>(gameObject->positionY); //TODO: Move to GameObject::UpdatePostion() ?
//              SDL_Log("GameObject coordinates after re-calculate (float): {%f, %f}; (int): {%i, %i}", gameObject->positionX, gameObject->positionY, gameObject->renderPosX, gameObject->renderPosY);
          }
      }

      int rockSpawnRoll = distrRockGen(gen); // TODO: Create some kind of RandomnessUtility to handle def too much random vars in the main xd
      if (rockSpawnRoll > 8) {
          int face = distrFaceGen(gen);
          int angle = distrAngleGen(gen);
          int spawnPoint;
          if (face == 0 || face == 2) {
              spawnPoint = distrWidthGen(gen);
          } else {
              spawnPoint = distrHeightGen(gen);
          }


                  window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, face, angle, spawnPoint, "asteroid"));

      }



    window.CheckAllCollisions();
    window.RenderAll();
    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 elapsedTime = currentFrameTime - lastFrameTime;
    ANIM_COUNTER++;
    if(ANIM_COUNTER == ANIM_DELAY) {
        ANIM_COUNTER = 0;
        player->frameCounter++;
    }

    if (elapsedTime < MS_PER_FRAME) {
        SDL_Delay(MS_PER_FRAME - elapsedTime);
    }

    lastFrameTime = SDL_GetTicks();


  }

  return 0;
}

