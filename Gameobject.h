#pragma once

//#include "tmpl8math.h"

namespace Tmpl8 {

	class Sprite;
	class Surface;

	class Gameobject
	{
	public:
		Sprite* sprite;
		int2 position;

		Gameobject() = default;
		Gameobject(Sprite* sprite, int2 position);
		Gameobject(const Gameobject& other);

		Gameobject& operator=(const Gameobject& other) {
			if (this != &other) {
				sprite = other.sprite;
				position = other.position;
			}
			return *this;
		}

		~Gameobject();

		virtual void Tick(float deltaTime);
		virtual void Render(Surface* surface, int x, int y);
	};
}