#include "Animation.h"

Animation::Animation( int flameNum, int divideNum ) : mCount( 0 ), mIsAnimating( false ) ,mNowDivNum(0)
{
	mEndCount = flameNum; //���t���[���A�j���[�V�������邩
	mValidTiming = flameNum/divideNum; //���R�}���Ƃɐ؂�ւ��邩
	mValidTiming = ( mValidTiming < 1 ) ? 1 : mValidTiming;
	start(); //�A�j���[�V�����X�^�[�g
}

Animation::~Animation(){
	//�������Ȃ�
}

bool Animation::animate() {
	//mEndCount�ɂȂ�܂ŃJ�E���^����
	++mCount;
	
	//�A�j���[�V�����̏I������
	if ( mCount > mEndCount ) {
		mIsAnimating = false; //�A�j���[�V�����̏I��
		return false;
	}
	
	int nowDivNum = mCount % mValidTiming;
	//mValidTiming�Ŋ���؂��Ƃ�true�ԋp
	if ( nowDivNum == 0 ) {
		++mNowDivNum;
		return true;
	}

	return false;
}

void Animation::start() {
	if ( mCount < 0 ) {
		mCount = 1; //�J�E���g�J�n
	}
	mIsAnimating = true;
}

void Animation::reset() {
	mCount = 0;
	mNowDivNum = 0;
	mIsAnimating = false;
}

bool Animation::getmIsAnimating() {
	return mIsAnimating;
}

int Animation::getNowDivNum() {
	return mNowDivNum;
}