#include "DxLib.h"
#include "Window.h"
#include "GameController.h"
#include "GlobalValues.h"
using namespace Global;

namespace {
	int nowCount = 0;
	int oldCount = 0;
	int FrameTime = 0;	//1フレームあたりの経過時間
	int TimeCounter = 0;	//タイムカウンター
	const int BlendParam = 230; //アルファブレンドの値
	const unsigned int windowColor = GetColor( 30, 30, 200 );	//窓の色
	const unsigned int frameColor = GetColor( 255, 255, 255 );	//窓枠の色
	const unsigned int fontColor = GetColor( 255, 255, 255 ); //文字の色
}

//変数の初期化のみ
Window::Window() :
	mX(0),
	mY(0),
	mEndX( 0 ),
	mEndY( 0 ),
	mWinType(WINDOW_NONE){ }

void Window::drawWindow( int begX, int begY, int endX, int endY, WindowType winType ) {
	//メンバ初期化
	//resetMember();
	//開始位置
	mX = begX;	mY = begY;
	endX = ( endX > WindowWidth ) ? WindowWidth : endX;
	endY = ( endY > WindowHeight ) ? WindowHeight : endY;
	mEndX = endX; //ウィンドウ右下のｘ
	mEndY = endY; //ウィンドウ右下のｙ
	mWinType = winType; //窓の種類
	if ( mWinType == WINDOW_NONE ) {
		DrawFormatString( 300, 300, GetColor( 255, 0, 0 ), "arienai!!" );
		WaitKey();
		DxLib_End();
	}

	//描画
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, BlendParam ); //アルファブレンドモードにセット
	DrawBox( mX, mY, mEndX, mEndY, windowColor, true ); //窓描画
	if ( mWinType == WINDOW_LINE ) { //枠付きだったら
		drawWindowLine(); //枠を付ける
	}
	
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 ); //通常モードに戻す
}

void Window::drawHPBar( int x, int y, double percent ) {
	//真ん中を暗くするグラデーション.HPバーの縦は21px
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
	//外を囲む
	DrawBox( x , y , x + 201, y + 22, GetColor( 0, 90, 0 ), false );
}

//HPを段階的に減らす
void Window::reduceHP( double nowHP, double afterHP ) {
	oldCount = nowCount;
	nowCount = GetNowCount();
	FrameTime = nowCount - oldCount; //1フレームあたりの時間
	TimeCounter -= FrameTime; //タイムカウンターを経過時間分減らす
	int HPHandle = MakeGraph( 200, 21 );//HPバーの領域確保
	//TimeCounterが0以上の時は処理をしない
	if ( TimeCounter < 0 ) {
		;
	}
}

//ウィンドウの高さ
int Window::getHeight() const {
	return mEndY-mY;
}

//ウィンドウの幅
int Window::getWidth() const {
	return mEndX-mX;
}

void Window::drawListOnWindow( int arraySize,int cursorPos, char** list ) {
	int divideY = getHeight() / arraySize;
	for ( int i=0 ; i < arraySize; ++i ) {
		//カーソル表示
		if ( cursorPos == i ) {
			DrawBox( mX + 10, ( divideY*i )+mY+10, mEndX - 10, ( divideY*i ) +mY+ 32, GetColor( 150, 150, 255 ), true );
			//DrawFormatString( px, y+(50*i), GetColor( 255, 255, 255 ), "%d", cursorPos );
			//DrawTriangle( x+10, y+(50*i), x+10, (y+25)+(50*i), x+22, (y+13)+(50*i), GetColor( 255, 255, 255 ) ,true);
		}
		//文字描画
		DrawString( mX+20, divideY*i+mY+10, list[i], GetColor( 255, 255, 255 ) );
	}
}

/*内部関数*/
void Window::drawWindowLine() const {
	//DrawLineを使用
	
	DrawLine( mX-1,			mY-1,			mEndX,			mY-1,		frameColor,	2); //上
	DrawLine( mX-1,			mEndY,			mEndX,			mEndY,		frameColor,	2); //下
	DrawLine( mX-1,			mY-1,			mX-1,				mEndY,		frameColor,	2); //左
	DrawLine( mEndX,		mY-1,			mEndX,			mEndY,		frameColor,	2); //右
}

void Window::resetMember() {
	mX = 0;
	mY = 0;
	mEndX = 0;
	mEndY = 0;
	mMessage = 0;
	mWinType = WINDOW_NONE;
}