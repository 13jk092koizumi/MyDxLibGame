#include "DxLib.h"
#include <vector>
using namespace std;

#include "Sequence/Game/Battle.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Battle/BattleMain.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

using namespace BATTLE;

namespace {
	unsigned int WHITE = GetColor( 255, 255, 255 );
	char* menuList[] = {
		"こうげき",
		"スキル",
		"にげる",
	};
	char* skillMenu[] = {
		"スキル1",
		"スキル2",
		"スキル3",
		"スキル4",
		"スキル5",
	};

} //namespace

namespace Sequence {
	namespace Game {
			Battle::Battle() :
				mFramecount( 0 ),
				mImage( 0 ),
				mWindow( 0 ),
				mBattleMain(0),
				ｍIsSkillMenu( false ),
				mCommandPhase(true), //最初はコマンド選択フェーズ
				mActPhase(false),
				mDecideCommand(false)
			{
				//メンバ配列の初期化
				memset( mCursorPosition, -1, sizeof mCursorPosition );
				memset( mNowKey, 0, sizeof mNowKey );
				memset( mOldKey, 0, sizeof mOldKey );

				mImage = new Image[ 3 ]{ "data/image/dng01.jpg" ,"data/image/chara/007.png","data/image/battler00/animal05.png" };
				mImage[ 0 ].setImgHandle();
				mImage[ 1 ].setImgHandle();
				mImage[ 2 ].setImgHandle();
				mWindow = new Window[ 5 ];

				mBattleMain = new BattleMain;
			}

			Battle::~Battle() {
				delete[] mImage;
				mImage = 0;

				delete[] mWindow;
				mWindow = 0;
			}

			Child* Battle::update( Parent* parent ) {
				Child* next = this;
				//画面描画
				mImage[ 0 ].drawGraph( 0, 0 );
				drawState();
				//コマンド選択フェーズか
				if ( mCommandPhase ) {
					mBattleMain->resetTurn(); //ターンの初期化
					mDecideCommand = false; //コマンド初期化
					selectCommand();
					DrawString( 100, 3, "コマンドを選択してください。", ::WHITE );

					if ( mDecideCommand ) {
						mCommandPhase = false; //選択フェーズをオフに
						mActPhase = true; //実行フェーズをオンに
					}
					mFramecount = 0;
				}
				if ( mActPhase  && mFramecount < 60) {
					//TODO:バトルのアニメーション処理・標的選択
					if ( mBattleMain->doTurn( mFramecount, commandKind() ) ) {
						next = new Dungeon; //doTurnがtrueならバトルが終了した
					}
					++mFramecount;
					if ( mFramecount == 60 ) {
						mActPhase = false;
						mCommandPhase = true;
					}
				}
				
				if ( CheckHitKey( KEY_INPUT_D ) ) {
					clsDx(); //printfDx clear
					next = new Dungeon;
				} else if ( CheckHitKey( KEY_INPUT_G ) ) {
					clsDx();
					parent->moveTo( Parent::NEXT_GAME_OVER );
				}


				return next;
			}

