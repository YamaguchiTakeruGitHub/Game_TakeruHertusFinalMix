#pragma once
//==========================================================//
// コンポーネントの集約
// MEMO:コンポーネントを追加したらここにインクルードを追加
//==========================================================//

#include "../ComponentControlCamera/ComponentControlCamera.h"//カメラ操作を管理
#include "../ComponentEventCamera/ComponentEventCamera.h"	 //イベントカメラ

#include "../ComponentTransform/ComponentTransform.h"		//位置・回転・スケールを管理

#include "../ComponentRightBody/ComponentRightBody.h"		//物理データを管理

#include "../ComponentModel/ComponentModel.h"				//モデルの初期化、更新、描画、解放を管理

#include "../ComponentMovement/ComponentMovement.h"			//移動処理を管理

#include "../ComponentPolygonDraw/ComponentPolygonDraw.h"	//モデルのポリゴン描画

#include "../ComponentHealth/ComponentHealth.h"				//ヒットポイントを管理

/*アニメーション関係*/
#include "../ComponentAnimation/ComponentAnimation.h"		//アニメーションを管理

/*ライト関係*/
#include "../ComponentLight/Direction/ComponentDirectionLight.h"//ディレクションライトを管理

/*当たり判定のまとめ*/
#include "ComponentCollisionCommon.h"//全ての当たり判定を管理

/*コマンドシステム*/
#include "../ComponentComandSystem/ComponentComandSystem.h"//コマンドシステムを管理
#include "../ComponentComandShortcutSystem/ComponentComandShortcutSystem.h"//ショートカットコマンドシステムを管理

/*エフェクト*/
#include "../ComponentEffect/ComponentEffect.h"//エフェクト

