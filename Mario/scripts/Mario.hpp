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
        marioTex = LoadGraph("./resource/mario_idle.png");
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

    void Draw() {
        DrawGraph( x , y , marioTex, TRUE);
    }
};