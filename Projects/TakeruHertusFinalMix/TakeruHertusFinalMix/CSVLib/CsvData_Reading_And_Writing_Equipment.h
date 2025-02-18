#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>//デバック用

/*===========================================*/
// 外部データの読み込み書き込みを楽にするライブラリ
// 参考元：ゼロから学ぶC++
/*===========================================*/
namespace CSVLib
{
	/// <summary>
	/// CSVファイルにデータを書き込む
	/// </summary>
	/// <param name="_fileName">ファイルのパス</param>
	/// <param name="_data">２次元配列</param>
	void WriteCSV(const std::string& _fileName, const std::vector<std::vector<std::string>>& _data);

	/// <summary>
	/// CSVファイルを読み込む
	/// </summary>
	/// <param name="_filename">読み込むファイルの名前</param>
	/// <returns>データ</returns>
	std::vector<std::vector<std::string>> ReadCSV(const std::string& _fileName);

	/// <summary>
	/// 指定したセルをそのままデータとして取得する
	/// </summary>
	/// <param name="_data">2次元配列</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <returns>指定されたセルのデータ</returns>
	std::string GetCell(const std::vector<std::vector<std::string>>& _data, int _row, int _col);

	/// <summary>
	/// 指定したセルを文字列(const char*型)として取得
	/// </summary>
	/// <param name="_data">2次元配列</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <returns></returns>
	const char* GetCell_ConstChar(const std::vector<std::vector<std::string>>& _data, int _row, int _col);

	/// <summary>
	/// 指定したセルを文字列(String型)として取得
	/// </summary>
	/// <param name="_data">2次元配列</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <returns>指定されたセルのデータ(string)</returns>
	std::string GetCell_String(const std::vector<std::vector<std::string>>& _data, int _row, int _col);

	/// <summary>
	/// 指定したセルを整数として取得
	/// </summary>
	/// <param name="_data">2次元配列(縦)</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <returns>指定されたセルのデータ(int)</returns>
	int GetCell_Int(const std::vector<std::vector<std::string>>& _data, int _row, int _col);
	

	/// <summary>
	/// 指定したセルを浮動小数点として取得
	/// </summary>
	/// <param name="_data">2次元配列(縦)</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <returns>指定されたセルのデータ(float)</returns>
	float GetCell_float(const std::vector<std::vector<std::string>>& _data, int _row, int _col);

	/// <summary>
	///  CSVデータの特定のセルを数値に変換して更新する
	/// </summary>
	/// <param name="_data">2次元配列(縦)</param>
	/// <param name="_row">列(縦)</param>
	/// <param name="_col">行(横)</param>
	/// <param name="_value">変換する数値</param>
	void UpdateCell_Value_Trans_String(std::vector<std::vector<std::string>>& _data, int _row, int _col, float _value);
	



	//===========================================================
	// ＜ユーザー定義関数＞
	// 以下には使用者が扱いやすくするために作成するスペースとする
	//===========================================================
	namespace User_Subscription
	{
		/// <summary>
		/// IDを検索してNumberにの値を取得する(ユーザー定義のサンプル)
		/// </summary>
		/// <param name="_data">2次元配列(縦)</param>
		/// <param name="_targetID">指定のID</param>
		/// <returns></returns>
		std::string GetNumberByID(const std::vector<std::vector<std::string>>& _data, const std::string& _targetID);
	}
}