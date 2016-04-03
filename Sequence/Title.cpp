#include "DxLib.h"

#include "Sequence/Title.h"
#include "Sequence/Parent.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/GameOver.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {
	char* list[] = {
		"はじめから",
		"つづきから",
	};
	//カウンタ用変数
	int nowCount = 0;
	int oldCount = 0;
	int TimeSensor = 0; //指定カウンタ数だけ呼び出さないとき使う
}

namespace Sequence {

	Title::Title() :
		mImage( 0 ),
		mWindow(0),
		mCursorPosition(-1),
		mPushFlag(false),
		mGameStartFlag(false) {
		//メンバ配列初期化
		memset( mNowKey, 0, sizeof mNowKey );
		memset( mOldKey, 0, sizeof mOldKey );
		mImage = new Image( "data/image/title.png" );
		mWindow = new Window;
		Sleep( 200 );
	}

	Title::~Title() {
		if ( mImage != 0 ) {
			delete mImage;
			mImage = 0;
		}
		if ( mWindow != 0 ) {
			delete mWindow;
			mWindow = 0;
		}
	}

	Child* Title::update( Parent* ) {
		Child* next = this; //基底クラスChildの基底クラスBaseへポインタを渡す。
		//何かキーが押されたらBaseTownへ遷移
		drawState();
		//メニュー表示していないとき
		if ( !mMenuFlag ) {
			DrawString( 200, 200, "push any key.", GetColor( 255, 255, 255 ) );
		}
		//何かキーが押されたとき
		if ( CheckHitKeyAll( )) {
			mPushFlag = true;
			if ( CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) { //ESCAPEキーの時は処理しないようにする
				drawState();
				if ( mGameStartFlag ) { //ゲームスタートの条件を満たしたとき
					next = new Game::Parent();
				}
			}
		}

		return next;
	}

	void Title::drawState() {
		
		//背景描画
		mImage->setImgHandle();
		mImage->drawGraph( 0, 0 );
		
		//何かキーが押されたらメニュー表示
		if ( mPushFlag ) { 
			startMenu();
			mMenuFlag = true;
			if ( CheckHitKey( KEY_INPUT_X ) ) { //xでキャンセルしたら
				mPushFlag = false;
				mMenuFlag = false;
			}
		}

		changeCursor();

		if ( CheckHitKey( KEY_INPUT_SPACE ) ) { //space(決定)を押した
			//メニュー選択
			switch ( mCursorPosition ) {
				case SMENU_HAJIMEKARA: //はじめから
					//TODO:ストーリーテリングを作る
					mGameStartFlag = true;
					break;
				case SMENU_TUDUKIKARA: //つづきから
					mGameStartFlag = true;
					break;
				default:
					mGameStartFlag = false;
					break;
			}
		}
			//TODO:debag DrawFormatString( 400, 0, GetColor( 255, 255, 255 ), "cursor:%d", mCursorPosition );
	}
	
	void Title::startMenu() {
		//menu描画
		mWindow->drawWindow( 240, 200, 380, 400, Window::WINDOW_LINE );
		mWindow->drawListOnWindow( 2, mCursorPosition,  list);
	}

	void Title::changeCursor() {
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
			mCursorPosition = ( mCursorPosition > 1 ) ? 1 : mCursorPosition;

		}
		mOldKey[ 0 ] = mNowKey[ 0 ]; //現在の状態を保存
		mOldKey[ 1 ] = mNowKey[ 1 ];

	}

} //namespace Sequence