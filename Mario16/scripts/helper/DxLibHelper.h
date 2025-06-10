#pragma once

enum class ScreenType 
{
    WINDOWED,      // ウィンドウモード
    FULL_SCREEN    // フルスクリーン
};

struct WindowData
{
    ScreenType type;
    int width;
    int height;
};

class DxLibHelper
{
private:

    int fps;        // 1秒毎の描画回数
    int frameTime;  // 1フレの時間
    int updateTime; // 更新時刻

public:

    DxLibHelper(int fps);

    // DXLibの初期化
    int Init(WindowData window);

    // 画面クリア・更新処理
    // 毎ループで呼んでください
    void RefreshScreen();

    // DXLibの終了処理
    void Cleanup();
};
