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

	//int2 tilepos = GetTilePosition();// *int2(TILE_WIDTH, TILE_HEIGHT);
	int2 tilepos = int2(newPosition.x / TILE_WIDTH, newPosition.y / TILE_HEIGHT);
	//printf("%d, %d\n", tilepos.x, tilepos.y);

	context->logicscreen->Box(tilepos, int2(8), 0xFF0000);

	int2 nextTile = position + int2(delta.x, delta.y);

	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (!Map::IsGridPosOnMap(int2(tilepos.x + x, tilepos.y + y))) {
				continue;
			}

			uint2 otherTile = uint2(
				tilepos.x + x,
				tilepos.y + y
			);

			int2 otherTileWorldPos = Map::GridToWorld(otherTile);

			if (context->map.layers[0].GetTileIDAtGridPosition(otherTile) == 0) {
				continue;
			}

			{
				//int2 _tp = int2(otherTile.x, otherTile.y) * int2(TILE_WIDTH, TILE_HEIGHT);
				int2 _tp = otherTileWorldPos;
				context->logicscreen->Box(_tp, int2(18, 18), 0xFF0000);
			}
			AABB tile = AABB::FromCenterAndSize(
				otherTileWorldPos,
				int2(TILE_WIDTH, TILE_HEIGHT));

			context->logicscreen->Box(tile.GetCenter(), int2(20, 20), 0xAAFFFF);

			AABB intersection = AABB::GetIntersection(box, tile);
			/*bool intersect = box.Intersects(
				AABB::FromCenterAndSize(
					Map::GridToWorld(otherTile), 
					int2(TILE_WIDTH, TILE_HEIGHT)
				)
			);*/

			float2 size = intersection.GetSize();
			float2 playerToOther = otherTileWorldPos - position;
			
			printf("%f %f\n", playerToOther.x, playerToOther.y);

			if (size.x * size.y <= 10e-5) continue;

			if (size.x < size.y && size.x > 10e-1) {
				if (playerToOther.x * delta.x > 0) {
					delta.x = 0;
				}
			}
			else if (size.y < size.x && size.y > 10e-1) {
				if (playerToOther.y * delta.y > 0) {
					delta.y = 0;
				}
			}


			//printf("intersects %d\n", (int)intersect);

			//if (intersect) {
			//	//return;
			//}

		}
	}

	/*if (context->map.layers[0].GetTileIDAtPosition(
		uint2(
			clamp(nextTile.x / TILE_WIDTH, 0, MAP_WIDTH), 
			clamp(nextTile.y / TILE_HEIGHT, 0, MAP_HEIGHT)
			)
	) != 0) 
	{
		return;
	}*/

	SetPosition(position + delta);
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