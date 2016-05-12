#ifndef INCLUDED_WINDOW_H
#define INCLUDED_WINDOW_H

//窓1つにつき1クラス用意
class Window{
public:
	enum WindowType {
		WINDOW_NORMAL,		//枠なし窓
		WINDOW_LINE,			//枠あり窓
		WINDOW_NO_TRANS, //透けない窓
		WINDOW_NONE,			//どれでもない
	};
	
	Window( ); //引数は窓の大きさx*y
	~Window() {}
	
	void drawWindow( int x1, int y1, int x2, int y2, WindowType ); //ウィンドウ描画.引数はウィンドウの開始位置、終了位置、ウィンドウタイプ
	
	void drawListOnWindow( int arraysize, int pos, char** list); //引数:配列の要素数、カーソルポジション、リスト配列
	
	void drawHPBar( int x, int y, double percent ); //HPバーを表示(x,y,HPの残り%)
	
	void reduceHP( double nowHP, double afterHP ); //HPバーを減らす(減る前HP%,減った後HP%);
	
	int getHeight() const; //ウィンドウ縦
	
	int getWidth() const; //ウィンドウ横

private:
	void drawWindowLine() const; //枠描画
	void resetMember(); //メンバ初期化

	int mX;	//表示位置の座標x
	int mY; //表示位置の座標y
	int mEndX; //windowの長さX
	int mEndY; //windowの長さY
	char* mMessage; //表示する文字列の配列
	WindowType mWinType;

};

#endif
