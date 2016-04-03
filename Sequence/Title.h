#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "Sequence/Child.h"

class Image;
class Window;

namespace Sequence {
	class Parent;
	class Title : public Child {
	public:
		Title();
		~Title();
		Child* update( Parent* );
	private:
		enum StartMenu {
			SMENU_HAJIMEKARA, //はじめから
			SMENU_TUDUKIKARA, //続きから
		};
		void drawState(); //各種描画
		void startMenu(); //はじめからかつづきからを選ぶ
		void changeCursor(); //カーソル入力

		Image* mImage; //タイトル画面画像
		Window* mWindow;
		int mCursorPosition; //カーソル位置
		bool mMenuFlag; //メニューを表示しているかのフラグ
		bool mPushFlag; //キーが押されたとかのフラグ
		bool mGameStartFlag; //ゲーム本編へ遷移するかのフラグ
		bool mNowKey[2];
		bool mOldKey[2];
	};

} //namespace Sequence

#endif
