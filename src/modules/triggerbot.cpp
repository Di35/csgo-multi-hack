#include "triggerbot.h"

triggerbot::triggerbot() {
	threadhelper::threadhelper(&logic);
}


void logic(mem *csgo) {
	localPlayer *lply = localPlayer::getLocalPlayer(csgo);
	if (!lply->isAlive()) { return; }
	int idAtCrosshair = lply->getCrossHairID();
	if (idAtCrosshair == 0) { return; }

	basePlayer atCrosshair(entlist::getEntPtrFromID(idAtCrosshair, csgo), csgo);
	if (atCrosshair.getTeam() == lply->getTeam()) { return; }

	POINT point;
	GetCursorPos(&point);
	SendMessage(GetForegroundWindow(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(point.x, point.y));
	Sleep(10);
	SendMessage(GetForegroundWindow(), WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(point.x, point.y));
}