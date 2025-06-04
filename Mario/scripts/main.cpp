
#include "./helper/DxLibHelper.h"
#include "./GameManager.hpp"

#include <DxLib.h>

// �R���\�[���A�v���P�[�V�����̎��́Aint main ����n�܂�
/*
int main()
{
}
*/

// �E�B���h�E�Y�A�v���P�[�V�����́Aint WINAPI WinMain ����n�܂�
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameManager gm;

	// DX���C�u�����́A�������}�������B
	DxLibHelper dxHelper(gm.fps);

	// DX���C�u�������J�n���܂��B
	if (dxHelper.Init({ ScreenType::WINDOWED, gm.winX ,gm.winY }) != 0) {
		return -1;
	}

	// ���C�����[�v -------------------------------------------------
	gm.Init();

	while (gm.isRun) {

		gm.Update();

		gm.Draw();

		// �`��X�V + FPS���������Ă����ǂ��z
		dxHelper.RefreshScreen();
	}

	// --------------------------------------------------------------

	gm.End();


	// DX���C�u�������I���܂��B
	dxHelper.Cleanup();

	return 0;
}