#pragma once

#include "./SpriteAnimation.hpp" // スプライトアニメーションをしたいので

#include "MapType.hpp"

#include <DxLib.h> // DXライブラリを使いたいので
#include <vector>  // std::vectorを使いたいので

// ノコノコです
class Nokonoko {

    enum class AnimTexType {
          Idle
        , Dash1, Dash2
        , Jump
    };

    enum class AnimType {
          Idle
        , Dash
        , Jump
    };

public:

    int pixelSize;   // 1マスのサイズ
    float x, y;      // 座標
    bool isDirLeft;  // 左向いてますか？

    bool isWallHit = false;// 壁に当たっているか

    SpriteAnimation spAnim;

    // コンストラクタ
    Nokonoko(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0)
        , spAnim(pixelSize), isDirLeft(true) {
    }

    // デストラクタ
    // Marioが消えた時に呼ばれる処理
    ~Nokonoko() {
    }

    void Load() {

        // 画像切り出し設定
        std::map<int, Rect> textures;

        // 待機画像の切り出し
        textures.insert({ (int)AnimTexType::Idle,{ 210 , 0 , 16 , 24 } });

        // ダッシュ画像の切り出し
        textures.insert({ (int)AnimTexType::Dash1,{ 210 , 0 , 16 , 24 } });
        textures.insert({ (int)AnimTexType::Dash2,{ 240 , 0 , 16 , 24 } });

        // ジャンプ画像の切り出し
        textures.insert({ (int)AnimTexType::Jump,{210,0,16,24} });

        // 画像のロード
        spAnim.Load("./resource/enemies.png", textures);

        // アニメーションを設定して追加します。
        std::vector<int> animVec;

        // 待機アニメーション設定
        animVec.push_back((int)AnimTexType::Idle);
        spAnim.AddAnimation((int)AnimType::Idle, animVec);
        animVec.clear();

        // ダッシュアニメーション設定
        animVec.push_back((int)AnimTexType::Dash1);
        animVec.push_back((int)AnimTexType::Dash2);
        spAnim.AddAnimation((int)AnimType::Dash, animVec);
        animVec.clear();

        // ジャンプアニメーション
        animVec.push_back((int)AnimTexType::Jump);
        spAnim.AddAnimation((int)AnimType::Jump, animVec);
        animVec.clear();
    }

    float velocityY = 0;  // y軸の力
    float velocityX = 0;  // x軸の力
    float gravity = 0.3f; // 重力
    bool isJump = false;  // ジャンプしてますか？
    bool isDirLeft = true; // 左を向いていますか？

    void Update(std::vector<std::vector<MapType>>& map) {

        Vector2<float> movable(0.5f, 0.0f);

        // ノコノコが向いている方向に移動させます。
        if (isDirLeft) {
            movable.x *= -1;
        }

        // ジャンプ中だったら
        if (isJump) {

            // 重力を適応します。
            velocityY += gravity;
            movable.y += velocityY;
        }

        // 移動と、当たり判定の二つを行います。
        MoveAndCollide(movable, map);

        // 床チェックします。
        CheckGround(map);

        // 最終アニメーションを決定します。
        AnimType newType = AnimType::Idle;

        if (isJump) {
            newType = AnimType::Jump;
        }
        else if (movable.x != 0) {
            newType = AnimType::Dash;
        }
        else {
            newType = AnimType::Idle;
        }

        // アニメーションを設定します。
        spAnim.SetAnimType((int)newType);
    }

