#include "enemy.h"
#include "player.h"
#include "raylib.h"
#include "weapon.h"
#include <stdbool.h>

void EnemyBasicSetup(Enemy *enemy) {
  // Stats
  enemy->speed = 0.8f;
  enemy->hp = 3;
  enemy->damage = 1;
  // Position
  enemy->startingPosition.x = 150.0f;
  enemy->startingPosition.y = 110.0f;
  enemy->position.x = enemy->startingPosition.x;
  enemy->position.y = enemy->startingPosition.y;
  // Sprite
  enemy->frameRec.x = 0.0f;
  enemy->frameRec.y = 0.0f;
  enemy->spriteSheet = (Texture2D)(LoadTexture)("characters/EyeEnemy.png");
  enemy->frameRec.width = (float)enemy->spriteSheet.width / 4;
  enemy->frameRec.height = (float)enemy->spriteSheet.height / 4;
  enemy->centerPosition.x = enemy->frameRec.width/2;
  enemy->centerPosition.y = enemy->frameRec.height/2;
  // Animations
  enemy->currentFrame = 0;
  enemy->frameSpeed = 8;
  enemy->frameCounter = 0;
  // Hitboxes
  enemy->hitbox.x = enemy->position.x - enemy->frameRec.width;
  enemy->hitbox.y = enemy->position.y - enemy->frameRec.height;
  enemy->hitbox.width = enemy->frameRec.width;
  enemy->hitbox.height = enemy->frameRec.height;
  // Player detection
  enemy->detectionArea.width = (float)enemy->frameRec.width * 6;
  enemy->detectionArea.height = (float)enemy->frameRec.height * 6;
  enemy->maxDistance = 200;
  enemy->pushDistanceCounter = 20;
  //Death
  enemy->isAlive = true;
}

void EnemyAttack(Enemy *enemy, Player *player) {
  enemy->damageCollision = CheckCollisionRecs(enemy->hitbox, player->hitbox);
  if (enemy->damageCollision) {
    if (enemy->damageCollisionCounter == 1) {
      player->hp -= 1;
      player->tookDamage = true;
    }
    if (enemy->damageCollisionCounter == 40) {
      enemy->damageCollisionCounter = 0;
    }
    enemy->damageCollisionCounter++;
  }
}

void EnemyPlayAnimations(Enemy *enemy) {
  enemy->frameCounter++;
  if (enemy->frameCounter >=
      (60 / enemy->frameSpeed)) // changing frames in animation
  {
    enemy->frameCounter = 0;
    enemy->currentFrame++;
    if (enemy->currentFrame > 4){
      enemy->currentFrame = 0;
      enemy->tookDamage = false;
    }
    enemy->frameRec.y =
        (float)enemy->currentFrame * (float)enemy->frameRec.height;
  }
}