			void Battle::drawState() {
				//メッセージログ
				mWindow[ WINNAME_B_MESSAGE ].drawWindow( 2, 2, 639, 30, Window::WINDOW_LINE );
				DrawFormatString( 20, 5, ::WHITE, "敵が襲ってきた！！" );
				/*プレイヤー*/
				//ステータス表示
				mWindow[ WINNAME_B_STATUS ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
				mWindow[ WINNAME_B_STATUS ].drawHPBar( 415, 385, 100 );
				//レベル
				DrawFormatString( 385, 355, ::WHITE, "レベル　%d", 1 );
				//HP
				DrawString( 385, 385, "HP", ::WHITE );
				DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );
				//EXP
				DrawString( 385, 415, "EXP", ::WHITE );
				DrawFormatString( 440, 416, ::WHITE, "%d / %d", 0, 1200 );
				//GOLD
				DrawString( 385, 450, "所持金", ::WHITE );
				DrawFormatString( 480, 450, ::WHITE, "%d G", 1000 );
				//キャラ画像
				mWindow[ WINNAME_B_CHARA ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
				mImage[ 1 ].drawGraph( 333, 355, false );
				
				/*敵*/
				//敵画像TODO:ランダムに敵生成できるように
				int counter = 0;
				counter = GetRand( 100 );
				//DrawFormatString( 400, 200, ::WHITE, "count:%d", counter );
				mImage[ 2 ].drawRotaGraph( 300, 220, 1.5, 0.0, true );
				if ( counter % 100 == 0 ) {
					mImage[ 2 ].drawRotaGraph( 300, 220, 1.6, 0.0, true );
				}
				//敵の残りHPを表示
				vector<int>& v = mBattleMain->getEnemyStatus();
				int i = 0;
				for ( auto itr = v.begin(); itr != v.end(); ++itr ) {
					DrawFormatString( 100, 30 + 20 * i, ::WHITE, "enemy%d:%d", i, v.at(i) );
					++i;
				}
				
			}

			void Battle::selectCommand() {
				//コマンドメニュー描画
				mWindow[ WINNAME_B_MENU1 ].drawWindow( 3, 350, 120, 478, Window::WINDOW_LINE );
				mWindow[ WINNAME_B_MENU1 ].drawListOnWindow( 3, mCursorPosition[ WINNAME_B_MENU1 ], ::menuList );
				//SPACEキーが押されたかどうか
				mNowKey[ 2 ] = Global::isKeyOn( KEY_INPUT_SPACE );
				//カーソル移動
				if ( !ｍIsSkillMenu ) { //スキルメニューが開かれていない
					changeCursor( WINNAME_B_MENU1, 3 );
					//メニュー分岐
					if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[ WINNAME_B_MENU1 ] == 1 ) { //スキルを選択した
						++mKeyCount;
						ｍIsSkillMenu = true;
					}
				}
				//スキルメニュー判定
				if ( mKeyCount > 0 && ｍIsSkillMenu ) { //spaceキ-のカウントが0以上でスキルメニューが有効である
					changeCursor( WINNAME_B_MENU2, 5/*TODO:スキル一覧の数*/ );
					mWindow[ WINNAME_B_MENU2 ].drawWindow( 110, 270, 320, 478, Window::WINDOW_LINE );
					mWindow[ WINNAME_B_MENU2 ].drawListOnWindow( 5, mCursorPosition[ WINNAME_B_MENU2 ], ::skillMenu );
				}

				if ( Global::isKeyOn( KEY_INPUT_X ) ) { //XかUP,DOWNキーを押したら
					mKeyCount = 0;
					ｍIsSkillMenu = false;
					mCursorPosition[WINNAME_B_MENU2] = -1;
				}

				//決定ボタンが押されていて、かつカーソル位置が正の数のときコマンドを確定する
				if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[WINNAME_B_MENU1] != 1  && mCursorPosition[ WINNAME_B_MENU1 ] >= 0 ) {
					//スキルを選択していない
					mDecideCommand = true; //コマンド確定
				} else if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[ WINNAME_B_MENU2 ] >= 0 ) {
					//スキルメニューの何かしらにカーソルがある
					mDecideCommand = true;
				}

				//現在の状態を保存
				for ( int i = 0; i < sizeof mOldKey; i++ ) {
					mOldKey[ i ] = mNowKey[ i ];
				}

			}

			void Battle::changeCursor( int cursorIndex, int listSize ) {
				//まず上キーが押されたかどうか
				mNowKey[ 0 ] = Global::isKeyOn( KEY_INPUT_UP );
				if ( !mOldKey[ 0 ] && mNowKey[ 0 ] ) { //前押されてなくて今押されていたら
					mCursorPosition[ cursorIndex ] -= 1; //カーソルを上に
					mCursorPosition[ cursorIndex ] = ( mCursorPosition[ cursorIndex ] < 0 ) ? 0 : mCursorPosition[ cursorIndex ];
				}
				//次に下キーが押されたかどうか
				mNowKey[ 1 ] = Global::isKeyOn( KEY_INPUT_DOWN );
				if ( !mOldKey[ 1 ] && mNowKey[ 1 ] ) {
					mCursorPosition[ cursorIndex ] += 1; //カーソルを下に
					mCursorPosition[ cursorIndex ] = ( mCursorPosition[ cursorIndex ] > listSize - 1 ) ? listSize - 1 : mCursorPosition[ cursorIndex ];
				}
			}

			int Battle::commandKind() {
				switch ( mCursorPosition[ 0 ] ) {
					case 0:
						//こうげき
						return 1;
					case 1:
						//スキル
						switch ( mCursorPosition[ 1 ] ) {
							case 0:
								return 101;
							case 1:
								return 102;
							case 2:
								return 103;
							case 3:
								return 104;
							case 4:
								return 105;
						}
						break;
					case 2:
						//にげる
						return 200;
				}
			}

	} //namespace Game
} //namespace Sequence
