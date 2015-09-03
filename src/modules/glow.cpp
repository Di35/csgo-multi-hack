#include "glow.h"

using namespace glob;

glow::glow() {
	threadhelper::threadhelper(&logic3);
}

void glow::logic() {
	//if (localPlayer::getLocalPlayer(imem)->getHealth() > 1)
		//return;
	DWORD glowObjectArray = getGlowObjectArray();
	GlowObjectDefinition_t glowObjects[256];
	int count = getGlowObjectCount();
	if (count > 255)
		count = 255;
	size_t size = count * sizeof(GlowObjectDefinition_t);
	imem->setModule(mem::CLIENTDLL);
	ReadProcessMemory(imem->getHandle(), ( void * ) glowObjectArray, &glowObjects, size, nullptr);
	for (int i = 0; i < count; i++) {
		basePlayer curPlayer((DWORD)glowObjects[i].pEntity, imem);
		if (!curPlayer.isAlive())
			continue;
		glowObjects[i].a = 1.f;
		if (curPlayer.getTeam() != localPlayer::getLocalPlayer(imem)->getTeam()) {
			glowObjects[i].r = 1;	
			glowObjects[i].g = 0;
			glowObjects[i].b = 0;
		} else {
			glowObjects[i].r = 0;
			glowObjects[i].g = 1;
			glowObjects[i].b = 0;
		}
		glowObjects[i].m_bRenderWhenOccluded = true;
		glowObjects[i].m_bRenderWhenUnoccluded = false;
	}
	imem->setModule(mem::CLIENTDLL);
	WriteProcessMemory(imem->getHandle(), ( void * ) glowObjectArray, &glowObjects, size, nullptr);
}

DWORD glow::getGlowObjectArray() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<DWORD>(offsets::m_dwGlowObject);
}

uint32_t glow::getGlowObjectCount() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<int>(offsets::m_dwGlowObject + 0x4);
}

void logic3(mem *csgo) {
	if (glow::imem == 0)
		glow::imem = csgo;
	glow::logic();
	Sleep(250);
}

mem *glow::imem = 0;