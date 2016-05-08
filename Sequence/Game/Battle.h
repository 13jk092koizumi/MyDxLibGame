#ifndef INCLUDED_SEQUENCE_GAME_BATTLE_H
#define INCLUDED_SEQUENCE_GAME_BATTLE_H

#include "Child.h"
class Image;
class Window;
class Animation;

namespace BATTLE {
	class BattleMain;
}

namespace Sequence {
	namespace Game {

		class Parent;

		//ダンジョン
		class Battle : public Child {
		public:
			Battle();
			~Battle();
			Child* update( Parent* );
		private:
			enum WinBattleName {
				WINNAME_B_MENU1, //こうげき・スキル・逃げる
				WINNAME_B_MENU2, //スキル選択
				WINNAME_B_STATUS,
				WINNAME_B_MESSAGE,
				WINNAME_B_CHARA,
			};
			enum BattleState {
				Battle_Start, //バトル開始
				Battle_CommandSelect, //コマンド選択
				Battle_PlayerAct, //プレイヤーのコマンド実行
				Battle_EnemyAct, //敵の攻撃アクション
				Battle_Result, //リザルト画面表示
				Battle_End, //バトル終了
				Battle_Gameover, //ゲームオーバー
				Battle_None,
			};
			void drawState(); //画面を構成
			void selectCommand(); //コマンド選択
			void changeCursor( int cursorIndex, int listSize ); //カーソル位置メンバの変更
			int commandKind(); //何のコマンドか(こうげき・スキル・逃げる)

			int mFramecount; //フレーム数(update()の呼ばれた回数)
			int mCursorPosition[ 2 ]; //menu1とmenu2のカーソル位置
			bool mNowKey[ 3 ]; //現在のキー状態
			bool mOldKey[ 3 ]; //前のキー状態
			int mKeyCount; //キーが押されていたら増加
			bool ｍIsSkillMenu; //スキルメニューが開かれているか

			Image* mImage;
			Window* mWindow;
			Animation* mAnimation;

			BATTLE::BattleMain* mBattleMain;
			BattleState mBattleState; //バトルの状態
			bool mCommandPhase; //選択フェーズかどうか
			bool mActPhase; //実行フェーズかどうか
			bool mDecideCommand; //コマンドが決定したかどうか
		};


	} //namespace Game
} //namespace Sequence

#endif
