#pragma once

namespace Tmpl8 {

	class Sprite;
	class Surface;

	class Gameobject
	{
	public:
		Sprite* sprite;
		int2 position;

		Gameobject() = default;
		Gameobject(Sprite* sprite, int x, int y);
		Gameobject(Sprite* sprite, int2 position);

		~Gameobject();

		void Tick(float deltaTime);
		void Render(Surface* surface, int x, int y);
	};
}