#include "weapon.h"
#include "player.h"
#include "enemy.h"

#include "raylib.h"

void WeaponBasicSetup(Weapon *weapon){
  weapon->inHandSpriteSheet = (Texture2D)(LoadTexture)("items/axeInHand.png");
  weapon->onGroundSpriteSheet = (Texture2D)(LoadTexture)("items/axe.png");
  weapon->frameRec.width = weapon->inHandSpriteSheet.width;
  weapon->frameRec.height = weapon->inHandSpriteSheet.height;
  weapon->frameRec.x = weapon->position.x;
  weapon->frameRec.y = weapon->position.y;
  weapon->centerPosition.x = weapon->frameRec.width/2;
  weapon->centerPosition.y = weapon->frameRec.height/2;
}


void DrawWeapon(Weapon *weapon){
}
void RenderWeapon(Weapon *weapon, Player *player){
  if (player->shouldSpawnWeapon){
    if(player->direction == RIGHT){
      weapon->position.y = player->position.y + player->frameRec.height/3.8;
      weapon->position.x = player->position.x + player->frameRec.width/1.4;

      weapon->hitbox.x = weapon->position.x-3.5;
      weapon->hitbox.y = weapon->position.y-5;
      weapon->hitbox.width = weapon->frameRec.height;
      weapon->hitbox.height = weapon->frameRec.width;
      DrawTexturePro(
          weapon->inHandSpriteSheet,
          weapon->frameRec,
          (Rectangle) {weapon->position.x, weapon->position.y, weapon->frameRec.width, weapon->frameRec.height},
          weapon->centerPosition,
          270,
          WHITE);
    }
    if(player->direction == LEFT){
      weapon->position.y = player->position.y + player->frameRec.height/3.8;
      weapon->position.x = player->position.x - player->frameRec.width/1.4;

      weapon->hitbox.x = weapon->position.x-3.5;
      weapon->hitbox.y = weapon->position.y-5;
      weapon->hitbox.width = weapon->frameRec.height;
      weapon->hitbox.height = weapon->frameRec.width;
      DrawTexturePro(
          weapon->inHandSpriteSheet,
          weapon->frameRec,
          (Rectangle) {weapon->position.x, weapon->position.y, weapon->frameRec.width, weapon->frameRec.height},
          weapon->centerPosition,
          90,
          WHITE);
    }
    if(player->direction == UP){
      weapon->position.y = player->position.y - player->frameRec.height/1.3;
      weapon->position.x = player->position.x - player->frameRec.width/4.5;

      weapon->hitbox.x = weapon->position.x-5;
      weapon->hitbox.y = weapon->position.y-4;
      weapon->hitbox.width =  weapon->frameRec.width;
      weapon->hitbox.height =weapon->frameRec.height;
      DrawTexturePro(
          weapon->inHandSpriteSheet,
          weapon->frameRec,
          (Rectangle) {weapon->position.x, weapon->position.y, weapon->frameRec.width, weapon->frameRec.height},
          weapon->centerPosition,
          180,
          WHITE);
    }
    if(player->direction == DOWN){
      weapon->position.y = player->position.y + player->frameRec.height/1.5;
      weapon->position.x = player->position.x - player->frameRec.width/4.5;

      weapon->hitbox.x = weapon->position.x-5;
      weapon->hitbox.y = weapon->position.y-4;
      weapon->hitbox.width =  weapon->frameRec.width;
      weapon->hitbox.height =weapon->frameRec.height;
      DrawTexturePro(
          weapon->inHandSpriteSheet,
          weapon->frameRec,
          (Rectangle) {weapon->position.x, weapon->position.y, weapon->frameRec.width, weapon->frameRec.height},
          weapon->centerPosition,
          0,
          WHITE);
    }
  }
}
