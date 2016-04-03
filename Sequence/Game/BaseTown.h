#ifndef INCLUDED_SEQUENCE_GAME_BASETOWN_H
#define INCLUDED_SEQUENCE_GAME_BASETOWN_H

#include "Sequence/Game/Child.h"
class Image;
class Window;

namespace Sequence {
	namespace Game {
		class Parent;
		
		//拠点の街。ここからゲームがスタートする。
		class BaseTown : public Child {
		public:
			BaseTown();
			~BaseTown();
			Child* update( Parent* );
			
		private:
			void drawState(); //画面を構成
			void changeCursor();
			void MenuExplanation(); //メニューの説明文
			bool checkFirstLoop(); //最初のループかどうかを調べる
			int mCursorPosition; //カーソル位置
			bool mFirstFlag; //一番最初のループかどうか
			int mFrameCount; //1フレーム毎に1増える
			bool mNowKey[ 2 ]; //現在フレームのキー
			bool mOldKey[ 2 ]; //1フレーム前のキー
			Image* mImage;	//街の画像
			Window* mWindow; //ウィンドウ
		};

	} //namespace Game
} //namespace Sequence

#endif