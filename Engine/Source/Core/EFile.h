#pragma once

#include <string>
#include <filesystem>

namespace File {

	std::string GetFilePath();
	bool SetFilePath(const std::string& filepath);

	bool FileExist(const std::string& filepath);

	bool GetFileSize(const std::string& filepath,int* size);

	bool readFile(const std::string& filepath, std::string& buffer);
}