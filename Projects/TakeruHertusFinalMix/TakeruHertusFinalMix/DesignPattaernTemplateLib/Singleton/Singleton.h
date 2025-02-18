#pragma once
#include <iostream>
#include <memory>
#include <mutex>

/// <summary>
/// シングルトンテンプレートクラス
/// </summary>
/// <typeparam name="T">シングルトン化したいクラス</typeparam>
template<typename T>
class Singleton
{
public:
	//インスタンスを取得する静的メソッド
	static std::shared_ptr<T> Instance()
	{
		//初回呼び出し時にインスタンスを生成
		std::call_once(initFlag, []() {instance = std::shared_ptr<T>(new T()); });
		return instance;
	}

protected:
	/*protectedにして外部からの生成を防ぐ*/
	Singleton() {}
	~Singleton() {}

private:
	static std::shared_ptr<T> instance;//唯一のインスタンス
	static std::once_flag initFlag;	   //初期化フラグ
	
	//コピーコンストラクタと代入演算子を削除して複製を防ぐ
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

};
//静的メンバ変数の初期化
template<typename T>
std::shared_ptr<T> Singleton<T>::instance = nullptr;

template<typename T>
std::once_flag Singleton<T>::initFlag;

/*MEMO*/
//シングルトンとはインスタンスを１つだけ作成してそれを使いまわすこと。
// これにより複数のインスタンスを禁止することができるため。
// 同じデータに対する変更の競合を防ぐことができる。
// 例：設定情報やサウンドマネージャー、アニメーションなど
// また安全性が高くグローバルなアクセスを提供することができる。