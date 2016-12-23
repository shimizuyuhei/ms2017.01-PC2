#include "main.h"
#include <conio.h>

void main() {
	TCPserver Server(9876);
	char tex[1] = {0};
	while (1)
	{
		tex[0] = _getch();
		printf("%x\n", tex[0]);
		Server.Send(tex);
	}

}