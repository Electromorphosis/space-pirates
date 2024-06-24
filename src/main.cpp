
#include <memory>
#include <random>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GlobalEventHandler.h"
#include "Window.h"
#include "MovementUtility.h"
#include "Player.h"
#include "Rock.h"
#include "TextBox.h"
#include "Particle.h"
#include "LaserBeam.h"

int main(int , char **) {
    using namespace std;
    MovementUtility *movementUtility = new MovementUtility();
    GlobalEventHandler globalEventHandler(0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrJetParticles(0, 3);
    std::uniform_int_distribution<> distrExplosionParticles(0, 5);
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
    Window window(&globalEventHandler, width, height);
    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60
    const Uint32 SHOOT_COOLDOWN_MS = 1000;
    Uint32 lastShootTime = 0;


    while (true) {
        // MAIN MENU LOGIC

        globalEventHandler.RestartEventsHandler();
        window.RestartRenderer();
        window.renderMenu = true;
        int buttonCooldown = 10;
        int menuView = 0; // -1 - game starts, 0 - main, 1 - Leaderboards, 2 - Help
        while (!globalEventHandler.gameOn) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) { // check if there are some events
                if (event.type == SDL_QUIT)
                    return 0;

            }
            const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
            if (buttonCooldown <= 0) {
                if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP]) {
                    window.menuHighlight--;
                    if (window.menuHighlight == -1) window.menuHighlight = 3;
                    window.menuHighlight %= 4;
                    buttonCooldown = 10;
                }
                if (keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN]) {
                    window.menuHighlight++;
                    window.menuHighlight %= 4;
                    buttonCooldown = 10;
                }
                if (keyboardState[SDL_SCANCODE_SPACE] || keyboardState[SDL_SCANCODE_KP_ENTER]) {
                    int previousMenuView = menuView;
                    menuView = window.menuHighlight;
                    if (previousMenuView == 0 && menuView == 0) menuView = -1;
                    SDL_Log("Menu option : %i", window.menuHighlight);
                    buttonCooldown = 10;
                }
                if (keyboardState[SDL_SCANCODE_ESCAPE] || keyboardState[SDL_SCANCODE_Q]) {
                    SDL_Quit();
                    return 0;
                }
            }

            int rockSpawnRoll = distrRockGen(
                    gen); // TODO: Create some kind of RandomnessUtility to handle def too much random vars in the main xd
            if (rockSpawnRoll > 90) {
                int face = distrFaceGen(gen);
                int angle = distrAngleGen(gen);
                int spawnPoint;
                if (face == 0 || face == 2) {
                    spawnPoint = distrWidthGen(gen);
                } else {
                    spawnPoint = distrHeightGen(gen);
                }
//

                window.gameObjectsVector.push_back(
                        std::make_unique<Rock>(&window, &globalEventHandler, face, angle, spawnPoint, "asteroid"));

            }

            for (auto &gameObject: window.gameObjectsVector) {
                if (gameObject && gameObject->movable) {
                    std::vector<float> gameObjectNewMovementVector = movementUtility->calculate(gameObject->angle);
//            SDL_Log("Vector calculated: { %f, %f }", gameObjectNewMovementVector.at(0), gameObjectNewMovementVector.at(1));
//              SDL_Log("GameObject coordinates before re-calculate (float): {%f, %f}", gameObject->positionX, gameObject->positionY);

                    gameObject->positionX += gameObjectNewMovementVector.at(0);
                    gameObject->positionY -= gameObjectNewMovementVector.at(1);
                    gameObject->renderPosX = static_cast<int>(gameObject->positionX);
                    gameObject->renderPosY = static_cast<int>(gameObject->positionY); //TODO: Move to GameObject::UpdatePosition() ?
//              SDL_Log("GameObject coordinates after re-calculate (float): {%f, %f}; (int): {%i, %i}", gameObject->positionX, gameObject->positionY, gameObject->renderPosX, gameObject->renderPosY);
                }
            }

            std::string Title = "SPACE PIRATEZ";
            std::string Start = "Start";
            std::string Leaderboards = "Leaderboards";
            std::string Help = "Help";
            std::string Quit = "Quit";
            window.textBoxesVector.clear();
            switch (menuView) {
                case -1:
                    globalEventHandler.gameOn = true;
                    break;
                case 0: // Main
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.1, height * 0.05, width - (width * 0.2),
                                                      height / 3, Title, 30));
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.30, height * 0.45, width - (width * 0.6),
                                                      height / 9, Start, 20));
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.10, height * 0.55, width - (width * 0.2),
                                                      height / 9, Leaderboards, 20));
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.35, height * 0.65, width - (width * 0.7),
                                                      height / 9, Help, 20));
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.35, height * 0.75, width - (width * 0.7),
                                                      height / 9, Quit, 20));
                    break;
                case 1: // Leaderboards
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.1, height * 0.05, width - (width * 0.2),
                                                      height / 3, Leaderboards, 30));
                    break;
                case 2: // Help
                    window.textBoxesVector.push_back(
                            std::make_unique<TextBox>(&window, width * 0.1, height * 0.05, width - (width * 0.2),
                                                      height / 3, Help, 30));
                    SDL_Log("Print help dummy");
                    break;
                case 3: // QUIT
                    SDL_Quit();
                    return 0;
                default:
                    break;
            }


            window.RenderAll();
            Uint32 currentFrameTime = SDL_GetTicks();
            Uint32 lastFrameTime = SDL_GetTicks();

            Uint32 elapsedTime = currentFrameTime - lastFrameTime;
            if (elapsedTime < MS_PER_FRAME) {
                SDL_Delay(MS_PER_FRAME - elapsedTime);
            }

            if (buttonCooldown > 0) {
                buttonCooldown--;
            }
            // Debug mode - straight to the game loop
