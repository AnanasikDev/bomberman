#pragma once

#include "settings.h"
#include "tarray.h"
#include "surface.h"
#include "sprite.h"

namespace Tmpl8 {
	class SpriteSheet {
		Array<Surface> surfaces;
		Array<Sprite*> sprites;
		size_t length;

	public:
		SpriteSheet() = default;
		SpriteSheet(Array<Surface> surfaces);
		~SpriteSheet() = default;

		Surface GetSurfaceWithID(int id) const;
		Sprite* GetSpriteWithID(int id) const;
	};
}