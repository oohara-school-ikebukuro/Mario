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
            x -= pixelSize * 0.1f;
        }

        if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
            x += pixelSize * 0.1f;
        }
    }

    void Draw() {

        spAnim.Draw(x, y);
    }
};