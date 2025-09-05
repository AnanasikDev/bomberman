#include "precomp.h"
#include "tmpl8math.h"
#include "settings.h"
#include "sprite.h"
#include "Gameobject.h"

Gameobject::~Gameobject() {
	printf("Gameobject deleted");
}

Gameobject::Gameobject(Game* context, Sprite* sprite, int2 pos) : context(context), position(pos), sprite(sprite), prevPosition(pos), deltaPosition(0) {
	/*int2 min = int2(position.x - sprite->GetWidth() / 2, position.y - sprite->GetHeight() / 2);
	int2 max = int2(position.x + sprite->GetWidth() / 2, position.y + sprite->GetHeight() / 2);
	box = AABB(min, max);*/
	box = AABB::FromCenterAndSize(position, sprite->GetSize());
}

Gameobject::Gameobject(const Gameobject& other) : context(other.context), sprite(other.sprite), position(other.position), prevPosition(other.position), deltaPosition(0), box(other.box) {
}

void Gameobject::SetPosition(int2 pos) {
	position = pos;
	box.SetCenterTo(position);
}

void Gameobject::Tick(float deltaTime) {
	//position.x += 1;
	deltaPosition = position - prevPosition;
	prevPosition = position;
}

void Gameobject::Render(Surface* surface, int x, int y) {
	if (sprite == nullptr) {
		printf("Cannot render, sprite is null");
		return;
	}
	sprite->Draw(surface, x - sprite->GetWidth() / 2, y - sprite->GetHeight() / 2);
	surface->Box(int2(box.GetCenter()), int2(box.GetSize()), 0x00FFFF);
	//sprite->DrawScaled(x, y, 200, 200, surface);
}

int2 Gameobject::GetTilePosition() const {
	return int2(position.x / TILE_WIDTH, position.y / TILE_HEIGHT);
}