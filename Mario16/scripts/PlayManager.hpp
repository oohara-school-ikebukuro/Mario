#pragma once

#include "./Stage.hpp"

// ゲームのメイン実行を管理するマネージャー
class PlayManager {

    Stage stage;

public: // ← 忘れずに

    PlayManager() : stage(16) {
    }

    void Init() {
        stage.Load("./stage/stage01.csv");
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
