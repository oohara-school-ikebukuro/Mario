#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <DxLib.h>

enum class MapType {

      NONE  = 0
    , FLOOR = 1
    , WALL  = 2
    , MARIO = 3
};

class Stage {

public:

    int pixelSize;

    // マップ情報が詰まった、2次元配列
    std::vector<std::vector<MapType>> map;

    int groundTex;
    int marioTex;

    // コンストラクタ
    Stage(int pixelSize) : pixelSize(pixelSize), groundTex(-1),marioTex(-1){
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

        // 画像の読み込み
        groundTex = LoadGraph("./resource/ground.png");
        marioTex = LoadGraph("./resource/mario_idle.png"); 

        // ステージ情報を、テキストファイルから引っ張る
        std::vector<std::vector<std::string>> data = readCSV(fileName);

        for (int y = 0; y < data.size(); y++) {

            map.push_back({});

            //                      ↓ これ忘れないで！
            for (int x = 0; x < data[y].size(); x++) {

                // string → 数字 → enum
                MapType type = (MapType)std::stoi(data[y][x]);

                // enum を map情報に格納
                map[y].push_back(type);

            }
        }
    }

    void Draw()
    {
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[y].size(); x++) {

                switch (map[y][x]) {
                    case MapType::FLOOR:
                        DrawGraph(x * pixelSize, y * pixelSize, groundTex, TRUE);
                        break;
                    case MapType::WALL:
                        DrawGraph(x * pixelSize, y * pixelSize, groundTex, TRUE);
                        break;
                    case MapType::MARIO:
                        DrawGraph(x * pixelSize, y * pixelSize, marioTex, TRUE);
                        break;
                }
            }
        }
    }

    void End() {
        DeleteGraph(groundTex);
        DeleteGraph(marioTex);
    }
};
