#include "TCPserver.h"

int result;          //�߂�l
						//�ڑ���������N���C�A���g�[���̏��
/*�T�[�o*/
SOCKET sksr;       //�\�P�b�g�T�[�o
struct sockaddr_in srcAddr;

/*�N���C�A���g*/
SOCKET skct1;         //�\�P�b�g
struct sockaddr_in dstAddr;

char buffer[1023];  //��M�f�[�^�̃o�b�t�@�̈�
char ret;

TCPserver::TCPserver(int portNum)
{
	std::thread thd(&TCPserver::WaitConnect, this);
	thd.join();
}

void TCPserver::WaitConnect()
{
	//int dstAddrSize = sizeof(dstAddr);

	//���M���̒[������o�^����
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_family = AF_INET;

	//�|�[�g�ԍ��̓N���C�A���g�v���O�����Ƌ���
	srcAddr.sin_port = htons(9876);
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//�\�P�b�g�ʐM�̊J�n����
	WSADATA data;
	result = WSAStartup(MAKEWORD(2, 0), &data);
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("�\�P�b�g�ʐM�����G���[\n");
		return;
	}

	//�\�P�b�g�̐���
	/*WinSock1.1, TCP, 0*/
	sksr = socket(AF_INET, SOCK_STREAM, 0);
	if (sksr < 0) {
		printf("%d\n", GetLastError());
		printf("�\�P�b�g�����G���[\n");
		return;
	}

	//�\�P�b�g�̃o�C���h
	result = bind(sksr, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("�o�C���h�G���[\n");
		return;
	}

	//�ڑ��̋���
	result = listen(sksr, 1);
	if (result < 0) {
		printf("�ڑ����G���[\n");
		return;
	}

	printf("�ڑ��J�n\n");

	/*�T�[�o��t�I��*/
	//closesocket(sksr);

	/*��M����*/
	//std::thread thd(&TCPserver::WaitRead, this);
	//thd.join();
}

void TCPserver::WaitRead()
{
	do {
		//�N���C�A���g���瑗�M���ꂽ�f�[�^�̎�M
		result = recv(skct1, buffer, 1023, 0);
		if (result < 0) {
			printf("��M�G���[\n");
			break;
		}
		printf("%s����M���܂���\n", buffer);

	} while (true);

}

void TCPserver::Send(char *data)
{
	int dstAddrSize = sizeof(dstAddr);
	int dataSize = sizeof(*data);

	do {
		skct1 = accept(sksr, (struct sockaddr *) &dstAddr, &dstAddrSize);
		if (skct1 < 0) {
			printf("�ҋ@�G���[\n");
			return;
		}

		//�N���C�A���g�փf�[�^�𑗐M����
		result = send(skct1, data, dataSize, 0);

		printf("%d,\n", dataSize);

		closesocket(skct1);

	} while (result < 0);


}

TCPserver::~TCPserver()
{
	printf("�ڑ��I��\n");

	//�\�P�b�g�ʐM�̏I��
	WSACleanup();

	printf("�f�X�g���N�^�Ăяo��\n");
}