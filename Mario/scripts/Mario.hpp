#pragma once

#include <DxLib.h>

class Mario {

public:

    int pixelSize;
    float x, y;

    int marioTex;

    // �R���X�g���N�^
    Mario(int pixelSize)
        : pixelSize(pixelSize), x(0), y(0), marioTex(-1){
    }

    // �f�X�g���N�^
    // Mario�����������ɌĂ΂�鏈��
    ~Mario() {
        DeleteGraph(marioTex);
    }

    void Load() {
        marioTex = LoadGraph("./resource/mario.png");
    }

    void Update() {

        // ��
        if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
            x -= pixelSize * 0.25f;
        }

        if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
            x += pixelSize * 0.25f;
        }
    }

    int frame = 0;
    int textureX = 0;
    void Draw() {

        // 5�t���[���o������A�摜�ς��܂��B
        frame++;
        if (frame > 5) {
            textureX++;
            frame = 0;

            // �摜�͈̔͊O�ɍs���Ƃ܂����̂�
            // ��ԍ��ɖ߂��܂��傤
            if (textureX >= 4) {
                textureX = 0;
            }
        }

        // 
        DrawRectGraph(
              x          // x���W
            , y          // y���W
            , textureX * 32     // �\������摜�ʒu�̍��㒸�_���Wx
            , 0 * 32     // �\������摜�ʒu�̍��㒸�_���Wy
            , 32         // �摜�T�C�Yx
            , 32         // �摜�T�C�Yy
            , marioTex   // �g���摜�̃n���h��(LoadGraph�����z)
            , TRUE       // �������g�����H
            , FALSE      // �摜�𔽓]�����邩�H
        );

        // �����Ȃ��Ă悢�ł���
        DrawGraph( x + 7 * 32, y , marioTex, TRUE);
    }
};