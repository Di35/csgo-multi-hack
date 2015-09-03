#include "mem.h"

mem *mem::getCsgo() {
	static mem csgo("Counter-Strike: Global Offensive");
	return &csgo;
}


mem::mem(const char *windowNamee) {
	windowName = windowNamee;
}

mem::~mem() {
	CloseHandle(handle);
}

bool mem::openHandle() {
	handle = OpenProcess(PROCESS_ALL_ACCESS, false, getProcID());
	if (handle == NULL)
		return false;

	return true;
}

bool mem::closeHandle() {
	if (handle == 0)
		return false;

	CloseHandle(handle);
	handle = 0;

	return true;
}

DWORD mem::getProcID() {
	if (procId == -1)
		GetWindowThreadProcessId(GetForegroundWindow(), &procId);

	return procId;
}

HANDLE mem::getHandle() {
	if (handle == 0)
		openHandle();

	return handle;
}

bool mem::checkForeGroundWindow() {
	BYTE keystates[256];
	char title[256];
	GetKeyState(0);//idk whyy
	GetKeyboardState(keystates); //meep told me this is needed??

	GetWindowTextA(GetForegroundWindow(), title, 256);

	if (!strcmp(title, getWindowName()))
		return true;

	return false;
}

const char *mem::getModuleOffsetEx(const char *ModuleName) {
	while (true) {
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, getProcID());
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);
		if (Module32First(snapshot, &entry))
			do {
				if (!strcmp(entry.szModule, ModuleName)) {
					CloseHandle(snapshot);
					return ( char * ) entry.modBaseAddr;
				}
			} while (Module32Next(snapshot, &entry));
			CloseHandle(snapshot);
	}
}

const char *mem::getClientDllOffset() {
	static const char *offset = getModuleOffsetEx("client.dll");
	return offset;
}

const char *mem::getEngineDllOffset() {
	static const char *offset = getModuleOffsetEx("engine.dll");
	return offset;
}

bool mem::setModule(int num) {
	switch (num) {
		case CLIENTDLL:
			moduleOffset = getClientDllOffset();
			moduleName = "client.dll";
			return true;
			break;
		case ENGINEDLL:
			moduleOffset = getEngineDllOffset();
			moduleName = "engine.dll";
			return true;
			break;
		default:
			return false;
			break;
	}
}

const char *mem::getModuleOffset() {
	return moduleOffset;
}

const char *mem::getWindowName() {
	return windowName;
}