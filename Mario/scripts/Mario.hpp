#pragma once

#include "./SpriteMana.hpp"
#include "./Vector2.hpp"

#include <DxLib.h>

#include <map>

// 画像以下
// https://www.mariouniverse.com/sprites-nes-smb/

class Mario {

    enum class Anim {
          Idle
        , Dush
        , Jump
        , Jump_loop
    };

public:

    int pixelSize;
    float x, y;

    int marioTex;
    bool isDirRight;

    std::map<Anim, std::vector<Vector2<int>>> animTex;

    Anim animType; // 現在のアニメーション種別
    int animFrame; // 経過フレーム数
    int animNum;

    // コンストラクタ
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0)
        , marioTex(-1), isDirRight(true)
        , animType(Anim::Jump),animFrame(0),animNum(0)
    {
        // アニメーションのスプライト位置をここに追加していきます。
        animTex.insert({ Anim::Idle, {} });

        animTex[Anim::Idle].push_back({ 0,0 });

        animTex.insert({ Anim::Dush, {} });

        animTex[Anim::Dush].push_back({ 0,0 });
        animTex[Anim::Dush].push_back({ 1,0 });
        animTex[Anim::Dush].push_back({ 2,0 });
        animTex[Anim::Dush].push_back({ 3,0 });
        animTex[Anim::Dush].push_back({ 0,1 });
        animTex[Anim::Dush].push_back({ 1,1 });
        animTex[Anim::Dush].push_back({ 2,1 });
        animTex[Anim::Dush].push_back({ 3,1 });

        animTex.insert({ Anim::Jump, {} });
        animTex[Anim::Jump].push_back({ 0,2 });
        animTex[Anim::Jump].push_back({ 1,2 });
        animTex[Anim::Jump].push_back({ 2,2 });

        animTex.insert({ Anim::Jump_loop, {} });

        animTex[Anim::Jump_loop].push_back({ 2,2 });

    }

    // デストラクタ
    // Marioが消えた時に呼ばれる処理
    ~Mario() {
    }

    void SetAnim(Anim anim) {
    }

    void Load() {
        marioTex = SpriteMana::Ins().LoadTexture("./resource/mario.png");
    }

    void Update() {

        // ←
        if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
            x -= pixelSize * 0.05f;
            isDirRight = false;
        }

        if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
            x += pixelSize * 0.05f;
            isDirRight = true;
        }
    }

    void Draw() {

        // アニメーションを更新します。
        animFrame++;

        if (animFrame > 3) {
            animFrame = 0;
            animNum++;

            if (animNum >= animTex[animType].size()) {
                if (animType == Anim::Jump) {
                    animType = Anim::Jump_loop;
                }
                animNum = 0;
            }
        }

        Vector2<int> spritePos = animTex[animType][animNum];

        DrawRectGraph(x, y, spritePos.x * 32, spritePos.y * 32, 32, 32, marioTex, TRUE, !isDirRight);
    }
};