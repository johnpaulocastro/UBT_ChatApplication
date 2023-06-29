#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <WS2tcpip.h>

#pragma comment (lib, "WS2_32.lib")

using namespace std;

void Server();
