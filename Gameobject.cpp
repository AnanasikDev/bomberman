#include "precomp.h"
#include "sprite.h"
#include "Gameobject.h"

Gameobject::Gameobject(Sprite* sprite, int2 pos) : position(pos), sprite(sprite) {
}

Gameobject::~Gameobject() {
	printf("Gameobject deleted");
}

Gameobject::Gameobject(const Gameobject& other) {
	sprite = other.sprite;
	position = other.position;
}

void Gameobject::Tick(float deltaTime) {
	//position.x += 1;
}

void Gameobject::Render(Surface* surface, int x, int y) {
	if (sprite == nullptr) {
		printf("Cannot render, sprite is null");
		return;
	}
	sprite->Draw(surface, x, y);
	//sprite->DrawScaled(x, y, 200, 200, surface);
}