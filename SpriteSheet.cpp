#include "precomp.h"
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(Array<Surface> surfaces) : surfaces(surfaces) {
	length = surfaces.GetLength();
	sprites = Array<Sprite*>(length);
	for (int i = 0; i < length; i++) {
		sprites[i] = new Sprite(&this->surfaces[i], 1);
	}
	printf("surfaces l : %d\n", surfaces.GetLength());
	printf("sprites  l : %d\n", sprites .GetLength());
}

Surface SpriteSheet::GetSurfaceWithID(int id) const {
	return surfaces[id];
}

Sprite* SpriteSheet::GetSpriteWithID(int id) const {
	return sprites[id];
}