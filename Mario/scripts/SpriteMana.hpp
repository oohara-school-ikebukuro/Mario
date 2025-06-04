#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "DxLib.h"

// シングルトンなクラスです
class SpriteMana {

private:
    SpriteMana() = default;

    std::unordered_map<std::string, int> textures;
    std::unordered_map<std::string, std::vector<int>> divTextures;

    // コピー禁止
    SpriteMana(const SpriteMana&) = delete;
    SpriteMana& operator=(const SpriteMana&) = delete;

public:

    static SpriteMana& Ins() {
        static SpriteMana instance;
        return instance;
    }

    int LoadTexture(const std::string& filePath) {
        if (textures.find(filePath) == textures.end()) {
            int handle = LoadGraph(filePath.c_str());
            if (handle == -1) {
                return -1; // ロード失敗
            }
            textures[filePath] = handle;
        }
        return textures[filePath];
    }

    std::vector<int> LoadDivTexture(const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize) {
        if (divTextures.find(filePath) == divTextures.end()) {
            std::vector<int> handles(allNum);
            if (LoadDivGraph(filePath.c_str(), allNum, xNum, yNum, xSize, ySize, handles.data()) == -1) {
                return {}; // ロード失敗
            }
            divTextures[filePath] = handles;
        }
        return divTextures[filePath];
    }

    void ReleaseAll() {
        for (auto& pair : textures) {
            DeleteGraph(pair.second);
        }
        textures.clear();

        for (auto& pair : divTextures) {
            for (int handle : pair.second) {
                DeleteGraph(handle);
            }
        }
        divTextures.clear();
    }

    ~SpriteMana() {
        ReleaseAll();
    }
};
