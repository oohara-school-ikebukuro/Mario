#pragma once

#include "./TitleManager.hpp"
#include "./PlayManager.hpp"
#include <DxLib.h>

class GameManager {

    // ゲームの現在の状態
    enum class GameStateType {
          None
        , Title
        , Play
    };

public:

    const int fps; // FPS設定
    const int winX,winY; // ウィンドウサイズ

    bool isRun;

    GameStateType gameState; // 現在のゲームの状態

    // マネージャー
    TitleManager titleMana;
    PlayManager playMana; 

    // コンストラクタ
    GameManager() : fps(60) , winX(640) , winY(640), isRun(true)
    , gameState(GameStateType::None){
    }

    //  最初の初期化
    void Init() {

        // 最初のステータスを、Playに設定します。
        ChangeState(GameStateType::Title);
    }

    void Update()
    {
        switch (gameState) {
            case GameStateType::Title:
            {
                titleMana.Update();

                if (titleMana.isEnd == true) {
                    ChangeState(GameStateType::Play);
                }
                break;
            }
            case GameStateType::Play:
                playMana.Update();
                break;
        }
    }

    void Draw() 
    {
        switch (gameState) 
        {
            case GameStateType::Title:
            {
                titleMana.Draw();
                break;
            }
            case GameStateType::Play:
            {
                playMana.Draw();
                break;
            }
        }
    }

    void ChangeState(const GameStateType& newState) {

        // 現在のゲームステートを終了させます。
        switch (gameState) {
            case GameStateType::Title:
                titleMana.End();
                break;
            case GameStateType::Play:
                playMana.End();
                break;
        }

        // 新しいステータスに移動
        gameState = newState;

        switch (newState) {
            case GameStateType::Title:
            {
                titleMana.Init();
                break;
            }
            case GameStateType::Play:
            {
                playMana.Init();
                break;
            }
        }
    }
};
