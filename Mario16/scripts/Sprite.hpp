#pragma once

#include "Rect.hpp"
#include <map>
#include <string>
#include <DxLib.h>

// ※ Spriteは、DXLibのInitが終わった後に、生成してください。
class Sprite {

private:

    int textureHandle;
    std::map<int, Rect> textures;

public:
    
    Sprite() : textureHandle(0){}

    // テクスチャをロードして、texturesをリセットします。
    void Load(const std::string& fileName) {
        textureHandle = LoadGraph(fileName.c_str());
        textures.clear();
    }


    // 読み込んだデータを、Rectの値で切り抜けるように設定を追加する
    void SetTexture(int num, Rect rect) {
        textures.insert({ num, rect });
    }

private:

    // 画像描画 本体
    void Draw(Rect rect, Rect texRect)
    {
        // DrawRectGraph
        DrawRectExtendGraph(
              rect.x, rect.y         // 左上頂点座標
            , rect.x + rect.width    // 右下頂点座標
            , rect.y + rect.height   
            , texRect.x, texRect.y          // 画像の左上頂点座標
            , texRect.width, texRect.height // 画像の右下頂点座標
            , textureHandle // 使うテクスチャ
            , true); // 背景透明の可否
    }

public:

    // 画像描画 外部から呼ぶ用
    void Draw(Rect rect, int num, bool isFlipX = false, bool isFlipY = false) {

        // keyチェック
        if (!textures.count(num)) {
            return;
        }

        Rect texRect = textures[num];

        // 画像を横に反転しますよ
        if (isFlipX == true) {

            rect.x = rect.x + rect.width;
            rect.width = -rect.width;
        }

        // 画像を縦に反転しますよ
        if (isFlipY == true) {
            rect.y = rect.y + rect.height;
            rect.height = -rect.height;
        }

        // 画像描画
        Draw(rect, texRect);
    }
};