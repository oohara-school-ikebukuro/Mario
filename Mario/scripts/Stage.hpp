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

    // �}�b�v��񂪋l�܂����A2�����z��
    std::vector<std::vector<MapType>> map;

    int groundTex;
    int marioTex;

    // �R���X�g���N�^
    Stage(int pixelSize) : pixelSize(pixelSize), groundTex(-1),marioTex(-1){
    }

    // csv�ǂݍ��ݏ���
    std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
        std::vector<std::vector<std::string>> records;
        std::ifstream file(filename);
        std::string line;

        if (!file) {
            std::cerr << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
            return records;
        }

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::vector<std::string> row;
            std::string value;

            // �s�̂��ׂẴJ���}��؂�f�[�^���擾
            while (std::getline(ss, value, ',')) {
                row.push_back(value);
            }

            records.push_back(row);
        }
        return records;
    }

    // �w�肵���A�t�@�C���̃e�L�X�g��ǂݍ��݂܂�
    void Load(const std::string& fileName) {

        // �摜�̓ǂݍ���
        groundTex = LoadGraph("./resource/ground.png");
        marioTex = LoadGraph("./resource/mario_idle.png"); 

        // �X�e�[�W�����A�e�L�X�g�t�@�C�������������
        std::vector<std::vector<std::string>> data = readCSV(fileName);

        for (int y = 0; y < data.size(); y++) {

            map.push_back({});

            //                      �� ����Y��Ȃ��ŁI
            for (int x = 0; x < data[y].size(); x++) {

                // string �� ���� �� enum
                MapType type = (MapType)std::stoi(data[y][x]);

                // enum �� map���Ɋi�[
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
