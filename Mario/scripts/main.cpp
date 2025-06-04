#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	WaitKey();				// キー入力待ち

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

// ブロック崩しの、scripts/helperをコピー
// Mario/scripts の中に、helperを貼り付け
// ソリューションエクスプローラーで「既存の項目を追加」
// helperの中の「DxLibHelper」を選択して追加

// ※ main.cppが、scriptsの下に無いよ！！
// ① エクスプローラー上で、main.cppをscriptsの下に移動しましょう
// ② ソリューションエクスプローラーのmain.cppを一度削除しましょう
// ③ ソリューションエクスプローラーで、既存の項目から、main.cppを追加
