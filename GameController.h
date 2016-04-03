#ifndef INCLUDED_GAMECONTROLLER_H
#define INCLUDED_GAMECONTROLLER_H

//�V���O���g��
class GameController {
public:
	//�L�[��������Ă��邩
	enum KeyState {
		NotPressed = 0,
		Pressed = 1,
		PressedNow = 2,
	};
	static GameController* instance();
	static void create(); //�C���X�^���X�쐬
	static void destroy(); //�C���X�^���X�폜
	
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
	void graphFps(); //fps�\��
	void controlFps(); //�Œ�fps��

	int mCount; //�J�E���^
	int mFrameSpdAvg; //���ς�1�t���[������
	int mWaitTime;
	int mPrevTime;
	
	static GameController* mInstance;
};

#endif
