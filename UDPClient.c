// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
//#include <Ws2tcpip.h>

#include <stdio.h>
#include <conio.h>

#include "addr.h"

//#include "addr.h"

#define USEC (10L)//������������- 10 ����� L-��� long
#define MSEC (1000*USEC)//�����������
//������ � ������� �������������



int mul(int a, int b);

int main(int argc, char* argv[])
{	//char a[5] = {'h','e','3','4',0};
	// Declare and initialize variables.
	ADDR ext_addr;
	
	WSADATA wsaData;
   int iResult;

    SOCKET SendSocket = INVALID_SOCKET;
    struct sockaddr_in clientService; 
	 struct sockaddr_in SendAddr;


    char *sendbuf = "this is a test";
   //������� ��������� ��� ������� �������� �������
	struct 
	{  LARGE_INTEGER time;
	   int num;
	   int marker;
	}  packet;//����� -�� ��� ���������, � ��� ������� ������ ���������

	char *a="he34";
	int sss=(int)a;
   int port;
	char*p=a;
	int res;
	int ip[4];
	unsigned long addr;
	printf(p);//����������� ������� ���� �� �������� ���� ��� ������ ������
   //��� %-���� ������� �����������
	//��������� ���������
	//res=sscanf(argv[1], "port=%d", &port);
	//if (res!=1)
	//{  return 1;
	//}
	res=sscanf(argv[1], "%d.%d.%d.%d:%d", &ip[3], &ip[2], &ip[1], &ip[0],&port);
	if (res!=5)
	{  return 2;
	}
	addr=(ip[3]<<24) | (ip[2]<<16) | (ip[1]<<8) | ip[0];
	
	set_addr(addr,port,&ext_addr);//���������=��������� ����������,
   // 3 =����� ��������� (��������� �����������)
	    //----------------------
//addr = 0 -�������� ��������
//port=8 �������� ��������
//ext_addr.port = 7;�������� ����� ��������� 
//(&ext_addr)->port=7;
    
  
    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR) {
      printf("WSAStartup failed: %d\n", iResult);
      return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SendSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

 //---------------------------------------------
    // Set up the SendAddr structure with the IP address of
    // the receiver (in this example case "192.168.1.1")
    // and the specified port number.
    SendAddr.sin_family = AF_INET;
    SendAddr.sin_port = htons(port);
   // SendAddr.sin_addr.s_addr = inet_addr("192.168.1.1");
	SendAddr.sin_addr.s_addr = htonl( ext_addr.ip) ;
  // SendAddr.sin_addr.S_un.S_addr = htol//������������ 
  //(define ������� ���������� �� ���� � ����) 
    //---------------------------------------------
    // Send a datagram to the receiver
    
    MessageBox(NULL,TEXT("test"),TEXT(""), MB_OK);
    wprintf(L"Sending a datagram to the receiver...\n");
	//������� ����������
	{  HANDLE hTimer=CreateWaitableTimer(NULL,FALSE,NULL);
		LARGE_INTEGER  dT;

		//�������� ������� ���� ��� �� ����,��� �� ���������
	    LARGE_INTEGER Frequency;
		
		int i;
		LARGE_INTEGER start_time;
		LARGE_INTEGER cur_time;

        //����� �������� (��������)
	   cur_time.QuadPart=0;//quadpart-���������� ���  � 64 �������
		packet.marker=0x1234;//16 ������
		QueryPerformanceFrequency(&Frequency);
      //��������� ���������- �������� �� ������ frequency
      //������� �������� ������� �������
      //������� ����������- � ����� ����� ��������� �����
      //-����� �� ������ ������� ����������
      //��������� �������� ������� ���������
		//for (i = 0; i < 10000; i++)
		for (i = 0;  ; i++)
		{	dT.QuadPart=-1000*USEC;//Waitable timer-���� �������� ����� �����
      //1�����������-����� ����� ����� ������ 1 �����������
			SetWaitableTimer(hTimer,&dT,0, NULL,NULL,0);
			WaitForSingleObject(hTimer, INFINITE);//���� ���� �������-htimer
//	        Sleep(10);
			packet.num = i;
			//��������� �����
			packet.time = cur_time;//����� ���� ���� ������
         	
         QueryPerformanceCounter(&cur_time);
    		iResult = sendto(SendSocket, (char *) &packet, sizeof(packet), 0, (SOCKADDR *) & SendAddr, sizeof (SendAddr));
			//�������� ����� ������������� ������ ��� ���� ������
		   
            //if (i!=0)
         if (1)
         {	//cur_time.QuadPart-=start_time.QuadPart;
				cur_time.QuadPart *= 1000000;
				cur_time.QuadPart /= Frequency.QuadPart;
			}
			else
			{   start_time=cur_time;//���� ������� �� ��������
			}
			
			if (iResult == SOCKET_ERROR) 
			{   wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
				closesocket(SendSocket);
				WSACleanup();
				return 1;
			}
		}
	}

	printf("OK\n");

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
   // clientService.sin_family = AF_INET;
   // clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
   // clientService.sin_port = htons( 27015 );

   //������ �� ��������� ������ ����� ����� - ��� �� �����
    //----------------------
	//����� ���������� �������
 
//{	printf("Hello World!\n");
//  printf("s=%d %d %d", mul(3,4), mul(4,0), mul(1,1));
    _getch();
//	r[eturn 0;
	return ;
}

