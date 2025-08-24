//
// Created by Administrator on 2025/8/24.
//

#ifndef PATH_H
#define PATH_H
namespace FCT
{
    std::string GetUniqueDirectoryName(const std::filesystem::path& baseDir, const std::string& baseName);
    //std::string GetUniqueDirectoryName(const std::string& baseDir, const std::string& baseName);
}
#endif //PATH_H
