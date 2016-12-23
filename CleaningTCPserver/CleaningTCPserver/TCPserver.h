#pragma once
#ifndef _INC_TCPSERVER    //�܂��ǂݍ��܂�Ă��Ȃ���Έȉ��̏���������
#define _INC_TCPSERVER    //���łɓǂݍ��܂�Ă���Ƃ����ڈ������

/*�C���N���[�h*/
#include <thread>
#include "Cleaning.h"

class TCPserver
{
private:

public:

	/*TCP�ʐM�T�[�o*/
	TCPserver(int portNum); /*�R���X�g���N�^*/
	
	/*Thread*/
	void WaitConnect();
	void WaitRead();
	void Send(char *data);
	~TCPserver();	/*�f�X�g���N�^*/
};

#endif    //_INC_TCPSERVER