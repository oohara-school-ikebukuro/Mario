#pragma once

#include <DxLib.h>
#include <string>

// マリオとか、敵でアニメーション処理を作るのがめんどくさいので、
// アニメーションの処理全部ここに書きます。
class SpriteAnimation {

public:

    int textureSize;
    int textureX, textureY;
    int textureHandle;

    // コンストラクタ
    SpriteAnimation(int textureSize) // マリオだと、32が入る予定
        : textureSize(textureSize),textureX(0), textureY(0),textureHandle(0) {
    }

    // ロード処理
    void Load(const std::string& fileName) {
        textureHandle = LoadGraph(fileName.c_str());
    }

    // 描画処理
    // x : x座標
    // y : y座標
    void Draw(int x , int y) {
        
        DrawRectGraph(
              x                        // x座標
            , y                        // y座標
            , textureX * textureSize   // 表示する画像位置の左上頂点座標x
            , textureY * textureSize   // 表示する画像位置の左上頂点座標y
            , textureSize              // 画像サイズx
            , textureSize              // 画像サイズy
            , textureHandle            // 使う画像のハンドル(LoadGraphした奴)
            , TRUE                     // 透明を使うか？
            , FALSE                    // 画像を反転させるか？
        );
    }

};
