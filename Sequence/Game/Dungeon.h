#ifndef INCLUDED_SEQUENCE_GAME_DUNGEON_H
#define INCLUDED_SEQUENCE_GAME_DUNGEON_H

#include "Child.h"
class Image;
class Window;

namespace Sequence {
	namespace Game {
		class Parent;

		//ダンジョン
		class Dungeon : public Child{
		public:
			Dungeon();
			~Dungeon();
			Child* update(Parent*);
		private:
			void drawState(); //画面を構成
			bool checkFirstLoop(); //初めてのループかどうか調べる
			void changeCursor(); //カーソルをキーによって変動

			enum WinName_Dungeon{
				WINNAME_FLOOR, //塔の階層
				WINNAME_PROGRESS, //探索度
				WINNAME_SELECTMENU, //セレクトメニュー
				WINNAME_CHARA, //キャラ
				WINNAME_STATUS, //HPや経験値など
				WINNAME_BOSSDOOR, //ボス部屋のドア
			};
			Image* mImage;
			Window* mWindow;
			int mCursorPosition; //カーソル位置
			int mFrameCount; //フレームカウンタ
			bool mFirstFlag; //初めてのループかどうか
			//キーの押下状態配列。添え字0はUP,1はDOWNキー
			bool mNowKey[2]; //現在フレームのキー
			bool mOldKey[2]; //前のフレームのキー

		};

	} //namespace Game
} //namespace Sequence

#endif
