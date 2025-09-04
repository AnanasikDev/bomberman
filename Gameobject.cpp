#include "precomp.h"
#include "sprite.h"
#include "Gameobject.h"

Gameobject::Gameobject(Sprite* sprite, int2 pos) : position(pos), sprite(sprite), prevPosition(pos), deltaPosition(0) {
}

Gameobject::~Gameobject() {
	printf("Gameobject deleted");
}

Gameobject::Gameobject(const Gameobject& other) : sprite(other.sprite), position(other.position), prevPosition(other.position), deltaPosition(0) {
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
	sprite->Draw(surface, x, y);
	//sprite->DrawScaled(x, y, 200, 200, surface);
}