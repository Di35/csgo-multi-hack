#pragma once

#include "baseplayer.h"
class localPlayer : public basePlayer {
public:
	static localPlayer *getLocalPlayer(mem *imem);

	localPlayer(mem *imem);
	localPlayer(DWORD lplyPtr);

	int getCrossHairID();

	Vector getPunchVec();

	void setEyeAngles(Angle ang);

	float getFlashDuration();
	float getFlashAlpha();
	void setFlashDuration(float duration);
	void setFlashAlpha(float alpha);
};