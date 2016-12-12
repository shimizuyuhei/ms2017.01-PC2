#include "TCPserver.h"

SOCKET s, s1;         //ソケット
int result;          //戻り値
						//接続を許可するクライアント端末の情報
struct sockaddr_in source;
char buffer[1024];  //受信データのバッファ領域
char ans[] = { 0xff };
char ret;

TCPserver::TCPserver(int portNum)
{

	memset(&buffer, '\0', sizeof(buffer));
	//送信元の端末情報を登録する
	memset(&source, 0, sizeof(source));
	source.sin_family = AF_INET;
	//ポート番号はクライアントプログラムと共通
	source.sin_port = htons(9876);
	source.sin_addr.s_addr = htonl(INADDR_ANY);

	//ソケット通信の開始準備
	WSADATA data;
	result = WSAStartup(MAKEWORD(2, 0), &data);
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("ソケット通信準備エラー\n");
	}

	//ソケットの生成
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s < 0) {
		printf("%d\n", GetLastError());
		printf("ソケット生成エラー\n");
	}

	//ソケットのバインド
	result = bind(s, (struct sockaddr *)&source, sizeof(source));
	if (result < 0) {
		printf("%d\n", GetLastError());
		printf("バインドエラー\n");
	}

	//接続の許可
	result = listen(s, 1);
	if (result < 0) {
		printf("接続許可エラー\n");
	}

	printf("接続開始\n");

	
}

void TCPserver::Send(char *data)
{
	
	//クライアントから通信があるまで待機
	s1 = accept(s, NULL, NULL);
	if (s1 < 0) {
		printf("待機エラー\n");
	}

	//クライアントから送信されたデータの受信
	//result = recv(s1, buffer, 10, 0);
	//if (result < 0) {
	//	printf("受信エラー\n");
	//}
	//printf("%sを受信しました", buffer);

	//クライアントへデータを送信する
	result = send(s1, ans, 10, 0);

}

TCPserver::~TCPserver()
{
	printf("デストラクタ呼び出し\n");

	printf("接続終了\n");
	closesocket(s1);

	//ソケット通信の終了
	WSACleanup();
}
