#pragma once

#include "./variable/Vector2.hpp"

#include <DxLib.h>
#include <string>

// ゲームのメイン実行を管理するマネージャー
class TitleManager {

public: // ← 忘れずに

    std::string titleName;

    float animTime;
    int frame;
    Vector2<int> currentPoint;
    Vector2<int> startPoint;
    Vector2<int> endPoint;

    bool isEnd; // タイトルが終了したことを表します。

    // コンストラクタ
    TitleManager()
        : startPoint({ 1000 , -80 })
        , endPoint({ 0 , 320})
        , currentPoint(startPoint)
        , animTime(2.0f)
        , titleName("ジョージの逆襲")
        , isEnd(false){
    }

    void Init() {
    }

    // Lerp 関数の定義（ヘッダ内など共通で使える場所に）
    float Lerp(float a, float b, float t) {
        return a * (1.0f - t) + b * t;
    }

    void Update() {

        if (frame < animTime * 60) {
            frame++;

            currentPoint.x = Lerp(startPoint.x, endPoint.x, frame / (60 * animTime));
            currentPoint.y = Lerp(startPoint.y, endPoint.y, frame / (60 * animTime));
        }

        // Titleは終了している。
        if (isEnd == true) {
            return;
        }

        // エンターキーを押したとき・・
        if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
            isEnd = true;
        }
    }

    int Clamp(int a,int min,int max) {
        if (a <= min) return min;
        if (a > max) return max;
        return a;
    }

    void Draw() {

        SetFontSize(80);
        DrawString(currentPoint.x, currentPoint.y, titleName.c_str()
            , GetColor(255,255,255));

        /*
        int frameTime = frame / 60 / animTime;
        int fontHandle = CreateFontToHandle("MS ゴシック", 80, 0);
        DrawRotaStringToHandle(currentPoint.x, currentPoint.y, 1, 1, 0, 0
            , 3.14 / 4 * frameTime
            , GetColor(255, 255, 255)
            , fontHandle
            , GetColor(255, 0, 0)
            , FALSE,titleName.c_str());
            */
    }

    void End() {
    }
};
