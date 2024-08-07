#include "EFile.h"
#include <iostream>
#include <fstream>

using namespace std;

string File::GetFilePath()
{
    return filesystem::current_path().string();
}

bool File::SetFilePath(const string& filepath)
{
    error_code ec;
    filesystem::current_path(filepath,ec);
    return !ec;
}

bool File::FileExist(const std::string& filepath)
{
    return filesystem::exists(filepath);
}

bool File::GetFileSize(const std::string& filepath, int* size)
{
    error_code ec;
     *size = (int)filesystem::file_size(filepath,ec);
     return !ec;
}

bool File::readFile(const std::string& filepath, std::string& buffer)
{
    if (!FileExist(filepath)) {
        cerr << "File does not exist: " << filepath << endl;
        return false;
    }

    ifstream stream(filepath);
    if (!stream.is_open()) {
        cerr << "Could not open file: " << filepath << endl;
        return false;
    }

    ostringstream ostream;
    ostream << stream.rdbuf();

    buffer = ostream.str();

    return true;
}
