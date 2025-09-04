#include "precomp.h"
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
	sprite->Draw(surface, x, y);
	//sprite->DrawScaled(x, y, 200, 200, surface);
}