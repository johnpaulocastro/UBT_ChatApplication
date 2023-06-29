#include "ClientInstance.h"

void Client()
{
	system("cls");

	cout << "===================================================" << endl;
	cout << "------------------CLIENT INSTANCE------------------" << endl;
	cout << "===================================================" << endl;

	string ipaddress;
	int portnum;
	string username;
	string password;
	char ch;

	cout << "Please enter server IP : ";
	cin >> ipaddress;
	cout << "Please enter server port : ";
	cin >> portnum;
	cout << "Please enter username : ";
	cin >> username;
	cout << "Please enter password : ";
	ch = _getch();
	while (ch != 13) {
		if (ch == 8) {
			if (password.length()) {
				cout << "\b \b";
				password.pop_back();
			}
			ch = _getch();
			continue;
		}

		//character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	cout << endl;

	// Do here: Initialize Winsock
	WSADATA wsData;

	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (wsOk != 0)
	{
		cerr << "Initializing winsock failed! Exiting..." << endl;
		return;
	}
	
	// Do here: Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Socket failed! Exiting..." << endl;
		return;
	}

	char* ipAdd = new char[ipaddress.length() + 1];
	strcpy(ipAdd, ipaddress.c_str());
	struct hostent* host = gethostbyname(ipAdd);

	sockaddr_in hint;
	ZeroMemory((char*)&hint, sizeof(hint));
	hint.sin_family = AF_INET;
	hint.sin_port = htons(portnum);
	hint.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	
	int status = connect(listening, (sockaddr*)&hint, sizeof(hint));
	if (status < 0)
	{
		cout << "Error connecting to socket!" << endl;
	}
	else 
	{
		cout << "===================================================" << endl;
		cout << "--------------WELCOME TO THE CHATROOM--------------" << endl;
		cout << "===================================================" << endl;
		cout << "Connected to server!" << endl;

		char msg[4096];
		while (1)
		{
			string data;
			cout << username << ": ";
			cin >> data;
			data = username + ": " + data;
			
			ZeroMemory(&msg, sizeof(&msg));
			strcpy(msg, data.c_str());
			send(listening, (char*)&msg, strlen(msg), 0);
			
			ZeroMemory(&msg, sizeof(&msg));
			recv(listening, (char*)&msg, sizeof(msg), 0);
			cout << msg << endl;
		}

		closesocket(listening);
	}
}
