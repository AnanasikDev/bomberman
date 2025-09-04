#pragma once

#include "Gameobject.h"
#include "Input.h"

namespace Tmpl8 {
	
	class Sprite;

	class Player : public Gameobject {
	public:
		int2 prevInput;
		int lives;
		KeyCode keyUp;
		KeyCode keyDown;
		KeyCode keyRight;
		KeyCode keyLeft;

		Player(Sprite* sprite, int2 position, int lives);

		Player(const Player& other);
		
		Player& operator=(const Player& other) {
			if (this != &other) {
				sprite = other.sprite;
				position = other.position;
				lives = other.lives;
			}
			return *this;
		}

		void Tick(float deltaTime) override;
		void Render(Surface* surface, int x, int y) override;
		int2 GetMovement();
		void InitControls(KeyCode up, KeyCode down, KeyCode right, KeyCode left);
	};
}