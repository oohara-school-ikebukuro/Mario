#pragma once

#include "MapType.hpp"
#include "Mario.hpp"
#include "Nokonoko.hpp"
#include "Sprite.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <DxLib.h>

class Stage {

public:

    int pixelSize;

    // マップ情報が詰まった、2次元配列
    std::vector<std::vector<MapType>> map;

    Sprite ground;
    Sprite items;

    Mario mario;

    std::vector<Nokonoko> nokonokos;

    // コンストラクタ
    Stage(int pixelSize) : pixelSize(pixelSize), mario(pixelSize) {
    }

    // csv読み込み処理
    std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
        std::vector<std::vector<std::string>> records;
        std::ifstream file(filename);
        std::string line;

        if (!file) {
            std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
            return records;
        }

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::vector<std::string> row;
            std::string value;

            // 行のすべてのカンマ区切りデータを取得
            while (std::getline(ss, value, ',')) {
                row.push_back(value);
            }

            records.push_back(row);
        }
        return records;
    }

    // 指定した、ファイルのテキストを読み込みます
    void Load(const std::string& fileName) {

        // 床画像の読み込み
        ground.Load("./resource/blocks.png");

        // 床画像の切り出し
        ground.SetTexture(0, { 3 * 16 , 3 * 16 , 16 , 16 });
        ground.SetTexture(1, { 5 * 16 , 3 * 16 , 16 , 16 });
        ground.SetTexture(2, { 3 * 16 , 1 * 16 , 16 , 16 });
        
        // アイテム画像の読み込み
        items.Load("./resource/items.png");

        // コイン画像の切り出し
        items.SetTexture(0, { 124,94,16,16 });

        // ステージ情報を、テキストファイルから引っ張る
        std::vector<std::vector<std::string>> data = readCSV(fileName);

        // ステージ情報を、enumでmapに入れ込む
        map.clear();
        nokonokos.clear(); // ノコノコのデータを初期化する。

        for (int y = 0; y < data.size(); y++) {

            map.push_back({});

            //                      ↓ これ忘れないで！
            for (int x = 0; x < data[y].size(); x++) {

                // string → 数字 → enum
                MapType type = (MapType)std::stoi(data[y][x]);

                // enum を map情報に格納
                map[y].push_back(type);

                // マリオの初期位置を設定
                if (type == MapType::MARIO) {
                    mario.x = x * pixelSize;
                    mario.y = y * pixelSize;
                }
                else if (type == MapType::NOKONOKO) {

                    // ノコノコを作ります。
                    Nokonoko nokonoko(pixelSize);

                    // ノコノコの座標を設定
                    nokonoko.x = x * pixelSize;
                    nokonoko.y = y * pixelSize;

                    // データのロード処理
                    nokonoko.Load();

                    // ノコノコを追加
                    nokonokos.push_back(nokonoko);
                }
            }
        }

        // マリオをロード
        mario.Load();
    }

    void Update(){
        mario.Update(map);

        //          ↓ ノコノコ
        for (auto& nokonoko : nokonokos) {

            nokonoko.Update(map);
            
            mario.HitEnemy(nokonoko);
        }
    }

    void Draw()
    {
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[y].size(); x++) {

                int posX = x * pixelSize;
                int posY = y * pixelSize;

                Rect rect({ posX,posY,pixelSize,pixelSize });

                switch (map[y][x]) {
                    case MapType::FLOOR:

                        ground.Draw(rect, 2);

                        break;
                    case MapType::WALL:

                        ground.Draw(rect, 1);

                        break;
                    case MapType::MARIO:
                        break;
                    case MapType::COIN:
                        
                        items.Draw(rect, 0);

                    break;
                }
            }
        }

        // マリオを描画
        mario.Draw();

        //          ↓ ノコノコ
        for (auto& nokonoko : nokonokos) {
            nokonoko.Draw();
        }
    }

    void End() {
    }
};
