#include "player.h"
#include "enemy.h"
#include "weapon.h"
#include "raylib.h"

// basic declarations

void PlayerBasicSetup(Player *player) {
  // Stats
  player->speed = 1.3f;
  player->hp = 10;
  // Frames
  player->currentFrame = 0;
  player->frameSpeed = 8;
  // Sprite
  player->spriteSheet = (Texture2D)(LoadTexture)("characters/GoldKnight.png");
  player->frameRec.x = player->position.x;
  player->frameRec.y = player->position.y;
  player->position.x = 20;
  player->position.y =  20;
  player->frameRec.width = (float)player->spriteSheet.width/4;
  player->frameRec.height = (float)player->spriteSheet.height/7;
  player->centerPosition.x = player->frameRec.width/2;
  player->centerPosition.y = player->frameRec.height/2;
  player->canMove = true;
  // Hitboxes
  player->hitbox.x = player->position.x - player->frameRec.width/2;
  player->hitbox.y = player->position.y - player->frameRec.height/2;
  player->hitbox.width = (float)player->frameRec.width;
  player->hitbox.height = (float)player->frameRec.height;
  player->direction = DOWN;
  //Dealing damage
  player->attackCooldown = 1;
}

void PlayerPlayAnimations(Player *player) {
  player->frameCounter++;
  if (player->frameCounter >=
      (60 / player->frameSpeed)) // changing frames in animation
  {
    if(player->didPlayerAttack == true){
      player->attackCooldown++;
      if(player->attackCooldown == 5){
        player->didPlayerAttack == false;
        player->attackCooldown = 1;
      }
    }
    player->frameCounter = 0;
    player->currentFrame++;
    player->attackFrameCounter++;
    if (player->currentFrame > 2){
      player->currentFrame = 0;
      player->tookDamage = false;
    }
    if (player->attackFrameCounter > 1){
      player->frameRec.y = player->frameRec.height*1;
      player->attackFrameCounter = 0;
      player->shouldAttack = false;
      player->shouldSpawnWeapon = false;
    }
  }
}

void PlayerMovement(Player *player) {
  player->hitbox.x = player->position.x - player->frameRec.width/2;
  player->hitbox.y = player->position.y - player->frameRec.height/2;
  player->hitbox.width = (float)player->frameRec.width;
  player->hitbox.height = (float)player->frameRec.height;
  switch (player->direction) {
  case RIGHT:
    player->frameRec.x = player->frameRec.width*3;
    player->frameRec.y = player->frameRec.height;
    break;
  case LEFT:
    player->frameRec.x = player->frameRec.width*2;
    player->frameRec.y = player->frameRec.height;
    break;
  case UP:
    player->frameRec.x = player->frameRec.width*1;
    player->frameRec.y = player->frameRec.height;
    break;
  case DOWN:
    player->frameRec.x = player->frameRec.width*0;
    player->frameRec.y = player->frameRec.height;
    break;
  }
  if(player->canMove){
    if (IsKeyDown(KEY_D)) {
      player->direction = RIGHT;
      if (player->canMove)
        player->position.x += player->speed;
      player->frameRec.x = player->frameRec.width*3;
      player->frameRec.y = player->frameRec.height * player->currentFrame;
    }
    if (IsKeyDown(KEY_A)) {
      player->direction = LEFT;
      if (player->canMove)
        player->position.x -= player->speed;
      player->frameRec.x = player->frameRec.width*2;
      player->frameRec.y = player->frameRec.height * player->currentFrame;
    }
    if (IsKeyDown(KEY_W)) {
      player->direction = UP;
      if (player->canMove)
        player->position.y -= player->speed;
      player->frameRec.x = player->frameRec.width*1;
      player->frameRec.y = player->frameRec.height * player->currentFrame;
         }
    if (IsKeyDown(KEY_S)) {
      player->direction = DOWN;
      if (player->canMove)
        player->position.y += player->speed;
      player->frameRec.x = player->frameRec.width*0;
      player->frameRec.y = player->frameRec.height * player->currentFrame;
    }
  }
}
void PlayerAttack(Player *player) {
  if(IsKeyPressed(KEY_E)){
    if(player->attackCooldown == 1){
      player->shouldSpawnWeapon = true;
      player->shouldAttack = true;
    }
  }
  if (player->shouldAttack) {

    player->didPlayerAttack = true;
    player->attackState = true;
    switch (player->direction) {
    case RIGHT:
      player->attackDirection = ARIGHT;
      player->frameRec.x = player->frameRec.width*3;
      player->frameRec.y = player->frameRec.height*(player->attackFrameCounter+3);
      player->canMove = false;

      player->hitbox.x = player->position.x - player->frameRec.width/2;
      player->hitbox.y = player->position.y - player->frameRec.height/2;
      player->hitbox.width = player->frameRec.width;
      player->hitbox.height = player->frameRec.height;
      break;
    case LEFT:
      player->attackDirection = ALEFT;
      player->canMove = false;
      player->frameRec.x = player->frameRec.width*2;
      player->frameRec.y = player->frameRec.height*(player->attackFrameCounter+3);

      player->hitbox.x = player->position.x - player->frameRec.width/2;
      player->hitbox.y = player->position.y - player->frameRec.height/2;
      player->hitbox.width = player->frameRec.width;
      player->hitbox.height = player->frameRec.height;
      break;
    case UP:
      player->attackDirection = AUP;
      player->canMove = false;
      player->frameRec.x = player->frameRec.width*1;
      player->frameRec.y = player->frameRec.height*(player->attackFrameCounter+3);

      player->hitbox.x = player->position.x - player->frameRec.width/2;
      player->hitbox.y = player->position.y - player->frameRec.height/2;
      player->hitbox.width = player->frameRec.width;
      player->hitbox.height = player->frameRec.height;
      break;
    case DOWN:
      player->attackDirection = ADOWN;
      player->canMove = false;
      player->frameRec.x = player->frameRec.width*0;
      player->frameRec.y = player->frameRec.height*(player->attackFrameCounter+3);

      player->hitbox.x = player->position.x - player->frameRec.width/2;
      player->hitbox.y = player->position.y - player->frameRec.height/2;
      player->hitbox.width = player->frameRec.width;
      player->hitbox.height = player->frameRec.height;
      break;
    }
  } else{
      player->canMove = true;
      player->attackFrameCounter=0;
  }
}

void DrawPlayer(Player *player) {
  DrawTexturePro(
      player->spriteSheet, 
      player->frameRec, 
      (Rectangle) {player->position.x, player->position.y, player->frameRec.width, player->frameRec.height},
      player->centerPosition,
      0,
      WHITE);
}
