//
// Created by Administrator on 2025/4/22.
//
#include "./ModelLoader.h"
#ifndef ASSIMP_MODELLOADER_H
#define ASSIMP_MODELLOADER_H
namespace FCT {
    class Assimp_ModelLoader : public ModelLoader{
    public:
        std::unique_ptr<ModelData> loadModel(const std::string& path) override;
        ModelInfo::SceneInfo loadModelInfo(const std::string& path) override;
        std::set<std::string> resolveTexturePaths(const std::string& modelPath) const override;
    protected:
        std::set<std::string> getPlatformSupportedExtensions() const override;
    };


}
#endif //ASSIMP_MODELLOADER_H
