#pragma once

#include "./Stage.hpp"
#include "./SpriteAnimation.hpp"
#include <DxLib.h>
#include <algorithm>
#include <cmath>

class Mario {

    enum class AnimType {
          Idle
        , Dush
        , Jump
    };

public:

    int pixelSize;   // 1マスのサイズ
    float x, y;      // 座標
    bool isDirLeft;  // 左向いてますか？

    float velocityY = 0;  // y軸の力
    float gravity = 0.3f; // 重力
    bool isJump = false;  // ジャンプしてますか？

    SpriteAnimation spAnim;

    // コンストラクタ
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0)
        , spAnim(pixelSize),isDirLeft(true){

        // アニメーション用に、頂点座標を登録していく
        std::vector<Vector2<int>> vertexVec;

        // ダッシュの登録
        vertexVec.push_back({ 1,0 });
        vertexVec.push_back({ 2,0 });
        vertexVec.push_back({ 3,0 });
        vertexVec.push_back({ 2,0 });
        vertexVec.push_back({ 1,0 });
        vertexVec.push_back({ 0,1 });
        vertexVec.push_back({ 1,1 });
        vertexVec.push_back({ 2,1 });
        vertexVec.push_back({ 3,1 });
        vertexVec.push_back({ 2,1 });
        vertexVec.push_back({ 1,1 });
        vertexVec.push_back({ 0,1 });

        // ダッシュのアニメーションをSpriteAnimationに設定します
        spAnim.AddAnimation((int)AnimType::Dush, vertexVec);
        vertexVec.clear(); // 中身を空にする

        // ジャンプの登録
        vertexVec.push_back({ 0,2 });
        vertexVec.push_back({ 1,2 });
        vertexVec.push_back({ 2,2 });

        spAnim.AddAnimation((int)AnimType::Jump, vertexVec);
        vertexVec.clear(); // 中身を空にする

        // 待機 の登録
        vertexVec.push_back({ 0, 0 });
        spAnim.AddAnimation((int)AnimType::Idle, vertexVec);
        vertexVec.clear(); // 中身を空にする
    }

    // デストラクタ
    // Marioが消えた時に呼ばれる処理
    ~Mario() {
    }

    void Load() {
        spAnim.Load("./resource/mario.png");
    }

    void Update(std::vector<std::vector<MapType>>& map) {

        Vector2<float> movable(0.0f, 0.0f); 

        // 左移動
        if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
            movable.x -= pixelSize * 0.1f;
        }

        // 右移動
        if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
            movable.x += pixelSize * 0.1f;
        }

        // スペースキーでジャンプ ジャンプしていないときのみ、ジャンプです
        if (CheckHitKey(KEY_INPUT_SPACE) != 0 && !isJump) {
            velocityY = -10.0f;
            isJump = true;
        }

        // ジャンプ中だったら
        if (isJump) {
            // 重力を適応します。
            velocityY += gravity;
            movable.y += velocityY;
        }

        // 横移動があれば、ダッシュします
        if (movable.x != 0) {
            // 向いてる方向に変更
            isDirLeft = (movable.x < 0);
        }

        // mapを見て、移動先が壁だったときは壁の外に押し出します。
        // 今回判定するべき範囲を考える
        MoveAndCollide(movable, map); 

        CheckGround(map);

        // 最終アニメーションを決定します。
        AnimType newType = AnimType::Idle;

        if (isJump) {
            newType = AnimType::Jump;
        }
        else if (movable.x != 0) {
            newType = AnimType::Dush;
        }
        else {
            newType = AnimType::Idle;
        }

        // アニメーションを設定します。
        spAnim.SetAnimType((int)newType);
    }

    // Lerp 関数の定義（ヘッダ内など共通で使える場所に）
    float Lerp(float a, float b, float t) {
        return a * (1.0f - t) + b * t;
    }

    void MoveAndCollide(
         const Vector2<float>& move
        ,const std::vector<std::vector<MapType>>& map) {

        int width = pixelSize;
        int height = pixelSize;

        // 横方向
        if (move.x != 0) {
            float toX = x + move.x;// 移動先

            // 右移動なら右端を、左端なら左端のタイル列だけ見ます
            int col = -1;
            if (move.x > 0) {
                // 右端
                col = static_cast<int>((toX + width - 1) / pixelSize);
            }
            else {
                // 左端
                col = static_cast<int>(toX / pixelSize);
            }
            // 垂直に重なるタイル行を列挙
            int top = static_cast<int>(y / pixelSize);
            int bottom = static_cast<int>((y + height - 1) / pixelSize);

            // 当たり判定をチェックします。
            bool hit = false;
            for (int row = top; row <= bottom; ++row) {

                // 配列外チェック
                if( row < 0 || row >= static_cast<int>(map.size())
                 || col < 0 || col >= static_cast<int>(map[0].size())) {
                    continue;
                }

                if (map[row][col] == MapType::FLOOR) {
                    hit = true; 
                    break; 
                }
            }

            if (hit) {
                if (move.x > 0) {
                    col--;  // 衝突が起こったセル隣にずらす
                    // x = col * pixelSize - width; // 右壁
                }
                else {
                    col++;  // 衝突が起こったセル隣にずらす
                    // x = (col + 1) * pixelSize;// 左壁
                }
                int desiredX = col * pixelSize; // 右側の場合、セルの左端へ
                x = Lerp(x, desiredX, 0.5f);
            }
            else {
                x = toX;
            }
        }

        if (move.y != 0) {
            float toY = y + move.y; // 移動先

            int row = -1;
            if (move.y > 0) {
                // 下端
                row = static_cast<int>((toY + height - 1) / pixelSize);
            }
            else {
                // 上端
                row = static_cast<int>(toY / pixelSize);
            }

            int left = static_cast<int>(x / pixelSize);
            int right = static_cast<int>((x + width - 1) / pixelSize);

            bool hit = false;
            for (int col = left; col <= right; ++col) {
                // 配列外チェック
                if (row < 0 || row >= static_cast<int>(map.size())
                    || col < 0 || col >= static_cast<int>(map[0].size())) {
                    continue;
                }

                if (map[row][col] == MapType::FLOOR) {
                    hit = true;
                    break;
                }
            }

            if (hit) {

                if (move.y > 0) { // 落下 → 床
                    // desiredY を、スプライトの下端が床に達するように計算
                    int desiredY = row * pixelSize - height;
                    y = Lerp(y, desiredY, 0.5f);
                }
                else { // ジャンプ → 天井
                    row++;
                    int desiredY = row * pixelSize;
                    y = Lerp(y, desiredY, 0.5f);
                }
                velocityY = 0;
            }
            else {
                y = toY;
            }
        }
    }

    // 床チェック
    void CheckGround(const std::vector<std::vector<MapType>>& map) {

        int width = pixelSize;
        int height = pixelSize;
        float epsilon = 2.0f; // 接地許容マージン

        float groundCheckY = y + height + epsilon; // 下端より 2 ピクセル下

        int row = static_cast<int>(groundCheckY / pixelSize);
        int left = static_cast<int>(x / pixelSize);
        int right = static_cast<int>((x + width - 1) / pixelSize);

        for (int col = left; col <= right; ++col) {
            // 配列範囲チェック
            if (row < 0 || row >= static_cast<int>(map.size()) ||
                col < 0 || col >= static_cast<int>(map[0].size()))
            {
                continue;
            }
            if (map[row][col] == MapType::FLOOR) {
                isJump = false;

                y = (row - 1) * pixelSize; // 完全に床に合わせる

                return;
            }
        }
        isJump = true;
        return;
    }


    void Draw() {
        spAnim.Draw(x, y, isDirLeft);
    }
};