    // 移動しながら、当たり判定チェック
    void MoveAndCollide(
        const Vector2<float>& movable
        , std::vector<std::vector<MapType>>& map) {

        int width = pixelSize;  // キャラの横幅
        int height = pixelSize; // キャラの縦幅


        // 横方向
        if (movable.x != 0) 
        {
            // 今回の移動先
            float toX = x + movable.x + velocityX;

            // 今回判定するべき行を、割り出します。
            int col = -1;

            // 右移動
            if (movable.x > 0) {
                col = (int)((toX + width - 1) / pixelSize);
            }
            else { // 左移動
                col = (int)(toX / pixelSize);
            }

            // 今回判定するべき列を割り出す
            int top = (int)(y / pixelSize);
            int bottom = (int)((y + height - 1) / pixelSize);

            // 当たり判定チェックしましょう
            bool isHit = false;
            for (int row = top; row <= bottom; ++row) {

                // 配列範囲チェック
                if (row < 0 || row >= map.size()
                    || col < 0 || col >= map[0].size()) {
                    continue;
                }
                // 何かに当たった？
                if (map[row][col] == MapType::FLOOR
                    || map[row][col] == MapType::WALL) {
                    isHit = true;
                    break; // 当たったらもう用がないので、breakして抜ける
                }
                // コインに当たった
                if (map[row][col] == MapType::COIN) {
                    map[row][col] = MapType::NONE;
                }
            }
            // 当たっていたら・・
            if (isHit) {
                isWallHit = true;

                if (movable.x > 0) {
                    col--; // 右から左に戻す必要があるので、-1
                    isDirLeft = true;
                }
                else {
                    col++; // 左から右に戻す必要があるので、+1
                    isDirLeft = false;
                }
                // 移動を完遂する
                int desiredX = col * pixelSize;
                x = desiredX;
            }
            else {
                isWallHit = false;
                x = toX;
            }
        }
        else {
            isWallHit = false;
        }

        if (movable.y != 0) {
            // 縦のチェック
            float toY = y + movable.y;

            // 今回判定するべき列を割り出す
            int row = -1;
            if (movable.y > 0) {
                row = (int)((toY + height - 1) / pixelSize);
            }
            else { // 左移動
                row = (int)(toY / pixelSize);
            }

            // 今回判定するべき行を割り出す
            int left = (int)(x / pixelSize);
            int right = (int)((x + width - 1) / pixelSize);

            // 当たり判定チェックしましょう
            bool isHit = false;
            for (int col = left; col <= right; ++col) {

                // 配列範囲チェック
                if (row < 0 || row >= map.size()
                    || col < 0 || col >= map[0].size()) {
                    continue;
                }
                // 何かに当たった？
                if (map[row][col] == MapType::FLOOR
                    || map[row][col] == MapType::WALL) {
                    isHit = true;
                    break; // 当たったらもう用がないので、breakして抜ける
                }

                if (map[row][col] == MapType::COIN) {
                    map[row][col] = MapType::NONE;
                }
            }

            // 当たっていたら・・
            if (isHit) {
                if (movable.y > 0) {
                    row--; // 右から左に戻す必要があるので、-1
                }
                else {
                    row++; // 左から右に戻す必要があるので、+1
                }
                // 移動を完遂する
                int desiredY = row * pixelSize;
                y = desiredY;
                velocityY = 0;
            }
            else {
                y = toY;
            }
        }
    }

    // 床チェック処理
    void CheckGround(const std::vector<std::vector<MapType>>& map) {

        int width = pixelSize;  // キャラの横幅
        int height = pixelSize; // キャラの縦幅
        float epsilon = 2.0f;   // 接地を許容マージン

        // キャラの足元座標
        float groundCheckY = y + height + epsilon;

        int row = (int)(groundCheckY / pixelSize);      // 今回調べるべき列
        int left = (int)(x / pixelSize);                // 今回調べるべき xの最低値 
        int right = (int)((x + width - 1) / pixelSize); // 今回調べるべき xの最高値

        for (int col = left; col <= right; ++col) {

            // 配列範囲チェック
            if (row < 0 || row >= map.size()
                || col < 0 || col >= map[0].size()) {
                continue;
            }

            // 床だったら、床の上に補正してジャンプを終わらせます
            // row : y軸 / col : x軸
            if (map[row][col] == MapType::FLOOR
                || map[row][col] == MapType::WALL) {
                isJump = false; // ジャンプを終わらせます
                y = (row - 1) * pixelSize; // 床の上に補正します。
                velocityY = 0;
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
