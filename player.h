#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"



typedef struct Player {
  //Stats
  Vector2 size;
  int hp;
  int damage;
  float speed;
  //Position
  Rectangle playerExactPosition;
  enum {
    DOWN,
    UP,
    LEFT,
    RIGHT,
  } direction;
  Vector2 position;
  enum {
    ADOWN,
    AUP,
    ALEFT,
    ARIGHT,
  } attackDirection;
  //Texture and animation
  Texture2D spriteSheet;
  int currentFrame;
  int frameSpeed;
  int frameCounter;
  int attackFrameCounter;
  int attackLargeFrameCounter;
  int attackMediumFrameCounter;
  Rectangle frameRec;
  Vector2 centerPosition;
  //Dealing damage
  Rectangle hitbox;
  Rectangle attackHitbox;
  bool attackState;
  bool shouldAttack;
  int attackCooldown;
  bool didPlayerAttack;
  //Movement
  bool canMove;
  //Taking damage
  bool tookDamage;
  //Weapons
  bool shouldSpawnWeapon;
  
} Player;


void PlayerBasicSetup(Player *player);
void PlayerMovement(Player *player);
void PlayerAttack(Player *player);
void DrawPlayer(Player *player);
void PlayerPlayAnimations(Player *player);



#endif
