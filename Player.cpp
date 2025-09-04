#include "precomp.h"
#include "tmpl8math.h"
#include "sprite.h"
#include "Input.h"
#include "Player.h"
#include "Game.h"

Player::Player(Game* context, Sprite* sprite, int2 position, int lives) : Gameobject(context, sprite, position), lives(lives), prevInput(0, 0) {
}

Player::Player(const Player& other) : Gameobject(other), lives(other.lives), prevInput(0, 0) {
}

void Player::Tick(float deltaTime) {
	Gameobject::Tick(deltaTime);
	int2 delta = GetMovement();
	int2 newPosition = position + delta;

	//context->logicscreen->Box(newPosition.x - 5, newPosition.y - 5, newPosition.x + 5, newPosition.y + 5, 0xFF0000);

	int2 tilepos = GetTilePosition() * TILE_WIDTH;
	printf("%d, %d\n", tilepos.x, tilepos.y);

	context->logicscreen->Box(tilepos.x - 8, tilepos.y - 8, tilepos.x + 8, tilepos.y + 8, 0xFF0000);

	int2 nextTile = position + int2(delta.x * TILE_WIDTH / 2, delta.y * TILE_HEIGHT / 2);

	if (context->map.layers[0].GetTileIDAtPosition(
		uint2(
			clamp(nextTile.x / TILE_WIDTH, 0, MAP_WIDTH), 
			clamp(nextTile.y / TILE_HEIGHT, 0, MAP_HEIGHT)
			)
	) != 0) 
	{
		return;
	}

	position = newPosition;
}

void Player::Render(Surface* surface, int x, int y) {
	Gameobject::Render(surface, x, y);
}

int2 Player::GetMovement() {
	int2 prevDelta = deltaPosition;
	int2 raw(0, 0);
	if (Input::IsKeyDown(keyUp))	raw.y = -1;
	if (Input::IsKeyDown(keyDown))	raw.y = 1;
	if (Input::IsKeyDown(keyRight)) raw.x = 1;
	if (Input::IsKeyDown(keyLeft))	raw.x = -1;

	int2 result;

	if (raw.x * raw.y == 0) result = raw;
	else if (raw.x == raw.x && raw.y != raw.y) result = int2(0, raw.y);
	else if (raw.x != raw.x && raw.y == raw.y) result = int2(raw.x, 0);
	else result = int2(0, raw.y);

	prevInput = raw;
	return result;
}

void Player::InitControls(KeyCode up, KeyCode down, KeyCode right, KeyCode left) {
	this->keyUp = up;
	this->keyDown = down;
	this->keyRight = right;
	this->keyLeft = left;
}