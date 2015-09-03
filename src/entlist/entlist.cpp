#include "entlist.h"

using namespace glob;

entlist::entlist(mem *imem) {
	imem = imem;
	imem->setModule(mem::CLIENTDLL);
	entlistPtr = mem::getCsgo()->readMemory<DWORD>(offsets::m_dwEntityList);
}

DWORD entlist::getEntPtrFromID(int id, mem *imem) {
	imem->setModule(mem::CLIENTDLL);
	return imem->readMemory<DWORD>(offsets::m_dwEntityList + (( id - 1 ) * 0x10));
}