#pragma once

#include "./SpriteAnimation.hpp"
#include <DxLib.h>

class Mario {

public:

    int pixelSize;
    float x, y;

    SpriteAnimation spAnim;

    // コンストラクタ
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0), spAnim(pixelSize){
    }

    // デストラクタ
    // Marioが消えた時に呼ばれる処理
    ~Mario() {
    }

    void Load() {
        spAnim.Load("./resource/mario.png");
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
        spAnim.Draw(x, y);

        // 書かなくてよいです↓
        // DrawGraph( x + 7 * 32, y , marioTex, TRUE);
    }
};