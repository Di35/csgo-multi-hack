#include "norecoil.h"

using namespace glob;

norecoil::norecoil() {
	threadhelper::threadhelper(&logic4);
}
Vector lastvec;

void logic4(mem *csgo) {
	Vector newvec = localPlayer::getLocalPlayer(csgo)->getPunchVec();
	if (newvec.x == 0.f && newvec.y == 0.f)
		return;
	Vector idk;
	idk.x = lastvec.x - newvec.x;
	idk.y = lastvec.y - newvec.y;
	lastvec = newvec;
	csgo->setModule(mem::ENGINEDLL);
	Angle lol = csgo->readMemory<Angle>(offsets::m_dwClientState, offsets::m_dwViewAngles, true);
	lol.x += 2*idk.x;
	lol.y += 2*idk.y;
	csgo->setModule(mem::ENGINEDLL);
	csgo->writeMemory<Angle>(offsets::m_dwClientState, offsets::m_dwViewAngles, lol, true);
	Sleep(5);
}