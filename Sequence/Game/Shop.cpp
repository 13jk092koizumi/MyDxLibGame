#include "DxLib.h"
#include "Sequence/Game/Shop.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/BaseTown.h"
#include "Image.h"

namespace Sequence {
	namespace Game {

		Shop::Shop() : mImage(0) {
			mImage = new Image( "data/image/shop.png" );
		}

		Shop::~Shop() {
			delete mImage; mImage = 0;
		}

		Child* Shop::update( Parent* ) {
			Child* next = this;

			//�摜�`��
			mImage->setImgHandle();
			mImage->drawGraph( 0, 0 );

			//�X�ƍs��������
			printfDx( "push B go to BaseTown\n" );
			if ( CheckHitKey( KEY_INPUT_B ) ) {
				clsDx();
				next = new BaseTown;
			}

			ScreenFlip();
			//WaitKey();

			return next;
		}

	} //namespace Game
} //namespace Sequence