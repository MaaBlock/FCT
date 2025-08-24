#include "path.h"
namespace FCT
{
    std::string GetUniqueDirectoryName(const std::filesystem::path& baseDir, const std::string& baseName)
    {
        std::filesystem::path targetDir = baseDir / baseName;

        if (!std::filesystem::exists(targetDir)) {
            return baseName;
        }

        int counter = 1;
        std::string uniqueName;
        std::filesystem::path uniqueDir;

        do {
            uniqueName = baseName + "_" + std::to_string(counter);
            uniqueDir = baseDir / uniqueName;
            counter++;
        } while (std::filesystem::exists(uniqueDir));

        return uniqueName;
    }
    /*
    std::string GetUniqueDirectoryName(const std::string& baseDir, const std::string& baseName)
    {
        return GetUniqueDirectoryName(std::filesystem::path(baseDir), baseName);
    }*/
}
