#include "Room.h"

Room::Room() {
	// Collegamenti con altre stanze
	front = nullptr;
	rear  = nullptr;
	left = nullptr;
	right = nullptr;
	// presenza di mostro, pozzo, pipistrello
	wump = false;
	pit = false;
	bat = false;
	numero = 0;
}
