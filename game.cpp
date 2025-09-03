// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "settings.h"
#include "precomp.h"
#include "Map.h"
#include "Gameobject.h"
#include "game.h"

void Game::AddGameobject(Gameobject* go) {
	gameobjects[gameobjectsCount++] = go;
}

Game::Game() : gameobjects(nullptr), maxGameobjectsCount(MAX_GAMEOBJECTS), mousePos(0, 0) {

}

Game::~Game() {
	for (int i = 0; i < gameobjectsCount; i++){
		delete gameobjects[i];
	}
	FREE64(gameobjects);
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	// anything that happens only once at application start goes here

	map.Init(uint2(MAP_WIDTH, MAP_HEIGHT), uint2(TILE_WIDTH, TILE_HEIGHT));

	gameobjects = (Gameobject**)MALLOC64(maxGameobjectsCount * sizeof(Gameobject*));

	map.ReadFromTMX("assets/bomberman/map.tmx");
	constexpr int idscount = SPRITE_SHEET_WIDTH * SPRITE_SHEET_HEIGHT;
	int ids[idscount];
	for (int i = 0; i < idscount; i++) {
		ids[i] = i;
	}

	IntArray tileIDs(SPRITE_SHEET_WIDTH * SPRITE_SHEET_HEIGHT, ids);

	sheet = SpriteSheet(Surface::FromSpriteSheet("assets/bomberman/spritesheet.png", TILE_WIDTH, SPRITE_SHEET_WIDTH, SPRITE_SHEET_HEIGHT, tileIDs));
	for (int l = 1; l < map.layers.GetLength(); l++) {
		for (int t = 0; t < map.layers[l].tiles.GetLength(); t++) {
			int2 pos = map.GetCoordinateByIndex(t);
			int id = map.layers[l].tiles[t];
			if (id == 0) continue;
			Gameobject* go = new Gameobject(sheet.GetSpriteWithID(id), pos);
			AddGameobject(go);
		}
	}

	logicscreen->Clear(BACKGROUND_COLOR);

	for (int i = 0; i < gameobjectsCount; i++) {
		gameobjects[i]->Render(logicscreen, gameobjects[i]->position.x, gameobjects[i]->position.y);
	}

	logicscreen->EnlargeAndCopyTo(screen, 2);
	//screen->Clear(0x00ff00);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	/*screen->Clear(BACKGROUND_COLOR);
	for (int i = 0; i < gameobjectsCount; i++){
		gameobjects[i]->Tick(deltaTime);
	}

	for (int i = 0; i < gameobjectsCount; i++) {
		gameobjects[i]->Render(screen, gameobjects[i]->position.x, gameobjects[i]->position.y);
	}

	screen = &screen->Enlarge(4);*/
}