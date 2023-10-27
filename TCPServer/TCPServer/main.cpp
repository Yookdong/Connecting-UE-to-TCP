#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include "PacketMaker.h"

#pragma comment(lib,"ws2_32.lib")
#define PACKET_SIZE_MAX 1024
using namespace std;

//----- MySQL -----
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

// 실험용 나중에 수정 필요함
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "ehggur0347!";

sql::Driver* SQL_Driver;
sql::Connection* SQL_Connection;
sql::Statement* SQL_State;
sql::ResultSet* SQL_Result;
//----------

fd_set Reads; // 원본
fd_set CopyReads; // 복사본

unsigned WINAPI Thread_Server(void* arg);

int main()
{
	//----- DB 관련 코드 생성 -----
	//try
	//{
	//	SQL_Driver = get_driver_instance();
	//	SQL_Connection = SQL_Driver->connect(server, username, password); // 서버 연결
	//	cout << "DB Server Connect Success\n";
	//}
	//catch (sql::SQLException e)
	//{
	//	cout << "Could not connect to server. Error message: " << e.what() << endl;
	//	system("pause");
	//	exit(1);
	//}

	// 미리 생성해 둔 스키마 연결
	//SQL_Connection->setSchema("dbserver_tcp");
	//----------

	cout << "Server Start\n";

	WSADATA WsaData;

	int Result = WSAStartup(MAKEWORD(2, 2), &WsaData);

	if (Result != 0)
	{
		cout << "WSADATA Error" << endl;
		exit(-1);
	}

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "ListenSocket Error Num : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 나중에 서버 주소 바꿀 것
	ListenSockAddr.sin_port = htons(7777); // port 번호도 바꿔

	Result = _WINSOCK2API_::bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	if (Result != 0)
	{
		cout << "Bind Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	Result = listen(ListenSocket, SOMAXCONN);

	if (Result == SOCKET_ERROR)
	{
		cout << "Listen Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	// Thread 용
	struct timeval Timeout;
	Timeout.tv_sec = 0;
	Timeout.tv_usec = 500;

	FD_ZERO(&Reads);
	FD_SET(ListenSocket, &Reads);

	printf("Wait for Connecting\n");

	while (true)
	{
		CopyReads = Reads;

		int changeSocketCunt = select(0, &CopyReads, 0, 0, &Timeout);

		if (changeSocketCunt <= 0)
		{
			continue;
		}
		else
		{
			for (int i = 0; i < (int)Reads.fd_count; ++i)
			{
				if (FD_ISSET(Reads.fd_array[i], &CopyReads))
				{
					if (Reads.fd_array[i] == ListenSocket)
					{
						SOCKADDR_IN ClientSockAddr;
						ZeroMemory(&ClientSockAddr, sizeof(ClientSockAddr));
						int ClientSockAddrLength = sizeof(ClientSockAddr);

						SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

						if (ClientSocket == INVALID_SOCKET)
						{
							cout << "Accept Error Number : " << GetLastError() << endl;
							continue;
						}

						FD_SET(ClientSocket, &Reads);
						CopyReads = Reads;

						char IP[1024] = { 0, };
						inet_ntop(AF_INET, &ClientSockAddr.sin_addr.s_addr, IP, 1024);
						cout << (unsigned short)ClientSocket << " connected : " << IP << endl;

						_beginthreadex(nullptr, 0, Thread_Server, (void*)&ClientSocket, 0, nullptr);

						break;
					}
				}
			}
		}
	}

	closesocket(ListenSocket);
	WSACleanup();

	delete SQL_Connection;

	system("pause");

	return 0;
}

unsigned __stdcall Thread_Server(void* arg)
{
	return 0;
}
