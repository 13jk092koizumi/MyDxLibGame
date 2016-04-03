#include "DxLib.h"
#include <climits>
#include "GameController.h"


namespace {
	const int MetricTimes = 60;			//fps�v����
	const int OneFrameMillsec = 16;		//1�t���[���̃~���b
	const int CountMax = INT_MAX;	//�J�E���^MAX
	const int KeyKindNum = 256;			//�L�[�̎��
	
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

//FPS�v���֐�
void GameController::calcFps() {
	fps[ mCount % MetricTimes ] = mWaitTime;	//1�T�̎��Ԃ��i�[
	if ( ( mCount % MetricTimes ) == ( MetricTimes - 1 ) ) {		//�v���񐔂ɒB������
		for ( int i = 0; i < MetricTimes; ++i ) {
			mFrameSpdAvg += fps[ i ];
		}
		mFrameSpdAvg /= MetricTimes;
	}
}

void GameController::graphFps() {
	if ( mFrameSpdAvg != 0 ) {
		//FPS���ς��O����Ȃ�������\��
		DrawFormatString( 0, 0, GetColor( 255, 255, 255 ),
			"FPS: %.1f", 1000.0 / (double)( mFrameSpdAvg ) );
	}
	
}

//FPS����
void GameController::controlFps() {
	mWaitTime = GetNowCount() - mPrevTime; //1�T�̏����ɂ����������Ԃ��v�Z
	if ( mPrevTime == 0 ) {
		//��ԍŏ���16����
		mWaitTime = OneFrameMillsec;
	}
	mPrevTime = GetNowCount();	//���݂̎������i�[
	if ( OneFrameMillsec > mWaitTime ) {
		//1�T�̏�����60fps��葬�������ꍇ
		//�҂�
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
			//�O�ɉ����ĂȂ��āA�������Ă�����
			key[ i ] = PressedNow;	//�����ꂽ�Ɣ���
		}
		prevKey[ i ] = key[ i ];		//���̓��͏�Ԃ�ۑ����Ă���
	}
}

//main�ŌĂ�
void GameController::control() {
	controlFps();	//FPS����
#ifdef _DEBUG
	calcFps();
	clsDx();
	graphFps();
#endif
	increaseCount(); //�J�E���^1����
}

GameController::GameController() :
	mCount(0),
	mFrameSpdAvg(0),
	mWaitTime(0),
	mPrevTime(0){
}
