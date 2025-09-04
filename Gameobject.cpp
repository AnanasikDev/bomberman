#include "precomp.h"
#include "settings.h"
#include "sprite.h"
#include "Gameobject.h"

Gameobject::~Gameobject() {
	printf("Gameobject deleted");
}

Gameobject::Gameobject(const Gameobject& other) : context(other.context), sprite(other.sprite), position(other.position), prevPosition(other.position), deltaPosition(0) {
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
	//sprite->DrawScaled(x, y, 200, 200, surface);
}

int2 Gameobject::GetTilePosition() const {
	return int2(position.x / TILE_WIDTH, position.y / TILE_HEIGHT);
}