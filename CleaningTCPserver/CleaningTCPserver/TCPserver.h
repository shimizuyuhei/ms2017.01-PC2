#pragma once
#ifndef _INC_TCPSERVER    //�܂��ǂݍ��܂�Ă��Ȃ���Έȉ��̏���������
#define _INC_TCPSERVER    //���łɓǂݍ��܂�Ă���Ƃ����ڈ������

/*�C���N���[�h*/
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