#ifndef INCLUDED_GLOBALVALUES_H
#define INCLUDED_GLOBALVALUES_H

//#define SIZEOF(array) (sizeof(array) / sizeof*(array))
#define STR(var) #var //引数に入る文字を文字列に変換するマクロ

namespace Global {
	const int WindowWidth = 640;							//ウィンドウ横
	const int WindowHeight = 480;						//ウィンドウ縦
	const int FontSize = 20;									//フォントサイズ
	const int WaitFrame = 30;								//何フレーム待つか

	//シーケンス遷移時に使う。
	void moveScreen(int flamecount, char* message); //シーケンス移動中
	//引数のキーが入力されているかを返す
	bool isKeyOn( int );
	//boolalphaもどき
	char* boolalpha(int);

} //namespace Global

#endif
