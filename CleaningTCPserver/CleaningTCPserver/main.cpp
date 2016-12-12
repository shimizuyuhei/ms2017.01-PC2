#include "main.h"

void main() {
	TCPserver Server(9876);
	Server.Send("a");
}