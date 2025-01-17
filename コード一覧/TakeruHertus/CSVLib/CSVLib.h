#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>




class CSVLib
{
public:
	static std::vector<std::vector<std::string>> read(const std::string& filename);

	static void write(const std::string& filename, const std::vector<std::vector<std::string>>& data);
};


