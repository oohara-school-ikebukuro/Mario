#pragma once

#include "./variable/Vector2.hpp"

#include <DxLib.h>
#include <string>
#include <map>
#include <vector>

// マリオとか、敵でアニメーション処理を作るのがめんどくさいので、
// アニメーションの処理全部ここに書きます。
class SpriteAnimation {

public:

    int textureSize;
    int textureHandle;

    int animNum;  // 現在進行中の、アニメーション番号
    int frame;    // 現在のアニメーションを実行したフレーム時間

    // アニメーション用の、頂点座標リスト
    std::map<int, std::vector<Vector2<int>>> animVertex;

    // コンストラクタ
    SpriteAnimation(int textureSize) // マリオだと、32が入る予定
        : textureSize(textureSize),textureX(0), textureY(0),textureHandle(0) {

        // アニメーション用に、頂点座標を登録していく
        // ダッシュ用
        animVertex.insert({ 0, std::vector<Vector2<int>>() });

        animVertex[0].push_back({ 1,0 });
        animVertex[0].push_back({ 2,0 });
        animVertex[0].push_back({ 3,0 });
        animVertex[0].push_back({ 2,0 });
        animVertex[0].push_back({ 1,0 });
        animVertex[0].push_back({ 0,1 });
        animVertex[0].push_back({ 1,1 });
        animVertex[0].push_back({ 2,1 });
        animVertex[0].push_back({ 3,1 });
        animVertex[0].push_back({ 2,1 });
        animVertex[0].push_back({ 1,1 });
        animVertex[0].push_back({ 0,1 });

        // ☆ チャレンジ
        // ジャンプの設定を追加してほしいです。
        animVertex.insert({ 1, std::vector<Vector2<int>>() });

        animVertex[1].push_back({ 0,2 });
        animVertex[1].push_back({ 1,2 });
        animVertex[1].push_back({ 2,2 });
    }

    // ロード処理
    void Load(const std::string& fileName) {
        textureHandle = LoadGraph(fileName.c_str());
    }

    // 描画処理
    // x : x座標
    // y : y座標
    void Draw(int x , int y) {
        
        // 5フレーム経ったら、画像変えます。
        frame++;
        if (frame > 5) {
            animNum++;
            frame = 0;

            // 画像の範囲外に行くとまずいので
            // 一番左に戻しましょう
                animNum = 0;
            }
        }

        DrawRectGraph(
              x                        // x座標
            , y                        // y座標
            , vertex.x * textureSize   // 表示する画像位置の左上頂点座標x
            , vertex.y * textureSize   // 表示する画像位置の左上頂点座標y
            , textureSize              // 画像サイズx
            , textureSize              // 画像サイズy
            , textureHandle            // 使う画像のハンドル(LoadGraphした奴)
            , TRUE                     // 透明を使うか？
            , FALSE                    // 画像を反転させるか？
        );
    }

};
