#include "CsvData_Reading_And_Writing_Equipment.h"

void CSVLib::WriteCSV(const std::string& _fileName, const std::vector<std::vector<std::string>>& _data)
{
	std::ofstream file(_fileName);

	//もしファイルが見つからない場合
	if (!file) throw std::runtime_error("CSVファイルを開けませんでした。filename:" + _fileName);

	//2次元配列のデータをCSV形式で書き込む
	for (const auto& row : _data)
	{
		for (size_t i = 0; i < row.size(); i++)
		{
			file << row[i];//セルのデータの書き込み
			if (i < row.size() - 1) file << ",";//セルの区切り
		}
		file << "\n";//行(横)の終わり
	}

	file.close();//ファイルを閉じる
	std::cout << "CSVファイルに書き込みました:" << _fileName << std::endl;
}

std::vector<std::vector<std::string>> CSVLib::ReadCSV(const std::string& _fileName)
{
	std::ifstream file(_fileName);

	//もしファイルが見つからない場合
	if (!file) throw std::runtime_error("CSVファイルを開けませんでした。filename:" + _fileName);

	std::vector<std::vector<std::string>> data;
	std::string line;

	//１行(横)ずつ読み込む
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::vector<std::string> row;
		std::string cell;

		//カンマ区切りでデータを分割して配列に格納
		while (std::getline(ss, cell, ','))
		{
			row.push_back(cell);
		}

		//1行(横)分のデータを追加
		data.push_back(row);
	}

	file.close();//ファイルを閉じる
	return data;//2次元配列(縦)を返す
}

std::string CSVLib::GetCell(const std::vector<std::vector<std::string>>& _data, int _row, int _col)
{
	//行(横)と列(縦)が範囲内であることを確認
	assert(_row >= 0 && _row < _data.size() && "行(横)の範囲が無効です！");
	assert(_col >= 0 && _col < _data[_row].size() && "列(縦)の範囲が無効です！");
	return _data[_row][_col];//指定したセルのデータを返す
}

const char* CSVLib::GetCell_ConstChar(const std::vector<std::vector<std::string>>& _data, int _row, int _col)
{
	if (_row < 0 || _row >= static_cast<int>(_data.size())) throw std::out_of_range("行(横)の範囲が無効です:" + std::to_string(_row));

	if (_col < 0 || _col >= static_cast<int>(_data[_row].size())) throw std::out_of_range("列(縦)の範囲が無効です:" + std::to_string(_col));

	return _data[_row][_col].c_str();
}

std::string CSVLib::GetCell_String(const std::vector<std::vector<std::string>>& _data, int _row, int _col)
{
	if (_row < 0 || _row >= static_cast<int>(_data.size())) throw std::out_of_range("行(横)の範囲が無効です:" + std::to_string(_row));

	if (_col < 0 || _col >= static_cast<int>(_data[_row].size())) throw std::out_of_range("列(縦)の範囲が無効です:" + std::to_string(_col));

	return _data[_row][_col];
}

int CSVLib::GetCell_Int(const std::vector<std::vector<std::string>>& _data, int _row, int _col)
{
	std::string value = GetCell_String(_data, _row, _col);

	try
	{
		return std::stoi(value);//文字列(縦)を整数に変換
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("数値変換エラー(int):" + value);
	}

}

float CSVLib::GetCell_float(const std::vector<std::vector<std::string>>& _data, int _row, int _col)
{
	std::string value = GetCell_String(_data, _row, _col);

	try
	{
		return std::stof(value);//文字列(縦)を浮動小数点に変換
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("数値変換エラー(float):" + value);
	}

}

void CSVLib::UpdateCell_Value_Trans_String(std::vector<std::vector<std::string>>& _data, int _row, int _col, float _value)
{
	if (_row < 0 || _row >= static_cast<int>(_data.size())) throw std::out_of_range("行(横)の範囲が無効です:" + std::to_string(_row));
	if (_col < 0 || _col >= static_cast<int>(_data[_row].size())) throw std::out_of_range("列(縦)の範囲が無効です:" + std::to_string(_col));

	_data[_row][_col] = std::to_string(_value);//数値を文字れtにへんかんして代入
}

std::string CSVLib::User_Subscription::GetNumberByID(const std::vector<std::vector<std::string>>& _data, const std::string& _targetID)
{
	int idColumn = 0;		//IDの列(縦)の位置（0行(横)目）
	int numberColumn = 4;	//Numberの列(縦)の位置(4行(横)目)ユーザーの設定

	//１行(横)目を飛ばして検索
	for (size_t i = 1; i < _data.size(); i++)
	{
		//指定したIDと一致する行(横)を見つけたら
		if (_data[i][idColumn] == _targetID)
		{
			//Numberの値を返す
			return _data[i][numberColumn];
		}
	}

	//一致するIDがない場合
	return "IDが見つかりません。";
}
