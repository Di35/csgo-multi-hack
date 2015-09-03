#include "threadhelper.h"

static DWORD WINAPI loop(functype func) {
	mem *csgo = new mem("Counter-Strike: Global Offensive");

	for (;;) {
		if (!csgo->checkForeGroundWindow()) {
			Sleep(100);
			continue;
		}

		csgo->setModule(mem::CLIENTDLL);
		csgo->openHandle();

		func(csgo);

		csgo->closeHandle();
		Sleep(5);
	}
	
	//TODO(nanocat): is "csgo" destroyed upon death of thread?
}

threadhelper::threadhelper(functype func) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&loop, func, 0, NULL);
}
