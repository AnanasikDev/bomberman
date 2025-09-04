#include "precomp.h"
#include "tmpl8math.h"
#include "sprite.h"
#include "Input.h"
#include "Player.h"

Player::Player(Sprite* sprite, int2 position, int lives) : Gameobject(sprite, position), lives(lives) {
}

Player::Player(const Player& other) : Gameobject(other) {
	lives = other.lives;
}

void Player::Tick(float deltaTime) {
	Gameobject::Tick(deltaTime);
	/*if (Input::IsKeyDown(KeyCode::W)) {
		printf("W\n");
	}
	else {
		printf("no input\n");
	}*/
}

void Player::Render(Surface* surface, int x, int y) {
	Gameobject::Render(surface, x, y);
}