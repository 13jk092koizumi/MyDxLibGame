#include "DxLib.h"
#include "Window.h"
#include "GameController.h"
#include "GlobalValues.h"
using namespace Global;

namespace {
	int nowCount = 0;
	int oldCount = 0;
	int FrameTime = 0;	//1�t���[��������̌o�ߎ���
	int TimeCounter = 0;	//�^�C���J�E���^�[
	const int BlendParam = 230; //�A���t�@�u�����h�̒l
	const unsigned int windowColor = GetColor( 30, 30, 200 );	//���̐F
	const unsigned int frameColor = GetColor( 255, 255, 255 );	//���g�̐F
	const unsigned int fontColor = GetColor( 255, 255, 255 ); //�����̐F
}

//�ϐ��̏������̂�
Window::Window() :
	mX(0),
	mY(0),
	mEndX( 0 ),
	mEndY( 0 ),
	mWinType(WINDOW_NONE){ }

void Window::drawWindow( int begX, int begY, int endX, int endY, WindowType winType ) {
	//�����o������
	//resetMember();
	//�J�n�ʒu
	mX = begX;	mY = begY;
	endX = ( endX > WindowWidth ) ? WindowWidth : endX;
	endY = ( endY > WindowHeight ) ? WindowHeight : endY;
	mEndX = endX; //�E�B���h�E�E���̂�
	mEndY = endY; //�E�B���h�E�E���̂�
	mWinType = winType; //���̎��
	if ( mWinType == WINDOW_NONE ) {
		DrawFormatString( 300, 300, GetColor( 255, 0, 0 ), "arienai!!" );
		WaitKey();
		DxLib_End();
	}

	//�`��
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, BlendParam ); //�A���t�@�u�����h���[�h�ɃZ�b�g
	DrawBox( mX, mY, mEndX, mEndY, windowColor, true ); //���`��
	if ( mWinType == WINDOW_LINE ) { //�g�t����������
		drawWindowLine(); //�g��t����
	}
	
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 ); //�ʏ탂�[�h�ɖ߂�
}

void Window::drawHPBar( int x, int y, double percent ) {
	//�^�񒆂��Â�����O���f�[�V����.HP�o�[�̏c��21px
	int green = 0;
	double remainHP = 200.0*(percent / 100.0);
	for ( int i = 1; i <= 21; ++i ) {
		if ( i < 10 ) {
			green = 255 - ( i *12 );
			DrawLine( x , y + i, x + (int)remainHP , y + i, GetColor( 0, green, 0 ) );
		}
		else if ( i == 10 ) {
			DrawLine( x , y + i, x + (int)remainHP, y + i, GetColor( 0, 140, 0 ) );
		}else if ( i > 10 ) {
			green = 255 - ( (21-i) * 12 );
			if ( green > 255 ) green = 255;
			DrawLine( x , y + i, x + (int)remainHP, y + i, GetColor( 0, green, 0 ) );
		}
	}
	//�O���͂�
	DrawBox( x , y , x + 201, y + 22, GetColor( 0, 90, 0 ), false );
}

//HP��i�K�I�Ɍ��炷
void Window::reduceHP( double nowHP, double afterHP ) {
	oldCount = nowCount;
	nowCount = GetNowCount();
	FrameTime = nowCount - oldCount; //1�t���[��������̎���
	TimeCounter -= FrameTime; //�^�C���J�E���^�[���o�ߎ��ԕ����炷
	int HPHandle = MakeGraph( 200, 21 );//HP�o�[�̗̈�m��
	//TimeCounter��0�ȏ�̎��͏��������Ȃ�
	if ( TimeCounter < 0 ) {
		;
	}
}

//�E�B���h�E�̍���
int Window::getHeight() const {
	return mEndY-mY;
}

//�E�B���h�E�̕�
int Window::getWidth() const {
	return mEndX-mX;
}

void Window::drawListOnWindow( int arraySize,int cursorPos, char** list ) {
	int divideY = getHeight() / arraySize;
	for ( int i=0 ; i < arraySize; ++i ) {
		//�J�[�\���\��
		if ( cursorPos == i ) {
			DrawBox( mX + 10, ( divideY*i )+mY+10, mEndX - 10, ( divideY*i ) +mY+ 32, GetColor( 150, 150, 255 ), true );
			//DrawFormatString( px, y+(50*i), GetColor( 255, 255, 255 ), "%d", cursorPos );
			//DrawTriangle( x+10, y+(50*i), x+10, (y+25)+(50*i), x+22, (y+13)+(50*i), GetColor( 255, 255, 255 ) ,true);
		}
		//�����`��
		DrawString( mX+20, divideY*i+mY+10, list[i], GetColor( 255, 255, 255 ) );
	}
}

/*�����֐�*/
void Window::drawWindowLine() const {
	//DrawLine���g�p
	
	DrawLine( mX-1,			mY-1,			mEndX,			mY-1,		frameColor,	2); //��
	DrawLine( mX-1,			mEndY,			mEndX,			mEndY,		frameColor,	2); //��
	DrawLine( mX-1,			mY-1,			mX-1,				mEndY,		frameColor,	2); //��
	DrawLine( mEndX,		mY-1,			mEndX,			mEndY,		frameColor,	2); //�E
}

void Window::resetMember() {
	mX = 0;
	mY = 0;
	mEndX = 0;
	mEndY = 0;
	mMessage = 0;
	mWinType = WINDOW_NONE;
}