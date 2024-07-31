#include "EFile.h"

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
