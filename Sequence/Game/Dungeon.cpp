#include "DxLib.h"
#include "Sequence/Game/Dungeon.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/BaseTown.h"
#include "Sequence/Game/Battle.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {

	char* list[] = {
		"先へ進む",
		"街へ戻る",
		"ボスに挑戦する!"
	};
	const unsigned int WHITE = GetColor( 255, 255, 255 ); //白
	const int menuHeight= Global::WindowHeight / 3; //セレクトメニューのｙ
	const int menuWidth = Global::WindowWidth / 3; //セレクトメニューのｘ
	int TimeSensor = 0;
} //namespace

namespace Sequence {
	namespace Game {

		Dungeon::Dungeon() :
			mImage( 0 ),
			mWindow(0),
			mFrameCount(0),
			mFirstFlag(false),
			mCursorPosition(-1) {
			//メンバ配列の初期化
			memset( mNowKey, 0, sizeof mNowKey );
			memset( mOldKey, 0, sizeof mOldKey );
			//画像はここで読み込んでおく
			mImage = new Image[ 2 ]{ "data/image/dng01.jpg" ,"data/image/chara/007.png"}; //ダンジョン画像
			mImage[ 0 ].setImgHandle(); //背景画像
			mImage[ 1 ].setImgHandle(); //キャラ画像
			mWindow = new Window[6];
		}

		Dungeon::~Dungeon() {
			delete[] mImage;
			mImage = 0;
			delete[] mWindow;
			mWindow = 0;
		}

		Child* Dungeon::update( Parent* ) {
			Child* next = this;

			if ( checkFirstLoop() || mFrameCount<Global::WaitFrame) {
				Global::moveScreen(mFrameCount,"移動中");
				++mFrameCount;
			} else {
				//画像描画
				mImage[ 0 ].drawGraph( 0, 0 );
				//TODO:バトル(モンスターとプレイヤー画像表示)
				//画面を構成
				drawState();
				changeCursor();
				if ( CheckHitKey( KEY_INPUT_SPACE ) ) {
					switch( mCursorPosition ) {
						case 0: //奥へ進む
							next = new Battle;
							break;
						case 1: //街へ戻る
							next = new BaseTown;
							break;
						//case 2:
						//	next = new BossBattle;
						// break;
						default: break;
					}
				}
			}

			if ( CheckHitKey( KEY_INPUT_B ) ) {
				clsDx();
				next = new Battle;
			} else if ( CheckHitKey( KEY_INPUT_BACK ) ) {
				clsDx();
				next = new BaseTown;
			}
			
			return next;
		}

		void Dungeon::drawState() {
			//フロア表示 TODO:フロアを可変に
			mWindow[ WINNAME_FLOOR ].drawWindow( 10, 4, 100, 30, Window::WINDOW_LINE );
			DrawFormatString( 13, 7, WHITE, "第%d層", 1 );
			//探索度表示 TODO:探索度システム実装
			mWindow[ WINNAME_PROGRESS ].drawWindow( 500, 4, 679, 30, Window::WINDOW_LINE );
			DrawString( 501, 7, "探索度", WHITE );
			//メニュー表示。先に進むとバトル開始、街に戻るとBaseTownへ。
			mWindow[ WINNAME_SELECTMENU ].drawWindow( menuWidth, menuHeight, menuWidth * 2, menuHeight * 2, Window::WINDOW_LINE );
			mWindow[ WINNAME_SELECTMENU ].drawListOnWindow( 3, mCursorPosition, list );
			//ステータス表示
			mWindow[ WINNAME_STATUS ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
			mWindow[ WINNAME_STATUS ].drawHPBar( 415, 385, 100 );
				//レベル
			DrawFormatString( 385, 355, ::WHITE, "レベル　%d", 1 );
				//HP
			DrawString( 385, 385, "HP", ::WHITE );
			DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );
				//EXP
			DrawString( 385, 415, "EXP", ::WHITE );
			DrawFormatString( 440, 416, ::WHITE, "%d / %d", 0, 1200 );
			//キャラ画像
			mWindow[ WINNAME_CHARA ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
			mImage[ 1 ].drawGraph( 333, 355, true );
		}

		bool Dungeon::checkFirstLoop() {
			//既にtrueだったら最初じゃない
			if ( mFirstFlag ) {
				return false;
			}
			mFirstFlag = true;
			return true;
		}

		void Dungeon::changeCursor() {
			//カーソル移動
			//まず上キーが押されたかどうか
			mNowKey[0] = Global::isKeyOn( KEY_INPUT_UP );
			if ( !mOldKey[0] && mNowKey[0] ) { //前押されてなくて今押されていたら
				--mCursorPosition; //カーソルを上に
				mCursorPosition = ( mCursorPosition < 0 ) ? 0 : mCursorPosition;
			}
			//次に下キーが押されたかどうか
			mNowKey[1] = Global::isKeyOn( KEY_INPUT_DOWN );
			if ( !mOldKey[1] && mNowKey[1] ) {
				++mCursorPosition; //カーソルを下に
				mCursorPosition = ( mCursorPosition > 2 ) ? 2 : mCursorPosition;
				
			}
			mOldKey[ 0 ] = mNowKey[ 0 ]; //現在の状態を保存
			mOldKey[ 1 ] = mNowKey[ 1 ];
			
		}

	} //namespace Game
} //namespace Sequence