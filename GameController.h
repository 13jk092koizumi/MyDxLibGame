#ifndef INCLUDED_GAMECONTROLLER_H
#define INCLUDED_GAMECONTROLLER_H

//シングルトン
class GameController {
public:
	//キーが押されているか
	enum KeyState {
		NotPressed = 0,
		Pressed = 1,
		PressedNow = 2,
	};
	static GameController* instance();
	static void create(); //インスタンス作成
	static void destroy(); //インスタンス削除
	
	char getKey( int input ) const;
	int getAllKeyPressed() const;

	void increaseCount();
	int GetmCount() const;

	void adjustKeyState();
	void control();

private:
	GameController();
	~GameController() {}
	GameController(const GameController&){}
	GameController& operator=(const GameController&){}

	void calcFps();
	void graphFps(); //fps表示
	void controlFps(); //固定fps化

	int mCount; //カウンタ
	int mFrameSpdAvg; //平均の1フレーム時間
	int mWaitTime;
	int mPrevTime;
	
	static GameController* mInstance;
};

#endif