void EnemyWalkAround(Enemy *enemy) {

  enemy->hitbox.x = enemy->position.x - enemy->frameRec.width/2;
  enemy->hitbox.y = enemy->position.y - enemy->frameRec.height/2;
  if (enemy->isPlayerDetected == false) {
    if (enemy->distanceCounter <= 50) {
      enemy->position.x += enemy->speed;
      enemy->frameRec.x = enemy->frameRec.width*3;
    } else if (enemy->distanceCounter > 50 && enemy->distanceCounter <= 100) {
      enemy->position.y += enemy->speed;
      enemy->frameRec.x = enemy->frameRec.width*0;
    } else if (enemy->distanceCounter > 100 && enemy->distanceCounter <= 150) {
      enemy->position.x -= enemy->speed;
      enemy->frameRec.x = -enemy->frameRec.width*2;
    } else if (enemy->distanceCounter > 150 && enemy->distanceCounter <= enemy->maxDistance) {
      enemy->frameRec.x = enemy->frameRec.width*1;
      enemy->position.y -= enemy->speed;
    } else if (enemy->distanceCounter == enemy->maxDistance + 1) {
      enemy->distanceCounter = 0;
    }
    enemy->distanceCounter++;
  }
}
void EnemyFollowPlayer(Enemy *enemy, Player *player) {
  enemy->hitbox.x = enemy->position.x + enemy->frameRec.width/2;
  enemy->hitbox.y = enemy->position.y + enemy->frameRec.height/2;
  enemy->detectionArea.x = enemy->position.x - enemy->detectionArea.width/2 ;
  enemy->detectionArea.y = enemy->position.y - enemy->detectionArea.height/2 ;
  
  if (enemy->pushDistanceCounter > 10) {
    enemy->detectedAlertArea =
        CheckCollisionRecs(enemy->detectionArea, player->hitbox);
    if (enemy->detectedAlertArea) {
      enemy->isPlayerDetected = true;
      enemy->shouldReturnToStart = true;
    } else if(enemy->shouldReturnToStart) {
      enemy->isPlayerDetected = false;
      if (enemy->shouldReturnToStart == true) {
        if (enemy->position.x == enemy->startingPosition.x &&
            enemy->position.y == enemy->startingPosition.y) {
          enemy->shouldReturnToStart = false;
        }
        if (enemy->startingPosition.x > enemy->position.x){
          enemy->frameRec.x = enemy->frameRec.width*3;
          enemy->position.x += enemy->speed;
        }
        if (enemy->startingPosition.x < enemy->position.x){
          enemy->position.x -= enemy->speed;
          enemy->frameRec.x = enemy->frameRec.width*2;
        }
        if (enemy->startingPosition.y < enemy->position.y){
          enemy->position.y -= enemy->speed;
          enemy->frameRec.x = enemy->frameRec.width*1;
        }
        if (enemy->startingPosition.y > enemy->position.y){
          enemy->position.y += enemy->speed;
          enemy->frameRec.x = enemy->frameRec.width*0;
        }
        if((enemy->position.x ==enemy->startingPosition.x) && (enemy->position.y == enemy->startingPosition.y))
          enemy->shouldReturnToStart = false;
      }
    }
    if (enemy->isPlayerDetected == true) {
      enemy->distanceCounter = 0;
      if ((player->position.x > enemy->position.x) &&
          (player->position.y > player->position.y)) {
        enemy->position.x += enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*3;
      }
      else if ((player->position.x < enemy->position.x) &&
          (player->position.y < player->position.y)) {
        enemy->position.x -= enemy->speed;
        enemy->position.y -= enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*2;
      }
      else if ((player->position.x < enemy->position.x) &&
          (player->position.y > player->position.y)) {
        enemy->position.x -= enemy->speed;
        enemy->position.y += enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*2;
      }
      else if ((player->position.x > enemy->position.x) &&
          (player->position.y < player->position.y)) {
        enemy->position.x += enemy->speed;
        enemy->position.y -= enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*3;
      }
      if (player->position.x > enemy->position.x){
        enemy->position.x += enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*3;
      }
      if (player->position.x < enemy->position.x){
        enemy->position.x -= enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*2;
      } 
      if (player->position.y  < enemy->position.y){
        enemy->position.y -= enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*1;
      } 
      if (player->position.y  > enemy->position.y){
        enemy->position.y += enemy->speed;
        enemy->frameRec.x = enemy->frameRec.width*0;
      } 
    }
  } else {
    enemy->pushDistanceCounter++;
    if(player->attackDirection == ARIGHT){
      enemy->position.x = enemy->position.x + 2;
    }
    if(player->attackDirection == ALEFT){
      enemy->position.x = enemy->position.x - 2;
    }
    if(player->attackDirection == UP){
      enemy->position.y = enemy->position.y - 2;
    }
    if(player->attackDirection == DOWN){
      enemy->position.y = enemy->position.y + 2;
    }
    
  }
}

void EnemyTakeDamage(Enemy *enemy, Player *player, Weapon *weapon) {
  enemy->damageCollision = CheckCollisionRecs(enemy->hitbox, weapon->hitbox);
  if (enemy->damageCollision && player->attackState) {
    enemy->pushDistanceCounter = 0;
    if (enemy->takingDamageCounter == 1) {
      enemy->hp -= 1;
      enemy->tookDamage = true;
    }
    if (enemy->takingDamageCounter == 10){
      enemy->takingDamageCounter = 0;
    }
    enemy->takingDamageCounter++;
  }
  player->attackState = false;
}

void DrawEnemy(Enemy *enemy) {
  DrawTexturePro(enemy->spriteSheet, 
      enemy->frameRec,
      (Rectangle) {enemy->position.x, enemy->position.y, enemy->frameRec.width, enemy->frameRec.height}, 
      enemy->centerPosition,
      0,
      WHITE);
}


void EnemyDeath(Enemy *enemy){
  if(enemy->hp <= 0){
    enemy->deathFrameCounter++;
    if (enemy->deathFrameCounter >=
        (60 / enemy->frameSpeed)) // changing frames in animation
    {
      enemy->deathFrameCounter = 0;
      enemy->deathCurrentFrame++;
    }
    if(enemy->deathCurrentFrame == 0){
      DrawTexturePro(enemy->spriteSheet, 
          enemy->frameRec,
          (Rectangle) {enemy->position.x, enemy->position.y, enemy->frameRec.width, enemy->frameRec.height}, 
          enemy->centerPosition,
          0,
          CLITERAL(Color){ 0, 0, 0, 150 });
    }
    if(enemy->deathCurrentFrame == 1){
      DrawTexturePro(enemy->spriteSheet, 
          enemy->frameRec,
          (Rectangle) {enemy->position.x, enemy->position.y, enemy->frameRec.width, enemy->frameRec.height}, 
          enemy->centerPosition,
          0,
          CLITERAL(Color){ 0, 0, 0, 100 });
    }
    if(enemy->deathCurrentFrame == 2){
      enemy->isAlive = false;
      enemy->tookDamage = false;
      DrawTexturePro(enemy->spriteSheet, 
          enemy->frameRec,
          (Rectangle) {enemy->position.x, enemy->position.y, enemy->frameRec.width, enemy->frameRec.height}, 
          enemy->centerPosition,
          0,
          CLITERAL(Color){ 0, 0, 0, 50 });
    }
  }
  else DrawEnemy(enemy);
}

