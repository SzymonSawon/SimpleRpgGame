#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player.h"
#include "weapon.h"

  typedef struct Enemy {
    //Stats
    Vector2 size;
    int hp;
    int damage;
    float speed;
    //Movement
    enum {
      ERIGHT,
      EDOWN,
      ELEFT,
      EUP,
    } direction;
    Vector2 position;
    //Texture and animation
    Texture2D spriteSheet;
    Rectangle frameRec;
    int currentFrame;
    int frameSpeed;
    int frameCounter;
    Vector2 centerPosition;
    //Player detection
    bool isPlayerDetected;
    bool detectedAlertArea;
    bool shouldReturnToStart;
    Rectangle detectionArea;
    Vector2 startingPosition;
    int distanceCounter;
    int maxDistance;
    //Dealing damage
    Rectangle hitbox;
    bool damageCollision;
    //for delay:
    int damageCollisionCounter;
    //Taking damage
    //for push distance
    int pushDistanceCounter;
    bool tookDamage;
    //for delay:
    int takingDamageCounter;
    //Death
    bool canMove;
    int deathFrameCounter;
    int deathCurrentFrame;
    bool isAlive;

  } Enemy;

void EnemyBasicSetup(Enemy *enemy);
void EnemyFollowPlayer(Enemy *enemy, Player *player);
void EnemyWalkAround(Enemy *enemy);
void DrawEnemy(Enemy *enemy);
void EnemyAttack(Enemy *enemy, Player *player);
void EnemyPlayAnimations(Enemy *enemy);
void EnemyTakeDamage(Enemy *enemy, Player *player, Weapon *weapon);
void EnemyDeath(Enemy *enemy);

#endif
