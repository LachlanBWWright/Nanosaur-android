// WebAPI.c - JavaScript/WebAssembly external command interface
// This file provides an API for external JavaScript code to interact with the game.
// Functions marked EMSCRIPTEN_KEEPALIVE are exported and callable from JavaScript.

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include "game.h"


/************************************************************/
/* FENCE COLLISION CONTROL                                  */
/************************************************************/
//
// Enables or disables background (fence/wall) collision detection.
// When disabled, the player can pass through terrain walls.
//
// JavaScript usage:
//   Module._SetFenceCollisionsEnabled(0);  // disable fences
//   Module._SetFenceCollisionsEnabled(1);  // enable fences
//

EMSCRIPTEN_KEEPALIVE void SetFenceCollisionsEnabled(int enabled)
{
	gFenceCollisionsDisabled = (enabled == 0);
}


/************************************************************/
/* FENCE COLLISION QUERY                                    */
/************************************************************/

EMSCRIPTEN_KEEPALIVE int GetFenceCollisionsEnabled(void)
{
	return gFenceCollisionsDisabled ? 0 : 1;
}


/************************************************************/
/* HEALTH CHEAT                                             */
/************************************************************/
//
// Restores the player's health to full.
//

EMSCRIPTEN_KEEPALIVE void CheatRestoreHealth(void)
{
	GetHealth(1);
}


/************************************************************/
/* FUEL CHEAT                                               */
/************************************************************/
//
// Fills the player's jetpack fuel to maximum.
//

EMSCRIPTEN_KEEPALIVE void CheatFillFuel(void)
{
	gFuel = MAX_FUEL_CAPACITY;
	gInfobarUpdateBits |= UPDATE_FUEL;
}


/************************************************************/
/* WEAPONS CHEAT                                            */
/************************************************************/
//
// Gives the player all weapons.
//

EMSCRIPTEN_KEEPALIVE void CheatGetWeapons(void)
{
	GetCheatWeapons();
}


/************************************************************/
/* EGGS CHEAT                                               */
/************************************************************/
//
// Recovers all eggs.
//

EMSCRIPTEN_KEEPALIVE void CheatGetAllEggs(void)
{
	GetAllEggsCheat();
}


/************************************************************/
/* SCORE QUERY                                              */
/************************************************************/
//
// Returns the current game score.
//

EMSCRIPTEN_KEEPALIVE uint32_t GetGameScore(void)
{
	return gScore;
}


#endif /* __EMSCRIPTEN__ */
