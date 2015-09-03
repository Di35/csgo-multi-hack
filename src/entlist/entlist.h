#pragma once

#include "../main.h"

class entlist {
public:
	static DWORD getEntPtrFromID(int id, mem *csgo);

	entlist(mem *csgo);
private:
	DWORD entlistPtr;
	mem *imem;
};