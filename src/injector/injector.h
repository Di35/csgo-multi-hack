#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <time.h>
#include <psapi.h>

namespace injector {
	void inject(const char *process, const char *old_dllname);
}