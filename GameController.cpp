#include "DxLib.h"
#include <climits>
#include "GameController.h"


namespace {
	const int MetricTimes = 60;			//fps計測回数
	const int OneFrameMillsec = 16;		//1フレームのミリ秒
	const int CountMax = INT_MAX;	//カウンタMAX
	const int KeyKindNum = 256;			//キーの種類
	
	int fps[ MetricTimes ];
	char key[ KeyKindNum ];
	char prevKey[ KeyKindNum ];

} //namespace

GameController* GameController::mInstance = 0;

GameController* GameController::instance() {
	return mInstance;
}

void GameController::create() {
	mInstance = new GameController;
}

void GameController::destroy() {
		delete mInstance;
		mInstance = 0;
}

//FPS計測関数
void GameController::calcFps() {
	fps[ mCount % MetricTimes ] = mWaitTime;	//1週の時間を格納
	if ( ( mCount % MetricTimes ) == ( MetricTimes - 1 ) ) {		//計測回数に達したら
		for ( int i = 0; i < MetricTimes; ++i ) {
			mFrameSpdAvg += fps[ i ];
		}
		mFrameSpdAvg /= MetricTimes;
	}
}

void GameController::graphFps() {
	if ( mFrameSpdAvg != 0 ) {
		//FPS平均が０じゃなかったら表示
		DrawFormatString( 0, 0, GetColor( 255, 255, 255 ),
			"FPS: %.1f", 1000.0 / (double)( mFrameSpdAvg ) );
	}
	
}

//FPS制御
void GameController::controlFps() {
	mWaitTime = GetNowCount() - mPrevTime; //1週の処理にかかった時間を計算
	if ( mPrevTime == 0 ) {
		//一番最初は16を代入
		mWaitTime = OneFrameMillsec;
	}
	mPrevTime = GetNowCount();	//現在の時刻を格納
	if ( OneFrameMillsec > mWaitTime ) {
		//1週の処理に60fpsより速かった場合
		//待つ
		Sleep( static_cast<DWORD>( OneFrameMillsec - mWaitTime ) );
	}

}

char GameController::getKey( int input ) const {
	return key[ input ];
}

int GameController::getAllKeyPressed() const {
	return GetHitKeyStateAll( key );
}

void GameController::increaseCount() {
	mCount;
	if ( mCount >= CountMax ) {
		mCount = 0;
	}
}

int GameController::GetmCount() const {
	return mCount;
}

void GameController::adjustKeyState() {
	for ( int i = 0; i < KeyKindNum; i++ ) {
		if ( prevKey[ i ] == NotPressed && key[ i ] == Pressed ) {
			//前に押してなくて、今押していたら
			key[ i ] = PressedNow;	//押されたと判定
		}
		prevKey[ i ] = key[ i ];		//今の入力状態を保存しておく
	}
}

//mainで呼ぶ
void GameController::control() {
	controlFps();	//FPS制御
#ifdef _DEBUG
	calcFps();
	clsDx();
	graphFps();
#endif
	increaseCount(); //カウンタ1増加
}

GameController::GameController() :
	mCount(0),
	mFrameSpdAvg(0),
	mWaitTime(0),
	mPrevTime(0){
}
