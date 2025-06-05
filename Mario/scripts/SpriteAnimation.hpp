#pragma once

#include "./variable/Vector2.hpp"

#include <DxLib.h>
#include <string>
#include <map>
#include <vector>

// マリオとか、敵でアニメーション処理を作るのがめんどくさいので、
// アニメーションの処理全部ここに書きます。
class SpriteAnimation {


    int textureSize;
    int textureHandle;

    int animType; // 現在進行中の、アニメーション種別
    int animNum;  // 現在進行中の、アニメーション番号
    int frame;    // 現在のアニメーションを実行したフレーム時間

    // アニメーション用の、頂点座標リスト
    std::map<int, std::vector<Vector2<int>>> animVertex;

public:

    // コンストラクタ
    SpriteAnimation(int textureSize) // マリオだと、32が入る予定
        : textureSize(textureSize),textureHandle(0)
        , animType(0) , animNum(0) , frame(0) {
    }

    // アニメーション種別を変更します。
    void SetAnimType(int newType) {

        if(animType != newType)
        {
            animType = newType;
            animNum = 0;
            frame = 0;
        }
    }

    // add : 追加
    // アニメーションを追加しますよという関数
    void AddAnimation(int animType, std::vector<Vector2<int>> vertexVec) {

        animVertex.emplace(animType, vertexVec);
    }

    // ロード処理
    void Load(const std::string& fileName) {
        textureHandle = LoadGraph(fileName.c_str());
    }

    // 描画処理
    // x : x座標
    // y : y座標
    // isDirLeft : 左向いてるか？
    void Draw(int x , int y, bool isDirLeft) {
        
        // animVertex に、 animType の値が存在しますか？というチェックをする
        if (animVertex.find(animType) == animVertex.end()) {
            return;
        }

        // 5フレーム経ったら、画像変えます。
        frame++;
        if (frame > 5) {
            animNum++;
            frame = 0;

            // 画像の範囲外に行くとまずいので
            // 一番左に戻しましょう
            if (animNum >= animVertex[animType].size()) {
                animNum = 0;
            }
        }

        Vector2<int> vertex = animVertex[animType][animNum];
        DrawRectGraph(
              x                        // x座標
            , y                        // y座標
            , vertex.x * textureSize   // 表示する画像位置の左上頂点座標x
            , vertex.y * textureSize   // 表示する画像位置の左上頂点座標y
            , textureSize              // 画像サイズx
            , textureSize              // 画像サイズy
            , textureHandle            // 使う画像のハンドル(LoadGraphした奴)
            , TRUE                     // 透明を使うか？
            , isDirLeft                // 画像を反転させるか？ 横に
            , FALSE                    // 画像を反転させるか？ 縦に
        );
    }

};
