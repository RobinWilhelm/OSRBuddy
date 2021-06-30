#pragma once


struct VanillaIceCream {
	const char* ingreds[4] = { "Milk", "Vanilla", "Egg", "Cream" };
	int amounts[4] = { 30, 30, 30, 30 };
	bool stackable = false;
};

struct SoulOfLaplace {
	enum {Snowmann_Killmark, Tenk_WP_Capsule, Tin_Edcanium} ingreds;
	int amounts[4] = { 285, 3, 25 };
	bool stackable = false;
};