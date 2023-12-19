#ifndef WEAPON_H
#define WEAPON_H

#include "raylib.h"
#include "player.h"

typedef struct Weapon{
  Vector2 position;
  Vector2 centerPosition;
  Texture2D inHandSpriteSheet;
  Texture2D onGroundSpriteSheet;
  Rectangle frameRec;
  Rectangle hitbox;
}Weapon;


void WeaponBasicSetup(Weapon *weapon);
void DrawWeapon(Weapon *weapon);
void WeaponLocation(Weapon *weapon, Player *player);
void RenderWeapon(Weapon *weapon, Player *player);
#endif
