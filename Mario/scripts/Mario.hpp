#pragma once

#include <DxLib.h>

class Mario {

public:

    int pixelSize;
    float x, y;

    int marioTex;

    // コンストラクタ
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0), marioTex(-1){
    }

    // デストラクタ
    // Marioが消えた時に呼ばれる処理
    ~Mario() {
        DeleteGraph(marioTex);
    }

    void Load() {
        marioTex = LoadGraph("./resource/mario.png");
    }

    void Update() {

        // ←
        if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
            x -= pixelSize * 0.25f;
        }

        if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
            x += pixelSize * 0.25f;
        }
    }

    int frame = 0;
    int textureX = 0;
    void Draw() {

        // 5フレーム経ったら、画像変えます。
        frame++;
        if (frame > 5) {
            textureX++;
            frame = 0;

            // 画像の範囲外に行くとまずいので
            // 一番左に戻しましょう
            if (textureX >= 4) {
                textureX = 0;
            }
        }

        // 
        DrawRectGraph(
              x          // x座標
            , y          // y座標
            , textureX * 32     // 表示する画像位置の左上頂点座標x
            , 0 * 32     // 表示する画像位置の左上頂点座標y
            , 32         // 画像サイズx
            , 32         // 画像サイズy
            , marioTex   // 使う画像のハンドル(LoadGraphした奴)
            , TRUE       // 透明を使うか？
            , FALSE      // 画像を反転させるか？
        );

        // 書かなくてよいです↓
        DrawGraph( x + 7 * 32, y , marioTex, TRUE);
    }
};