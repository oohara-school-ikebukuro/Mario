
#include "./helper/DxLibHelper.h"
#include "./GameManager.hpp"

#include <DxLib.h>

// コンソールアプリケーションの時は、int main から始まる
/*
int main()
{
}
*/

// ウィンドウズアプリケーションは、int WINAPI WinMain から始まる
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameManager gm;

	// DXライブラリの、お助けマンを作る。
	DxLibHelper dxHelper(gm.fps);

	// DXライブラリを開始します。
	if (dxHelper.Init({ ScreenType::WINDOWED, gm.winX ,gm.winY }) != 0) {
		return -1;
	}

	// メインループ -------------------------------------------------

	// エネミーロード
	int textureHandle = LoadGraph("./resource/enemies.png");

	gm.Init();

	while (gm.isRun) {

		gm.Update();

		gm.Draw();

		DrawRectExtendGraph(
		       0 , 0  // 表示する左上頂点
			, 32 , 32 // 表示する右下頂点
			,  0 , 0  // 表示したい画像の左上頂点
			, 28 , 28 // 表示する右下頂点
			, textureHandle, true);

		// 描画更新 + FPS調整をしてくれる良い奴
		dxHelper.RefreshScreen();
	}

	// --------------------------------------------------------------


	// DXライブラリを終わります。
	dxHelper.Cleanup();

	return 0;
}