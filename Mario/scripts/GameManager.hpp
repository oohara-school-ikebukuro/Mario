#pragma once

#include "./Stage.hpp"
#include <DxLib.h>

class GameManager {

public:

    const int fps; // FPS設定
    const int winX,winY; // ウィンドウサイズ

    bool isRun;

    Stage stage;

    GameManager() : fps(60) , winX(640) , winY(640), isRun(true)
     , stage(32){
    }

    void Init() {
        stage.Load("./stage/stage01.txt");
    }

    void Update() {
        stage.Update();
    }

    void Draw() {

        stage.Draw();
    }

    void End() {

        stage.End();
    }
};
