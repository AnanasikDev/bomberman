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
	gameobjects = (Gameobject**)MALLOC64(maxGameobjectsCount * sizeof(Gameobject*));

	map.ReadFromTMX("assets/bomberman/map.tmx");
	constexpr int idscount = SPRITE_SHEET_WIDTH * SPRITE_SHEET_HEIGHT;
	int ids[idscount];
	for (int i = 0; i < idscount; i++) {
		ids[i] = i;
	}

	IntArray tileIDs(SPRITE_SHEET_WIDTH * SPRITE_SHEET_HEIGHT, ids);

	sheet = SpriteSheet(Surface::FromSpriteSheet("assets/bomberman/spritesheet.png", TILE_WIDTH, SPRITE_SHEET_WIDTH, SPRITE_SHEET_HEIGHT, tileIDs));
	for (int l = 0; l < map.layers.GetLength(); l++) {
		for (int t = 0; t < map.layers[l].tiles.GetLength(); t++) {
			int2 pos = map.GetGridCoordinateByIndex(t);
			pos.x += TILE_WIDTH / 2;
			pos.y += TILE_HEIGHT / 2;
			int id = map.layers[l].tiles[t];
			if (id == 0) continue;
			Gameobject* go = new Gameobject(this, sheet.GetSpriteWithID(id), pos);
			AddGameobject(go);
		}
	}

	/*players = */
	/*for (int p = 0; p < NUM_PLAYERS; p++) {
		Player player = new Player(sheet.GetSpriteWithID(0), int2(0, 0), MAX_LIVES);
		players[p] = player;
		AddGameobject(&players[p]);
	}*/

	//PtrArray<Player> arr(1);
	//arr[0] = new Player(sheet.GetSpriteWithID(0), int2(0, 0), MAX_LIVES);
	players = Array<UniquePtr<Player>>(NUM_PLAYERS);
	for (int p = 0; p < NUM_PLAYERS; p++) {
		Player* player = new Player(this, sheet.GetSpriteWithID(0), int2(40, 40), MAX_LIVES);
		players[p] = player;
		player->InitControls(KeyCode::W, KeyCode::S, KeyCode::D, KeyCode::A);
		AddGameobject(player);
	}
	//UniquePtr<Player> player = new Player(sheet.GetSpriteWithID(0), int2(0, 0), MAX_LIVES);

	//arr[0] = Player(sheet.GetSpriteWithID(0), int2(0, 0), MAX_LIVES);

	//screen->Clear(0x00ff00);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{

	logicscreen->Clear(BACKGROUND_COLOR);
	for (int i = 0; i < gameobjectsCount; i++){
		gameobjects[i]->Tick(deltaTime);
	}

	for (int i = 0; i < gameobjectsCount; i++) {
		gameobjects[i]->Render(logicscreen, gameobjects[i]->position.x, gameobjects[i]->position.y);
	}

	int2 mp = int2(mousePos.x / 4, mousePos.y / 4);

	logicscreen->EnlargeAndCopyTo(screen, 4, 0, 0);
}