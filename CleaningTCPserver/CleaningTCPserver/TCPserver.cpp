#include "TCPserver.h"

int result;          //戻り値
						//接続を許可するクライアント端末の情報
/*サーバ*/
SOCKET sksr;       //ソケットサーバ
struct sockaddr_in srcAddr;

/*クライアント*/
SOCKET skct1;         //ソケット
struct sockaddr_in dstAddr;

char buffer[1023];  //受信データのバッファ領域
char ret;

TCPserver::TCPserver(int portNum)
{
	std::thread thd(&TCPserver::WaitConnect, this);
	thd.join();
}

void TCPserver::WaitConnect()
{
	//int dstAddrSize = sizeof(dstAddr);

	//送信元の端末情報を登録する
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_family = AF_INET;

	//ポート番号はクライアントプログラムと共通
	srcAddr.sin_port = htons(9876);
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//ソケット通信の開始準備
	WSADATA data;
	result = WSAStartup(MAKEWORD(2, 0), &data);
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("ソケット通信準備エラー\n");
		return;
	}

	//ソケットの生成
	/*WinSock1.1, TCP, 0*/
	sksr = socket(AF_INET, SOCK_STREAM, 0);
	if (sksr < 0) {
		printf("%d\n", GetLastError());
		printf("ソケット生成エラー\n");
		return;
	}

	//ソケットのバインド
	result = bind(sksr, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("バインドエラー\n");
		return;
	}

	//接続の許可
	result = listen(sksr, 1);
	if (result < 0) {
		printf("接続許可エラー\n");
		return;
	}

	printf("接続開始\n");

	/*サーバ受付終了*/
	//closesocket(sksr);

	/*受信処理*/
	//std::thread thd(&TCPserver::WaitRead, this);
	//thd.join();
}

void TCPserver::WaitRead()
{
	do {
		//クライアントから送信されたデータの受信
		result = recv(skct1, buffer, 1023, 0);
		if (result < 0) {
			printf("受信エラー\n");
			break;
		}
		printf("%sを受信しました\n", buffer);

	} while (true);

}

void TCPserver::Send(char *data)
{
	int dstAddrSize = sizeof(dstAddr);
	int dataSize = sizeof(*data);

	do {
		skct1 = accept(sksr, (struct sockaddr *) &dstAddr, &dstAddrSize);
		if (skct1 < 0) {
			printf("待機エラー\n");
			return;
		}

		//クライアントへデータを送信する
		result = send(skct1, data, dataSize, 0);

		printf("%d,\n", dataSize);

		closesocket(skct1);

	} while (result < 0);


}

TCPserver::~TCPserver()
{
	printf("接続終了\n");

	//ソケット通信の終了
	WSACleanup();

	printf("デストラクタ呼び出し\n");
}