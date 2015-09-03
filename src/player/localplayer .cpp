#include "localplayer.h"

using namespace glob;

localPlayer *localPlayer::getLocalPlayer(mem *imem) {
	return new localPlayer(imem);
}

localPlayer::localPlayer(mem *imem) {
	setMemoryInterface(imem);
	imem->setModule(mem::CLIENTDLL);
	plyPtr = imem->readMemory<DWORD>(offsets::LocalPlayer_offset);
}

localPlayer::localPlayer(DWORD lplyPtr) {
	plyPtr = lplyPtr;
}

int localPlayer::getCrossHairID() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<int>(getPlyPtr(), offsets::m_iCrosshairID);
}

float localPlayer::getFlashDuration() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<float>(getPlyPtr(), offsets::m_flFlashDuration);

}

float localPlayer::getFlashAlpha() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<float>(getPlyPtr(), offsets::m_flFlashMaxAlpha);

}

void localPlayer::setFlashAlpha(float alpha) {
	imem->setModule(mem::CLIENTDLL);
	imem->writeMemory<float>(getPlyPtr(), offsets::m_flFlashMaxAlpha, alpha);
}

void localPlayer::setFlashDuration(float duration) {
	imem->setModule(mem::CLIENTDLL);
	imem->writeMemory<float>(getPlyPtr(), offsets::m_flFlashDuration, duration);

}

Vector localPlayer::getPunchVec() {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<Vector>(getPlyPtr(), offsets::m_vecPunch);
}