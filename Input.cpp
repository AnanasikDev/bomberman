#include "precomp.h"
#include "Input.h"

uint* Input::keystates = nullptr;

bool Input::IsKeyDown(uint keycode) {
	return keystates[keycode & 255] == 1;
}

bool Input::IsKeyDown(KeyCode keycode) {
	return keystates[(uint)keycode & 255] == 1;
}
