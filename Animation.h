#ifndef INCLUDED_ANIMATION_H
#define INCLUDED_ANIMATION_H

//指定カウンタ数の間アニメーションの有効判定をするクラス
/*使い方
・コンストラクタにアニメーションさせるフレーム数とコマ(分割)数
・animate()でアニメーションが有効かの判定とコマ送りのタイミングの時true返却
・start()はカウンタを1にしてアニメーションを有効にする
・reset()は各変数を初期状態に戻す
*/

class Animation {
public:
	Animation( int flameNum, int divideNum ); //フレーム数とコマ数
	~Animation();
	bool animate(); //アニメのコマ数に応じてtrueを返す
	bool getmIsAnimating();
	int getNowDivNum();
	void start(); //判定開始
	void reset(); //変数のリセット
private:
	unsigned int mCount; //カウンタ
	unsigned int mEndCount; //終了するタイミング
	int mNowDivNum; //今何分割目か(０～divideNum)
	int mValidTiming; //アニメーション時間÷分割数(何コマか)
	bool mIsAnimating; //アニメ―ション中か否か
};

#endif