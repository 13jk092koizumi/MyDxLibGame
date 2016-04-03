#include "DxLib.h"
#include "Sequence/Game/BaseTown.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Sequence/Game/Shop.h"
#include "Sequence/Title.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {
	char* list[] = {
		"塔を上る",
		"ステータス",
		"ショップ",
		"スキル強化"
	};
	char* explainSelect[] = {
		"塔を上ってお金を稼ぎましょう。",
		"ステータスの詳細を表示します。",
		"装備や道具を売買できます。",
		"スキルをゴールドで強化できます。"
	};
	//色
	const unsigned int WHITE = GetColor( 255, 255, 255 );	//白
	//フレーム制御用
	int nowCounter = 0;
	int oldCounter = 0;
	int TimeSensor = 0;
	int FrameTime = 0;
}

namespace Sequence {
	namespace Game {

		BaseTown::BaseTown() :
			mImage(0),
			mCursorPosition(-1),
			mFrameCount(0),
			mFirstFlag(false) {
			//メンバ配列初期化
			memset( mOldKey, 0, sizeof mOldKey );
			memset( mNowKey, 0, sizeof mNowKey );
			mImage = new Image[ 2 ]{ "data/image/town.png" ,"data/image/chara/007.png"};
			mWindow = new Window[4];
			//背景画像読み込み
			mImage[ 0 ].setImgHandle();
			mImage[ 1 ].setImgHandle();
		}

		BaseTown::~BaseTown() {
			delete[] mImage;
			mImage = 0;
			delete[] mWindow;
			mWindow = 0;
		}

		Child* BaseTown::update(Parent* parent) {
			Child* next = this;
			//画面描画
			drawState();
			
			if ( CheckHitKey( KEY_INPUT_SPACE ) ) {
				switch ( mCursorPosition ) {
					case 0:
						next = new Dungeon;
						break;
					case 1:
						//TODO:ステータス表示
						break;
					case 2:
						next = new Shop;
						break;
					case 3:
						//TODO:スキル強化
						break;
					default:
						break; //何もしない
				}
			} else if ( CheckHitKey( KEY_INPUT_BACK ) ) {
				parent->moveTo( Parent::NEXT_TITLE );
			}
			return next;
		}

		void BaseTown::drawState() {
			//最初のループかどうか
			if ( checkFirstLoop() || mFrameCount<Global::WaitFrame ) {
				//ロード画面を表示
				Global::moveScreen( mFrameCount, "Now Loading" );
				++mFrameCount;
			} else {
				mImage[ 0 ].drawGraph( 0, 0 );
				//画面を構成
				DrawString( 10, 25, "ベースタウン", GetColor( 50, 50, 50 ) );
				mWindow[ 0 ].drawWindow( 10, 50, 200, 370, Window::WINDOW_LINE );

				//カーソル入力チェック
				changeCursor();

				//メニューリスト
				mWindow[ 0 ].drawListOnWindow( 4, mCursorPosition, list );

				//メニューの説明文
				MenuExplanation();

				//HPなど
				//TODO:キャラのステータスと連動させる
				mWindow[ 1 ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
				mWindow[ 1 ].drawHPBar( 415, 385, 100 );
				DrawFormatString( 385, 355, ::WHITE, "レベル　%d", 1 );
				DrawString( 385, 385, "HP", ::WHITE );
				DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );

				//キャラ画像
				mWindow[ 2 ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
				mImage[ 1 ].drawGraph( 333, 355, true );

				//所持ゴールド表示
				mWindow[ 3 ].drawWindow( 480, 5, 639, 30, Window::WINDOW_LINE );
				DrawFormatString( 480, 7, WHITE, "所持金 %d", 1000 );
				DrawString( 619, 7, "G", WHITE );
			}
		}

		void BaseTown::MenuExplanation() {
			int posY = mWindow[ 0 ].getHeight() / 4; //ウィンドウサイズを4(list[]の要素数)で割る
			for ( int i = 0; i < 4; ++i ) {
				if ( i == mCursorPosition ) {
					SetDrawBlendMode( DX_BLENDMODE_ALPHA, 190 ); //アルファブレンドモードにセット
					DrawBox( 210, ( posY * i ) + 60, 531, ( posY*i ) + 80, GetColor( 50, 50, 50 ), true );
					SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
					DrawString( 210, (posY * i)+60, ::explainSelect[ i ], ::WHITE );
				}
			}
		}

		void BaseTown::changeCursor() {
			//カーソル移動
			//まず上キーが押されたかどうか
			mNowKey[ 0 ] = Global::isKeyOn( KEY_INPUT_UP );
			if ( !mOldKey[ 0 ] && mNowKey[ 0 ] ) { //前押されてなくて今押されていたら
				--mCursorPosition; //カーソルを上に
				mCursorPosition = ( mCursorPosition < 0 ) ? 0 : mCursorPosition;
			}
			//次に下キーが押されたかどうか
			mNowKey[ 1 ] = Global::isKeyOn( KEY_INPUT_DOWN );
			if ( !mOldKey[ 1 ] && mNowKey[ 1 ] ) {
				++mCursorPosition; //カーソルを下に
				mCursorPosition = ( mCursorPosition > 3 ) ? 3 : mCursorPosition;

			}
			mOldKey[ 0 ] = mNowKey[ 0 ]; //現在の状態を保存
			mOldKey[ 1 ] = mNowKey[ 1 ];
			
		}

		bool BaseTown::checkFirstLoop() {
			//既にtrueだったら最初じゃない
			if ( mFirstFlag ) {
				return false;
			}
			mFirstFlag = true;
			return true;
		}

	} //namespace Game
} //namespace Sequence
