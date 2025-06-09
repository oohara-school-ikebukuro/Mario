#pragma once

#include "./SpriteAnimation.hpp" // スプライトアニメーションをしたいので
#include <DxLib.h> // DXライブラリを使いたいので
#include <vector>  // std::vectorを使いたいので

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

    SpriteAnimation spAnim;

    // コンストラクタ
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0), spAnim(pixelSize),isDirLeft(true){

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

    float velocityY = 0;  // y軸の力
    float gravity = 0.3f; // 重力
    bool isJump = false;  // ジャンプしてますか？

    void Update(const std::vector<std::vector<MapType>>& map) {

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

        // 移動値を反映します。
        x += movable.x;
        y += movable.y;

        // 床チェックします。
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
            if (map[row][col] == MapType::FLOOR) {
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