//            globalEventHandler.gameOn = true;
        }



        // ACTUAL GAME LOGIC
        window.textBoxesVector.clear();
        window.gameObjectsVector.clear();
        window.RenderAll();
//Player player(&window);
//std::unique_ptr<Player> player(new Player(&window));
        window.renderMenu = false;
        Player *player = new Player(&window);
        player->movable = true;
        window.player = std::unique_ptr<Player>(player);

////    Player& player;
//    if (window.gameObjectsVector.at(0)) { // Check if the vector is not empty
//        Player* playerPtr = static_cast<Player*>(window.gameObjectsVector.at(0).get());
////        player = *playerPtr; // Dereference the pointer and assign to the reference
//    }

        for (int i = 0; i < 20; i++) {
            window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, &globalEventHandler, "random"));
        }
        std::string initScore = "SCORE : 0";
        std::string initHP = "HP : 3";
        // TODO: Could be useful to have an utility for calculation of a sensible text box size based on font & char sizes
        window.scoreTextBox = std::make_unique<TextBox>(&window, 0, 0, 130, 24, initScore);
        window.healthTextBox = std::make_unique<TextBox>(&window, width - 80, 0, 80, 24, initHP);
        Uint32 lastFrameTime = SDL_GetTicks();


//    window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, 0, 180, 250, "asteroid"));

        bool gameLoop = true;
        while (gameLoop) {


            SDL_Event event;
            while (SDL_PollEvent(&event)) { // check if there are some events
                if (event.type == SDL_QUIT)
                    return 0;

            }

            const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
            playerAccel = false;
// Todo: Add velocity vector which is applied at the end of the scan, so that <<possibly>> it will work for multi-key combos

//    player->currentAnimationState = Player::IDLE;
            if (player->movable && player->hp > 0) {


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
                    player->angle -= 1;
                    player->currentAnimationState = Player::COUNTER_TURN;
                }
                if (keyboardState[SDL_SCANCODE_D]) {
                    player->angle += 1;
                    player->currentAnimationState = Player::CLOCKWISE_TURN;
                }

                if (keyboardState[SDL_SCANCODE_SPACE] && lastFrameTime - lastShootTime >= SHOOT_COOLDOWN_MS) {
                    player->isShooting = true;
                    lastShootTime = lastFrameTime; // Update the last shoot time
                    player->currentAnimationState = Player::SHOOT;
                    spawnPlayerLaser = true;
                }
            } else {
                playerAccel = false;
                player->isShooting = false;
            }

            if (keyboardState[SDL_SCANCODE_ESCAPE])  {
                SDL_Quit();
                return 0;
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

                int partRoll = distrJetParticles(gen);
                if (player->velocity != 0 && partRoll == 1) { // Some random colored particles, but most pale
                    window.particleEffectsVector.push_back(
                            std::make_unique<Particle>(&window, player->positionX, player->positionY, 10, "random",
                                                       true));
                    //      SDL_Log("At x:%i, y:%i particle was generated!", window.gameObjectsVector.back()->renderPosX, window.gameObjectsVector.back()->renderPosY);
                } else {
                    window.particleEffectsVector.push_back(
                            std::make_unique<Particle>(&window, player->positionX, player->positionY, 10, "random",
                                                       false));
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


            if (spawnPlayerLaser) {
                window.projectilesVector.push_back(
                        std::make_unique<LaserBeam>(&window, player->positionX, player->positionY, player->angle));
//        SDL_Log("Player coordinates (float): {%f, %f}", player->positionX, player->positionY);
                spawnPlayerLaser = false;
            }

            for (auto &projectile: window.projectilesVector) {
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

            for (auto &gameObject: window.gameObjectsVector) {
                if (gameObject && gameObject->movable) {
                    std::vector<float> gameObjectNewMovementVector = movementUtility->calculate(gameObject->angle);
//            SDL_Log("Vector calculated: { %f, %f }", gameObjectNewMovementVector.at(0), gameObjectNewMovementVector.at(1));
//              SDL_Log("GameObject coordinates before re-calculate (float): {%f, %f}", gameObject->positionX, gameObject->positionY);

                    gameObject->positionX += gameObjectNewMovementVector.at(0);
                    gameObject->positionY -= gameObjectNewMovementVector.at(1);
                    gameObject->renderPosX = static_cast<int>(gameObject->positionX);
                    gameObject->renderPosY = static_cast<int>(gameObject->positionY); //TODO: Move to GameObject::UpdatePosition() ?
//              SDL_Log("GameObject coordinates after re-calculate (float): {%f, %f}; (int): {%i, %i}", gameObject->positionX, gameObject->positionY, gameObject->renderPosX, gameObject->renderPosY);
                }
            }

            int rockSpawnRoll = distrRockGen(
                    gen); // TODO: Create some kind of RandomnessUtility to handle def too much random vars in the main xd
            if (rockSpawnRoll > 98) {
                int face = distrFaceGen(gen);
                int angle = distrAngleGen(gen);
                int spawnPoint;
                if (face == 0 || face == 2) {
                    spawnPoint = distrWidthGen(gen);
                } else {
                    spawnPoint = distrHeightGen(gen);
                }


                window.gameObjectsVector.push_back(
                        std::make_unique<Rock>(&window, &globalEventHandler, face, angle, spawnPoint, "asteroid"));

            }


            window.CheckAllCollisions();
            window.UpdateGui();
            window.RenderAll();
            Uint32 currentFrameTime = SDL_GetTicks();
            Uint32 elapsedTime = currentFrameTime - lastFrameTime;
            ANIM_COUNTER++;
            if (ANIM_COUNTER == ANIM_DELAY) {
                ANIM_COUNTER = 0;
                player->frameCounter++;
            }

            if (elapsedTime < MS_PER_FRAME) {
                SDL_Delay(MS_PER_FRAME - elapsedTime);
            }

            lastFrameTime = SDL_GetTicks();
            SDL_Log("HP = %i", player->hp);
            if (player->hp <= 0 && player->currentAnimationState != Player::DESTROY) {
//        globalEventHandler.gameOn = false;
                player->currentAnimationState = Player::DESTROY;
                player->name = "None"; // This will disable further collisions
                globalEventHandler.gameOverTtl = 100;
            }
            if (player->currentAnimationState == Player::DESTROY) {
                player->velocity /= 1.1;
                globalEventHandler.gameOverTtl -= 1;

            }
            if (globalEventHandler.gameOverTtl <= 70) {
                for (int i = 0; i < 15; i++) {
                    int partRoll = distrExplosionParticles(gen);
                    if (partRoll >= 3) { // Random particles with or without the color
                        window.particleEffectsVector.push_back(
                                std::make_unique<Particle>(&window, player->positionX, player->positionY, 15,
                                                           "explosion", true));
                        //      SDL_Log("At x:%i, y:%i particle was generated!", window.gameObjectsVector.back()->renderPosX, window.gameObjectsVector.back()->renderPosY);
                    } else {
                        window.particleEffectsVector.push_back(
                                std::make_unique<Particle>(&window, player->positionX, player->positionY, 15,
                                                           "explosion", false));
                    }
                }

            }

            if (globalEventHandler.gameOverTtl <= 60) {
                for (int i = 0; i < 15; i++) {
                    int partRoll = distrExplosionParticles(gen);
                    if (partRoll >= 2) { // Random particles with or without the color
                        window.particleEffectsVector.push_back(
                                std::make_unique<Particle>(&window, player->positionX, player->positionY, 30,
                                                           "explosion", true));
                        //      SDL_Log("At x:%i, y:%i particle was generated!", window.gameObjectsVector.back()->renderPosX, window.gameObjectsVector.back()->renderPosY);
                    } else {
                        window.particleEffectsVector.push_back(
                                std::make_unique<Particle>(&window, player->positionX, player->positionY, 30,
                                                           "explosion", false));
                    }
                }

            }
            if (globalEventHandler.gameOverTtl <= 50) {
                globalEventHandler.gameOn = false;

            }
            if (globalEventHandler.gameOverTtl <= 0) {
                gameLoop = false;
            }

        }
        std::string gameOverText = "GAME OVER";
        window.textBoxesVector.push_back(
                std::make_unique<TextBox>(&window, width / 3, height / 3, width / 3, height / 6, gameOverText, 20));
        window.RenderAll();
        SDL_Delay(3500);

    }
    return 0;
}
