#include "main.h"
#include "player/baseplayer.h"
#include "player/localplayer.h"
#include "entlist/entlist.h"

#include "modules/triggerbot.h"
#include "modules/noflash.h"
#include "modules/glow.h"
#include "modules/norecoil.h"

using namespace glob;

int main(char *argv[], int argc) {
	printf("running...\n");

	mem *csgo = mem::getCsgo();

	printf("%s\n", csgo->getWindowName());

	triggerbot trigger;
	//noflash noflaash;
	//glow gloow;
	//norecoil noreil;



	for (;;) {}

	return 0;
}