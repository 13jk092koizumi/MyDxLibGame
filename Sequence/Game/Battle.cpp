#include "DxLib.h"
#include <vector>
using namespace std;

#include "Sequence/Game/Battle.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Battle/BattleMain.h"
#include "Battle/Enemy.h"
#include "Image.h"
#include "Window.h"
#include "Animation.h"
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
	
	/*アニメーション判別用*/
	enum anime {
		ANIME_PATTACK, //プレイヤー攻撃アニメーション
		ANIME_EATTACK, //敵攻撃アニメーション
		ANIME_IMG_ENEMY, //敵画像のアニメーション
	};

} //namespace

namespace Sequence {
	namespace Game {
			Battle::Battle() :
				mFramecount( 0 ),
				mImage( 0 ),
				mWindow( 0 ),
				mAnimation(0),
				mBattleMain(0),
				ｍIsSkillMenu( false ),
				mBattleState(Battle_None),
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
				mBattleState = Battle_CommandSelect;
				mAnimation = new Animation[ 3 ]{ Animation( 30, 3 ), Animation(30,3), Animation(60,6) };
			}

			Battle::~Battle() {
				delete[] mImage;
				mImage = 0;

				delete[] mWindow;
				mWindow = 0;

				delete[] mAnimation;
				mAnimation = 0;
			}

			Child* Battle::update( Parent* parent ) {
				Child* next = this;
				//画面描画
								
				//アニメーション用変数
				bool isValidAnime = false;
				int nowDivNum = 0;
				int color = 0;

				//バトルの状態遷移
				switch ( mBattleState ) {
					case Battle_CommandSelect:
						
						drawState();
						DrawFormatString( 20, 5, ::WHITE, "敵が襲ってきた！！" );

						mBattleMain->resetTurn(); //ターンの初期化
						mDecideCommand = false; //コマンド初期化
						selectCommand();
						if ( mDecideCommand ) { //コマンドを決定した
							mBattleState = Battle_PlayerAct;
						}
						break;
					
					case Battle_PlayerAct:
						if ( mBattleMain->exeTurn( mFramecount, commandKind() /*selectTarget()*/ ) ) { //プレイヤーのターン終了
							mBattleState = Battle_EnemyAct;
						}
						
						isValidAnime = mAnimation[ANIME_PATTACK].animate(); //コマ送りのタイミングか
						if ( isValidAnime && mAnimation[ANIME_PATTACK].getmIsAnimating() ) { //アニメーションが有効である
							nowDivNum = mAnimation[ANIME_PATTACK].getNowDivNum();
							color = 88 * nowDivNum;
							color = ( color > 255 ) ? 255 : color;
							/*TODO:攻撃エフェクトに置き換える*/
							DrawBox( 0, 0,Global::WindowWidth,Global::WindowHeight, GetColor( color, color, color ),true );
							if ( nowDivNum > 1 ) {
								//デバッグ
								int damage = mBattleMain->getDamege( 2 );
								if ( damage < 0 ) {
									damage = 11111111;
								}
								DrawFormatString( 20, 5, GetColor( 0, 0, 0 ), "敵に%dのダメージ！！", damage ); //ダメージ量表示
							}
						} else if ( mAnimation[ANIME_PATTACK].getmIsAnimating() == false ) {
							mAnimation[ANIME_PATTACK].end(); //カウンタを初期化
							mAnimation[ANIME_PATTACK].start();
							mBattleState = Battle_EnemyAct;
						}
//						++mFramecount;
//						if ( mFramecount > 60 ) {
//							mBattleState = Battle_EnemyAct;
//							mFramecount = 0;
//						}
						break;
					case Battle_EnemyAct:
						if ( mBattleMain->exeTurn( mFramecount, commandKind() ) ) { //敵ターン終了
							mBattleState = Battle_CommandSelect;
							if ( mBattleMain->isBattleEnd() ) { //バトルが終了してたら
								mBattleState = Battle_Result; //リザルト画面表示
								if ( mBattleMain->isGameOver() ) { //ゲームオーバーフラグを満たしてたら
									mBattleState = Battle_Gameover;//ゲームオーバーへ
								}
							}
						}

						++mFramecount;
						if ( mFramecount > 60 ) {
							mBattleState = Battle_CommandSelect;
							mFramecount = 0;
						}
						break;
					case Battle_Result:
						/*TODO:リザルト画面表示(終わったフラグが立ったらBattle_Endへ)*/
						++mFramecount;
						if ( mFramecount > 60 ) {
							mBattleState = Battle_End;
							mFramecount = 0;
						} else {
							mBattleMain->result();
						}
						break;
					case Battle_End:
						/*TODO:終了アニメーションの表示*/
						mBattleState = Battle_None; //変数初期化
						next = new Dungeon; //ダンジョンに戻る
						break;
					case Battle_Gameover:
						parent->moveTo( Parent::NEXT_GAME_OVER ); //ゲームオーバーへ
						mBattleState = Battle_None; //変数初期化
						break;
					case Battle_None: //ありえない！？
						DrawString( 0, 200, "NowBattleState is NONE!!!", GetColor( 255, 255, 0 ) );
						WaitKey();
						break;
				}

				/*
				//コマンド選択フェーズか
				if ( mCommandPhase ) {
					mBattleMain->resetTurn(); //ターンの初期化
					mDecideCommand = false; //コマンド初期化
					selectCommand();

					if ( mDecideCommand ) {
						mCommandPhase = false; //選択フェーズをオフに
						mActPhase = true; //実行フェーズをオンに
					}
					mFramecount = 0;
				}
				if ( mActPhase  && mFramecount < 60) {
					//TODO:バトルのアニメーション処理・標的選択
					if ( mBattleMain->exeTurn( mFramecount, commandKind() ) ) {
						next = new Dungeon; //exeTurnがtrueならバトルが終了した
					}
					++mFramecount;
					if ( mFramecount == 60 ) {
						mActPhase = false;
						mCommandPhase = true;
					}
				}
				*/
				
				//デバッグ
				DrawFormatString( 0, 200, GetColor(0,0,0), "mBattleState:%d", mBattleState );

				if ( Global::isKeyOn( KEY_INPUT_D ) ) {
					next = new Dungeon;
				} else if ( Global::isKeyOn ( KEY_INPUT_G ) ) {
					parent->moveTo( Parent::NEXT_GAME_OVER );
				}


				return next;
			}

