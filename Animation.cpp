#include "Animation.h"

Animation::Animation( int flameNum, int divideNum ) : mCount( 0 ), mIsAnimating( false ) ,mNowDivNum(0)
{
	mEndCount = flameNum; //何フレームアニメーションするか
	mValidTiming = flameNum/divideNum; //何コマごとに切り替えるか
	mValidTiming = ( mValidTiming < 1 ) ? 1 : mValidTiming;
	start(); //アニメーションスタート
}

Animation::~Animation(){
	//何もしない
}

bool Animation::animate() {
	//mEndCountになるまでカウンタ増加
	++mCount;
	
	//アニメーションの終了判定
	if ( mCount > mEndCount ) {
		mIsAnimating = false; //アニメーションの終了
		return false;
	}
	
	int nowDivNum = mCount % mValidTiming;
	//mValidTimingで割り切れるときtrue返却
	if ( nowDivNum == 0 ) {
		++mNowDivNum;
		return true;
	}

	return false;
}

void Animation::start() {
	if ( mCount < 0 ) {
		mCount = 1; //カウント開始
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