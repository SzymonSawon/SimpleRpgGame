#include "raylib.h"
#include <stdbool.h>

#include "player.h"
#include "enemy.h"
#include "weapon.h"


#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

// Program main entry point
int main(void) {
  //Screen scale
  const int screenWidth = 2560;
  const int screenHeight = 1440;

  const int virtualScreenWidth = 480;
  const int virtualScreenHeight = 270;

  const float virtualRatio = (float)screenWidth / (float)screenWidth;

  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - keyboard input");
  Camera2D worldSpaceCamera = {0};
  worldSpaceCamera.zoom = 1.0f;

  Camera2D screenSpaceCamera = {0};
  screenSpaceCamera.zoom = 1.0f;
  
  screenSpaceCamera.offset = (Vector2){(float)virtualScreenWidth/2,(float)virtualScreenHeight/2};

  RenderTexture2D target =
      LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);


  Vector2 origin = {0.0f, 0.0f};

  Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width,
                         -(float)target.texture.height};
  Rectangle destRec = {-virtualRatio, -virtualRatio,
                       screenWidth + (virtualRatio * 2),
                       screenHeight + (virtualRatio * 2)};
  
  //Textures

  //Frames
  int frameCounter = 0;
  int frameSpeed = 8;

  //Initialization
  Player player = {0};
  PlayerBasicSetup(&player);
  Weapon axe = {0};
  WeaponBasicSetup(&axe);

  Enemy eyeEnemy = {0};
  EnemyBasicSetup(&eyeEnemy);
  //Set game to run at 60 fps
  SetTargetFPS(60); 

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    frameCounter++;
    int last_pressed = 0;
    


  
    // Player movement
    PlayerMovement(&player);
    // Player attack
    PlayerAttack(&player);
    EnemyTakeDamage(&eyeEnemy,&player, &axe);
    //Player animations
    PlayerPlayAnimations(&player);

    // Slime movement
    if(eyeEnemy.isAlive){
      EnemyFollowPlayer(&eyeEnemy, &player);
      EnemyWalkAround(&eyeEnemy);
      // Slime Attack
      EnemyAttack(&eyeEnemy, &player);
      // Enemy Animations
      EnemyPlayAnimations(&eyeEnemy);
    }



   // Textures and Animations
    destRec.x = player.position.x;
    destRec.y = player.position.y;
    BeginMode2D(screenSpaceCamera);
    BeginTextureMode(target);
    ClearBackground(CLITERAL(Color){ 255, 255, 255, 0 });
    DrawText(TextFormat("Player HP: %d", player.hp), 1, 1, 1, BLACK);
    DrawText(TextFormat("Enemy HP: %d", eyeEnemy.hp), 1, 15, 2, BLACK);
    player.playerExactPosition.x = player.position.x;
    player.playerExactPosition.y = player.position.y;
    player.playerExactPosition.width = 1;
    player.playerExactPosition.height = 1;
    DrawRectangle(player.playerExactPosition.x, player.playerExactPosition.y, player.playerExactPosition.width, player.playerExactPosition.height, PINK);
    if (true) {
      //Player hitbox
      DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, GREEN);
      DrawRectangle(eyeEnemy.hitbox.x, eyeEnemy.hitbox.y, eyeEnemy.hitbox.width, eyeEnemy.hitbox.height, RED);
      DrawRectangle(axe.hitbox.x, axe.hitbox.y, axe.hitbox.width, axe.hitbox.height, RED);
      //Enemy player detection area
      //Enemy hitbox
    }
    EnemyDeath(&eyeEnemy);
    RenderWeapon(&axe, &player);
    DrawPlayer(&player);
    RenderWeapon(&axe, &player);
      //DrawRectangle(player.playerExactPosition.x, player.playerExactPosition.y, player.playerExactPosition.width,
        //            player.playerExactPosition.height, ORANGE);
        //
        //
    //Player change color when taking damage
    if(player.tookDamage == false){
      player.hp = player.hp;
      }else{
        DrawTexturePro(
            player.spriteSheet, 
            player.frameRec, 
            (Rectangle) {player.position.x, player.position.y, player.frameRec.width, player.frameRec.height},
            player.centerPosition,
            0,
            CLITERAL(Color){ 235, 64, 52, 100 });
        }
    if(eyeEnemy.tookDamage == true){
        DrawTexturePro(
            eyeEnemy.spriteSheet, 
            eyeEnemy.frameRec, 
            (Rectangle) {eyeEnemy.position.x, eyeEnemy.position.y, eyeEnemy.frameRec.width, eyeEnemy.frameRec.height},
            eyeEnemy.centerPosition,
            0,
            CLITERAL(Color){ 235, 64, 52, 100 });
        }

    EndTextureMode();
    EndMode2D();

    BeginDrawing();
    ClearBackground(LIME);
    DrawTexturePro(target.texture, sourceRec, destRec, player.position, 0.0f, WHITE);
    EndDrawing();
  }
  UnloadTexture(eyeEnemy.spriteSheet);
  UnloadTexture(player.spriteSheet);
  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
