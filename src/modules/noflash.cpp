#include "noflash.h"

noflash::noflash() {
	threadhelper::threadhelper(&logic2);
}


void logic2(mem *csgo) {
	localPlayer::getLocalPlayer(csgo)->setFlashDuration(0.f);
	localPlayer::getLocalPlayer(csgo)->setFlashAlpha(0.f);
	Sleep(250);
}