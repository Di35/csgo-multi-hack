#pragma once

#include <iostream>
#include <stdio.h>
#include <tchar.h>

#include "windows.h"

#include "injector/injector.h"
#include "mem/mem.h"

#define safecontinue(msToWait) csgo->closeHandle();Sleep(msToWait);continue;

struct Vector {
	float x, y, z;
};
struct Angle {
	float x, y, z;
};

namespace glob {

	namespace offsets
	{
		const static DWORD LocalPlayer_offset = 0xa7afac;
		const static DWORD HandleOnGround_offset = 0x14C;
		const static DWORD m_bSpotted = 0x935;
		const static DWORD GlobalVars = 0x4f0204;
		const static DWORD m_vecOrigin = 0x134;
		const static DWORD m_iCrosshairID = 0x2410;
		const static DWORD m_dwEntityList = 0x04a1d384;
		const static DWORD m_iHealth = 0xfc;
		const static DWORD m_dwGlowObject = 0x04b3034;
		const static DWORD m_iTeamNum = 0xf0;
		const static DWORD m_flFlashMaxAlpha = 0x1db0;
		const static DWORD m_flFlashDuration = 0x1db4;
		const static DWORD m_vecPunch = 0x13e8;
		const static DWORD m_angEyeAngles = 0x23b4;
		const static DWORD m_dwClientState = 0x005d0214;
		const static DWORD m_dwViewAngles = 0x4ce0;
		const static DWORD m_dwInput = 0x4a67cc0;
		const static DWORD m_dwInGame = 0xe8;
	}
}