			void Battle::drawState() {
				//背景
				mImage[ 0 ].drawGraph( 0, 0 );

				//メッセージログ
				mWindow[ WINNAME_B_MESSAGE ].drawWindow( 2, 2, 639, 30, Window::WINDOW_LINE );
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
				drawEnemy();
				
			}

			void Battle::drawEnemy() {
				int enemyNum = mBattleMain->getEnemyNum(); //敵の数取得
				float scale = 0;
				int rand = GetRand( 100 );
				if ( rand == 0 ) {
					scale = 0.1f;
				}
				/*敵画像の表示*/
				mAnimation[ ANIME_IMG_ENEMY ].animate();
				int nowDivNum = mAnimation[ANIME_IMG_ENEMY].getNowDivNum(); //何コマ目か取得
				int movePx = 0; //敵画像の上下の移動量(上下に揺らす)
				switch ( nowDivNum ) {
					case 1:
						movePx = 1;	break;
					case 2:
						movePx = 2;	break;
					case 3:
						movePx = 3;	break;
					case 4:
						movePx = 2;	break;
					case 5:
						movePx = 1;	break;
					case 6:
						movePx = 0;
						mAnimation[ ANIME_IMG_ENEMY ].end();
						mAnimation[ ANIME_IMG_ENEMY ].start(); //アニメーションの再開
						break;
				}
				switch ( enemyNum ) {
					case 1:
						mImage[ 2 ].drawRotaGraph( Global::WindowWidth / 2, (Global::WindowHeight / 2) - movePx , 1.5f+scale, 0.0f ,true);
						break;
					case 2:
						for ( int i = 1; i <= enemyNum; ++i ) {
							mImage[ 2 ].drawRotaGraph( 640 - ( 440 * i / enemyNum ), 180 - movePx, 1.4f+scale, 0.0f, true );
						}
						break;
					case 3:
					case 4:
					case 5:
						for ( int i = 1; i <= enemyNum; ++i ) {
							mImage[ 2 ].drawRotaGraph( 640 - ( 540 * i / enemyNum ), 180 - movePx, 1.2f+scale, 0.0f, true );
 						}
						break;
				}
				/*残りHPの表示*/
				SetFontSize( 12 ); //文字サイズ変更
				vector<Status> eStatus = mBattleMain->getEnemyStatus(); //vectorで敵のステータス構造体の配列を取得
				Status* data = eStatus.data(); //敵のStatus構造体のポインタを取得
				int hpColor = 0; //HPの色
				int i = 0;
				for ( auto itr = eStatus.begin(); itr != eStatus.end(); ++itr ) {
					if( data[ i ].hp < data[ i ].hpMax * 0.3f ) 	{ //HP30%以下のとき
						hpColor = GetColor( 250, 0, 0 ); //黒っぽい赤
					} 
					else if ( data[i].hp < data[i].hpMax * 0.5f ) { //HP50%以下のとき
						hpColor = GetColor( 255, 165, 0 ); //オレンジ
					}
					else {
						hpColor = GetColor( 255, 255, 255 ); //白
					}
					DrawFormatString( 640 - ( 540 * (i+1) / enemyNum ), 175, hpColor, "%d", eStatus[ i ] );
					++i;
				}

				SetFontSize( Global::FontSize );

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
						//break;
					case 2:
						//にげる
						return 200;
				}
				return -1;
			}

	} //namespace Game
} //namespace Sequence
