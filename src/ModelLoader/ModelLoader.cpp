#include "./ModelLoader.h"
namespace FCT {
    std::set<std::string> ModelLoader::resolveModePaths(const std::string& modelPath)
    {
        std::set<std::string> allPaths;

        std::string absoluteModelPath;
        try {
            if (std::filesystem::exists(modelPath)) {
                absoluteModelPath = std::filesystem::canonical(modelPath).string();
            } else {
                absoluteModelPath = std::filesystem::absolute(modelPath).string();
            }
            allPaths.insert(absoluteModelPath);
        } catch (const std::filesystem::filesystem_error&) {
            allPaths.insert(modelPath);
            absoluteModelPath = modelPath;
        }

        std::filesystem::path modelFilePath(absoluteModelPath);
        std::string extension = modelFilePath.extension().string();

        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        std::set<std::string> texturePaths = resolveTexturePaths(absoluteModelPath);
        allPaths.insert(texturePaths.begin(), texturePaths.end());

        std::set<std::string> specificDependencies = getModelSpecificDependencies(absoluteModelPath);

        std::filesystem::path modelDir = std::filesystem::path(absoluteModelPath).parent_path();
        for (const auto& relativePath : specificDependencies) {
            try {
                std::string absolutePath = std::filesystem::canonical(modelDir / relativePath).string();
                allPaths.insert(absolutePath);
            } catch (const std::filesystem::filesystem_error&) {
                std::string absolutePath = std::filesystem::absolute(modelDir / relativePath).string();
                allPaths.insert(absolutePath);
            }
        }

        return allPaths;
    }

    std::set<std::string> ModelLoader::getModelSpecificDependencies(const std::string& modelPath) const
    {
        std::set<std::string> dependencies;

        std::filesystem::path modelFilePath(modelPath);
        std::string extension = modelFilePath.extension().string();
        std::string baseName = modelFilePath.stem().string();

        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        if (extension == ".obj") {
            dependencies.insert(baseName + ".mtl");
        }
        else if (extension == ".gltf")
        {
            dependencies.insert(baseName + ".bin");
        }
        else if (extension == ".fbx")
        {

        } else if (extension == ".glb")
        {

        } else if (extension == ".usdz")
        {

        }
        return dependencies;
    }

    std::set<std::string> ModelLoader::getSupportedExtensions() const
    {
        auto platform = getPlatformSupportedExtensions();
        std::set<std::string> supportedExtensions = {
            ".obj",
            ".gltf",
            ".fbx",
            ".glb",
            ".usdz"
        };
        return supportedExtensions;
    }
}
