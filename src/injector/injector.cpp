//by meep
//TODO(nanocat): This code is clusterfuck, it's recommended that you rewrite it.

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <time.h>
#include <psapi.h>

#include <stdio.h>
#include <stdlib.h>

namespace injector {
	char valid_chars[] = { // yes i know i can do this better but i am lazy
		'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
	};

	/* void quit(const char *format, ...)
	{
		va_list args;

		va_start(args, format);
		vprintf(format, args);
		va_end(args);

		std::cin.get();
		ExitProcess(0); // do not use this, use exit() instead
	} */
	
	template<typename... Args>
	void quit(const char *message, Args... vargs)
	{
		printf(message, vargs...);
		exit(0);
	}

	// not entirely mine
	__forceinline const char *GetProcessName(DWORD pid)
	{
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

		if (!process)
		{
			CloseHandle(process);
			return "";
		}
		char filename[MAX_PATH + 1] = { 0 };

		HMODULE module;
		DWORD junk;


		if (EnumProcessModules(process, &module, sizeof(module), &junk))
		{
			GetModuleBaseNameA(process, module, filename, sizeof(filename));
		}
		CloseHandle(process);

		return filename; // ignore the warning, it's inline
	}

	void inject(const char *process, const char *old_dllname)
	{
		FILE *file;
		fopen_s(&file, old_dllname, "rb");

		if (!file)
			quit("file bad");

		char temp_path[MAX_PATH];
		GetTempPathA(MAX_PATH, temp_path);

		char dllname[MAX_PATH];
		sprintf_s(dllname, "%s%c%c%c%c%c%c%c%c.txt",
			temp_path,
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)],
			valid_chars[rand() % sizeof(valid_chars)]);

		FILE *newfile;
		fopen_s(&newfile, dllname, "wb");

		fseek(file, 0, SEEK_END);
		long len = ftell(file);
		char *temp = new char[len];
		fseek(file, 0, SEEK_SET);

		size_t size = fread(temp, 1, len, file);

		fwrite(temp, 1, size, newfile);

		fclose(file);
		fclose(newfile);

		delete[] temp;

		HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

		THREADENTRY32 entry;
		entry.dwSize = sizeof(entry);

		BOOL good = true;

		for (Thread32First(snap, &entry); good; good = Thread32Next(snap, &entry))
		{
			if (strcmp(GetProcessName(entry.th32OwnerProcessID), process) == 0)
			{
				// make sure people can't complain it's an error number from opening invalid processes and shit before
				SetLastError(0);
				printf("Thread id %i\n", entry.th32ThreadID);

				// open our process and thread so we can do things
				HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32OwnerProcessID);
				HANDLE thread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, entry.th32ThreadID);

				// suspend that shit so it doesn't move! if it moves kill it!
				SuspendThread(thread);

				CONTEXT context;
				CONTEXT new_ctx;

				context.ContextFlags = CONTEXT_FULL;
				GetThreadContext(thread, &context);

				memcpy(&new_ctx, &context, sizeof(CONTEXT));

				// set active code to execute
				new_ctx.Eip = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

				// fix stack for our function call
				new_ctx.Esp = new_ctx.Esp - 0x8;

				// write the return address
				WriteProcessMemory(hprocess, (LPVOID)(new_ctx.Esp),
					&context.Eip,
					sizeof(context.Eip), NULL);

				size_t dll_len = strlen(dllname);
				DWORD write = new_ctx.Esp - dll_len - 0x200;

				// write our dll name's pointer-to-be
				WriteProcessMemory(hprocess, (LPVOID)(new_ctx.Esp + 4), &write, sizeof(write), NULL);

				// write our dll name in a safe spot
				WriteProcessMemory(hprocess, (LPVOID)write, dllname, dll_len + 1, NULL);

				// set the registers in the thread
				SetThreadContext(thread, &new_ctx);


				// make the thread run again
				ResumeThread(thread);

				// close our handles

				CloseHandle(thread);
				CloseHandle(hprocess);
				CloseHandle(snap);
				Sleep(1000);
				char last_location[MAX_PATH];
				sprintf_s(last_location, "%s%c%c%c%c%c%c%c%c.txt",
					temp_path,
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)],
					valid_chars[rand() % sizeof(valid_chars)]);
				MoveFileA(dllname, last_location);

				fopen_s(&newfile, dllname, "wb");
				fwrite("MZ", 1, 1, newfile);
				fclose(newfile);
				quit("Found! last error: %i\nInjected name: %s\nWrote %p for LoadLibraryA\n", GetLastError(), dllname, new_ctx.Eip);
				break; // not really needed but yolo
			}
		}
		CloseHandle(snap);

		fopen_s(&newfile, dllname, "wb");
		fwrite("\x00", 1, 1, newfile);
		fclose(newfile);
		quit("Didn't work!!!!! (process not found) \n");
	}
}
