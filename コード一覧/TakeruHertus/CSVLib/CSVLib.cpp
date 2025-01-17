#include "CSVLib.h"

std::vector<std::vector<std::string>> CSVLib::read(const std::string& filename)
{
	std::ifstream file(filename);
	std::vector<std::vector<std::string>> data;
	std::string line;

	if (!file.is_open()) {
		throw std::runtime_error("ファイルを開けませんでした: " + filename);
	}

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		std::vector<std::string> row;

		while (std::getline(ss, token, ',')) {
			row.push_back(token);
		}

		data.push_back(row);
	}

	return data;
}

void CSVLib::write(const std::string& filename, const std::vector<std::vector<std::string>>& data)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		throw std::runtime_error("ファイルを開けませんでした:" + filename);
	}

	for (const auto& row : data)
	{
		for (size_t i = 0; i < row.size(); i++)
		{
			file << row[i];
			if (i != row.size() - 1)
			{
				file << ",";
			}
		}
		file << "\n";
	}


}
