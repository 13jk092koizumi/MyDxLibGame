#ifndef INCLUDED_GLOBALVALUES_H
#define INCLUDED_GLOBALVALUES_H

//#define SIZEOF(array) (sizeof(array) / sizeof*(array))
#define STR(var) #var //�����ɓ��镶���𕶎���ɕϊ�����}�N��

namespace Global {
	const int WindowWidth = 640;							//�E�B���h�E��
	const int WindowHeight = 480;						//�E�B���h�E�c
	const int FontSize = 20;									//�t�H���g�T�C�Y
	const int WaitFrame = 30;								//���t���[���҂�

	//�V�[�P���X�J�ڎ��Ɏg���B
	void moveScreen(int flamecount, char* message); //�V�[�P���X�ړ���
	//�����̃L�[�����͂���Ă��邩��Ԃ�
	bool isKeyOn( int );
	//boolalpha���ǂ�
	char* boolalpha(int);

} //namespace Global

#endif
