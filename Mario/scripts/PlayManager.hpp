#pragma once

#include "./Stage.hpp"

// ゲームのメイン実行を管理するマネージャー
class PlayManager {

    Stage stage;

public: // ← 忘れずに

    PlayManager() : stage(32) {
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
