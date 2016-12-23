#pragma once
#ifndef _INC_TCPSERVER    //まだ読み込まれていなければ以下の処理をする
#define _INC_TCPSERVER    //すでに読み込まれているという目印をつける

/*インクルード*/
#include <thread>
#include "Cleaning.h"

class TCPserver
{
private:

public:

	/*TCP通信サーバ*/
	TCPserver(int portNum); /*コンストラクタ*/
	
	/*Thread*/
	void WaitConnect();
	void WaitRead();
	void Send(char *data);
	~TCPserver();	/*デストラクタ*/
};

#endif    //_INC_TCPSERVER