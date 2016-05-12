#ifndef INCLUDED_WINDOW_H
#define INCLUDED_WINDOW_H

//��1�ɂ�1�N���X�p��
class Window{
public:
	enum WindowType {
		WINDOW_NORMAL,		//�g�Ȃ���
		WINDOW_LINE,			//�g���葋
		WINDOW_NO_TRANS, //�����Ȃ���
		WINDOW_NONE,			//�ǂ�ł��Ȃ�
	};
	
	Window( ); //�����͑��̑傫��x*y
	~Window() {}
	
	void drawWindow( int x1, int y1, int x2, int y2, WindowType ); //�E�B���h�E�`��.�����̓E�B���h�E�̊J�n�ʒu�A�I���ʒu�A�E�B���h�E�^�C�v
	
	void drawListOnWindow( int arraysize, int pos, char** list); //����:�z��̗v�f���A�J�[�\���|�W�V�����A���X�g�z��
	
	void drawHPBar( int x, int y, double percent ); //HP�o�[��\��(x,y,HP�̎c��%)
	
	void reduceHP( double nowHP, double afterHP ); //HP�o�[�����炷(����OHP%,��������HP%);
	
	int getHeight() const; //�E�B���h�E�c
	
	int getWidth() const; //�E�B���h�E��

private:
	void drawWindowLine() const; //�g�`��
	void resetMember(); //�����o������

	int mX;	//�\���ʒu�̍��Wx
	int mY; //�\���ʒu�̍��Wy
	int mEndX; //window�̒���X
	int mEndY; //window�̒���Y
	char* mMessage; //�\�����镶����̔z��
	WindowType mWinType;

};

#endif
