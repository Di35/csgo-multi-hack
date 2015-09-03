#pragma once
#include "../main.h"
#include "../threadhelper/threadhelper.h"
#include "../player/localplayer.h"
#include "../entlist/entlist.h"

#include <stdint.h>

struct GlowObjectDefinition_t
{
	void* pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	uint8_t unk2[10];
};

void logic3(mem *csgo);
class glow {
public:
	glow::glow();
	static DWORD getGlowObjectArray();
	static uint32_t getGlowObjectCount();
	static void logic();
	static mem *imem;
};