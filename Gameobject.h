#pragma once

namespace Tmpl8 {

	class Sprite;
	class Surface;

	class Gameobject
	{
	protected:
		int2 prevPosition;

	public:
		Sprite* sprite;
		int2 position;
		int2 deltaPosition;
		class Game* context;
		AABB box;

		Gameobject(Game* context) : context(context), sprite(nullptr), position(0, 0), deltaPosition(0, 0), prevPosition(0, 0) {}
		Gameobject(Game* context, Sprite* sprite, int2 pos);
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
		void SetPosition(int2 pos);

		int2 GetTilePosition() const;
	};
}