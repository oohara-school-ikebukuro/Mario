#include "./DxLibHelper.h"

#include <DxLib.h>
#include <algorithm>

DxLibHelper::DxLibHelper(int fps) : fps(fps)
{
    if (fps <= 0) { // 0で割れないので
        fps = std::clamp(fps, 1, 1000);
    }
    frameTime = 1000 / fps;
    updateTime = GetNowCount();
}

int DxLibHelper::Init(WindowData window)
{
    switch (window.type)
    {
        case ScreenType::FULL_SCREEN:
            ChangeWindowMode(TRUE);  // フルスクリーン
            break;

        case ScreenType::WINDOWED:
        default:
            ChangeWindowMode(TRUE);  // ウィンドウモード
            SetGraphMode(window.width, window.height, 32);  // 解像度指定
            break;
    }

    if (DxLib_Init() == -1) 
    {
        return -1; // 初期化失敗時に終了
    }

    SetDrawScreen(DX_SCREEN_BACK);  // ダブルバッファリング

    return 0;
}

void DxLibHelper::RefreshScreen()
{
    // 描画処理
    ScreenFlip();       // 画面更新
    ProcessMessage();   // Windowsメッセージ処理
    ClearDrawScreen();  // 画面クリア

    // フレーム時間を計測
    int now = GetNowCount(); // フレーム開始時間を取得
    int deltaTime = now - updateTime;

    // 必要なら待機して、更新時間
    if (deltaTime < frameTime) {
        WaitTimer(frameTime - deltaTime);
        updateTime = GetNowCount();
    }
    else {
        updateTime = now;
    }
}

// DXLibの終了処理
void DxLibHelper::Cleanup() {
    DxLib_End();
}