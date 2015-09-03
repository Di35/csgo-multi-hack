#pragma once

#include "Windows.h"
#include "TlHelp32.h"
#include <stdio.h>
#include <string.h>

class mem {
public:

	enum {
		CLIENTDLL,
		ENGINEDLL
	};

	static mem *getCsgo();

	mem(const char *windowName);
	~mem();

	bool checkForeGroundWindow();

	const char *getWindowName();

	bool openHandle();
	bool closeHandle();

	DWORD getProcID();
	HANDLE getHandle();

	bool setModule(int num);
	const char *getModuleOffsetEx(const char *moduleName);
	const char *getClientDllOffset();
	const char *getEngineDllOffset();

	const char *getModuleOffset();

	template <class retType>
	retType readMemoryRaw(DWORD address, SIZE_T size, bool useModuleOffset = true) {
		retType toReturn;
		ReadProcessMemory(getHandle(), ( LPVOID ) ( ( useModuleOffset ? getModuleOffset() : 0 ) + address ), &toReturn, size, nullptr);
		return toReturn;
	}

	template <class retType>
	retType readMemory(DWORD address, bool useModuleOffset = true) {
		retType toReturn;
		ReadProcessMemory(getHandle(), ( LPVOID ) ( ( useModuleOffset ? getModuleOffset() : 0 ) + address ), &toReturn, sizeof(retType), nullptr);
		return toReturn;
	}

	template <class retType>
	retType readMemory(DWORD address, DWORD offset, bool useModuleOffset = false) {
		if (useModuleOffset)
			address = readMemory<DWORD>(address);

		return readMemory<retType>(address + offset, false);
	}

	void writeMemoryRaw(DWORD address, DWORD toWrite, SIZE_T size, bool useModuleOffset = true) {
		WriteProcessMemory(getHandle(), ( LPVOID ) ( ( useModuleOffset ? getModuleOffset() : 0 ) + address ), &toWrite, size, nullptr);
	}

	template <class writeType>
	void writeMemory(DWORD address, writeType toWrite, bool useModuleOffset = true) {
		WriteProcessMemory(getHandle(), ( LPVOID ) ( ( useModuleOffset ? getModuleOffset() : 0 ) + address ), &toWrite, sizeof(writeType), nullptr);
	}

	template <class writeType>
	void writeMemory(DWORD address, DWORD offset, writeType toWrite, bool useModuleOffset = false) {
		if (useModuleOffset)
			address = readMemory<DWORD>(address);

		writeMemory<writeType>(address + offset, toWrite, false);
	}

	private:
	const char *windowName;
	DWORD procId = -1; //let's hope these default values work
	HANDLE handle = 0;
	const char *moduleOffset = 0;
	const char *moduleName = "";

};