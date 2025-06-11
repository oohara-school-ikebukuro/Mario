#pragma once

#include "./variable/Vector2.hpp"
#include "./Sprite.hpp"

#include <DxLib.h>
#include <string>
#include <map>
#include <vector>

// マリオとか、敵でアニメーション処理を作るのがめんどくさいので、
// アニメーションの処理全部ここに書きます。
class SpriteAnimation {

    int textureSize;

    int animType; // 現在進行中の、アニメーション種別
    int animNum;  // 現在進行中の、アニメーション番号
    int frame;    // 現在のアニメーションを実行したフレーム時間

    // アニメーション用の、頂点座標リスト
    std::map<int, std::vector<int>> animVertex;

    // スプライトを保持
    Sprite sprite;

public:

    // 現在のアニメーションを返しますよという処理
    int GetAnimType() { return animType; }

    // コンストラクタ
    SpriteAnimation(int textureSize) // マリオだと、32が入る予定
        : textureSize(textureSize)
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
    void AddAnimation(int animType, std::vector<int> animNumVec) {

        animVertex.emplace(animType, animNumVec);
    }

    // ロード処理
    void Load(const std::string& fileName, const std::map<int, Rect>& textures) {
        sprite.Load(fileName);

        // テクスチャ分割設定を、Spriteに反映していきます。
        for (const auto& pair : textures) {
            sprite.SetTexture(pair.first, pair.second);
        }
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

        // 画像描画します。
        int anim = animVertex[animType][animNum];
        int width = textureSize;
        int height = textureSize;
        sprite.Draw(
            { x , y , width ,  height },
            anim,isDirLeft,FALSE
        );

        /*
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
        */
    }
};
