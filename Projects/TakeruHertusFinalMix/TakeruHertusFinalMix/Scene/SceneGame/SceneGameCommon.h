#pragma once
/*ゲームシーンで扱うクラスをインクルード*/

/*オブジェクト*/

//プレイヤー
#include "../../Object/Character/Player/Player.h"

#include "../../Object/Character/Enemy/Enemy_Fox/Enemy_Fox.h"

//敵マネージャー
#include "../../Object/Character/Enemy/Manager/SpownManager.h"

//ドラゴン敵
#include "../../Object/Character/Enemy/Enemy_Doragon/Enemy_Doragon.h"

//カメラ
#include "../../Object/Camera/Camera.h"

//マップ
#include "../../Object/Map/MapTutorial/MapTutorial.h"

//ライト
#include "../../Object/Light/Light.h"

//スカイドーム
#include "../../Object/SkyDome/SkyDome.h"

//当たり判定
#include "../../Object/Collision/Collision.h"

//エフェクト
#include "../../Object/ObjectEffecter/ObjectEffecter.h"

//コマンドシステム
#include "../../Object/Command/Command.h"

//TS剣
#include "../../Object/Weapon/TSSword/TSSword.h"

//TS盾
#include "../../Object/Weapon/TSShield/TSShield.h"

//TS杖
#include "../../Object/Weapon/TSRod/TSRod.h"

//セーブシステム
#include "../../Object/SavePoint/SavePoint.h"