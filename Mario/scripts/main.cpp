#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�

	WaitKey();				// �L�[���͑҂�

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

// �u���b�N�����́Ascripts/helper���R�s�[
// Mario/scripts �̒��ɁAhelper��\��t��
// �\�����[�V�����G�N�X�v���[���[�Łu�����̍��ڂ�ǉ��v
// helper�̒��́uDxLibHelper�v��I�����Ēǉ�

// �� main.cpp���Ascripts�̉��ɖ�����I�I
// �@ �G�N�X�v���[���[��ŁAmain.cpp��scripts�̉��Ɉړ����܂��傤
// �A �\�����[�V�����G�N�X�v���[���[��main.cpp����x�폜���܂��傤
// �B �\�����[�V�����G�N�X�v���[���[�ŁA�����̍��ڂ���Amain.cpp��ǉ�
