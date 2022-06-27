#pragma once

// Stanza
class Room
{
public:
	Room();
	// Collegamenti con altre stanze
	Room* front{ nullptr };
	Room* rear{ nullptr };
	Room* left{ nullptr };
	Room* right{ nullptr };
	// presenza di mostro, pozzo, pipistrello
	bool wump{ false };
	bool pit{ false };
	bool bat{ false };
	int numero{ 0 };
};
