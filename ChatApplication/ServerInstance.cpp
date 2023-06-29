#include "ServerInstance.h"

void Server()
{
	system("cls");

	cout << "===================================================" << endl;
	cout << "------------------SERVER INSTANCE------------------" << endl;
	cout << "===================================================" << endl;

	string username;
	string password;
	char ch;

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

	cout << "===================================================" << endl;
	cout << "--------------WELCOME TO THE CHATROOM--------------" << endl;
	cout << "===================================================" << endl;

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

	// Do here: Bind the IP Address and Port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	char shost[256];
	int hostname = gethostname(shost, sizeof(shost));
	struct hostent* host_entry = gethostbyname(shost);
	char* IP = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

	cout << "IP Address : " << (string)IP << endl;
	cout << "Port Number : 54000 " << endl;

	// Do here: Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Do here: Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		// client's remote name
	char service[NI_MAXSERV];	// Service (i.e port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	// Do here: Close listening socket
	closesocket(listening);

	// Do here: While Loop: accept and echo message back to client
	char msg[4096];

	while (true)
	{
		ZeroMemory(&msg, sizeof(&msg));
		recv(clientSocket, (char*)&msg, sizeof(msg), 0);
		cout << msg << endl;

		string data;
		cout << username << ": ";
		cin >> data;
		data = username + ": " + data;

		ZeroMemory(&msg, sizeof(&msg));
		strcpy(msg, data.c_str());
		send(clientSocket, (char*)&msg, strlen(msg), 0);
	}



	// Do here: Close the socket
	closesocket(clientSocket);

	// Do here: Cleanup Winsock
	WSACleanup();
}