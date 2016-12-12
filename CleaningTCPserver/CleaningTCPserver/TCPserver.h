#pragma once
#ifndef _INC_TCPSERVER    //まだ読み込まれていなければ以下の処理をする
#define _INC_TCPSERVER    //すでに読み込まれているという目印をつける

/*インクルード*/
#include "Cleaning.h"

class TCPserver
{
private:

public:
	TCPserver(int portNum);
	void Send(char *data);
	~TCPserver();
};
#endif    //_INC_TCPSERVER