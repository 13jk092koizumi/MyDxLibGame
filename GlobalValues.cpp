#include "DxLib.h"
#include "GlobalValues.h"

namespace Global {
	const unsigned int WHITE = GetColor( 255, 255, 255 );
	void moveScreen( int flameCount, char* message ) {
		DrawBox( 0, 0, 640, 480, GetColor( 0, 0, 0 ), true ); //画面を真っ暗に
		int n = flameCount % 9;
		//なんちゃってローディング画面(いきなり画面が変わると味気ないので)
		switch ( n ) {
			case 0:case 1: case 2:
				DrawFormatString( 400, 450,WHITE, "%s.", message );
				break;
			case 3:case 4: case 5:
				DrawFormatString( 400, 450, WHITE, "%s..", message );
				break;
			case 6: case 7: case 8:
				DrawFormatString( 400, 450, WHITE, "%s...", message );
				break;
			default:
				break;
		}
	}

	bool isKeyOn( int keycode ) {
		if ( CheckHitKey( keycode ) ) {
			return true;
		} else {
			return false;
		}
	}

	char* boolalpha( int num ) {
		if ( num == 0 ) {
			return "true";
		} else if ( num == 1 ) {
			return "false";
		}
		return "it's not boolean";
	}

}