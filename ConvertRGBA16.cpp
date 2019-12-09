//-----------------------------------------------------------------------------
//
// RGBA16変換するプラグイン
//
//-----------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "PbPlugin.h"

#ifdef __cplusplus
#define DLLExport extern "C" __declspec (dllexport)
#else
#define DLLExport __declspec (dllexport)
#endif

// プロトタイプ宣言
int ExecMono(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecGrayScale(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecIndexColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecFullColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);

// TODO: １つのプラグインには複数のフィルタを登録できます。
//       登録するフィルタの数を定義してください。
#define FILTER_IN_PLUGIN 1

// TODO: フィルタの種類を 英語表記|日本語表記 で定義してください。
const char* g_szKinds[FILTER_IN_PLUGIN] = 
{
	"Color|カラー"
};

// TODO: フィルタの名前を 英語表記|日本語表記 で定義してください。
const char* g_szNames[FILTER_IN_PLUGIN] = 
{
	"RGBA16|RGBA16"
};

// TODO: サポートしているイメージタイプ、及びオプションを定義してください。 
//
//       イメージ全体を参照するには PBF_REFERENCE_IMAGE を指定してください。カ
//       レントレイヤーとターゲットレイヤーは異なることがあります。フィルタは
//       ターゲットレイヤーに対してのみ行ってください。
DWORD g_dwFormats[FILTER_IN_PLUGIN] =
{
	/*PBF_TYPE_MONO | PBF_TYPE_GRAYSCALE | PBF_TYPE_INDEXCOLOR | */PBF_TYPE_FULLCOLOR /*| PBF_REFERENCE_IMAGE*/
};


// TODO: 任意のコピーライト文字列を設定してください。
const char* g_szCopyright = "@sapphire_al2o3";

HINSTANCE g_hInstance;


///////////////////////////////////////////////////////////////////////////////
// エントリポイント

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		g_hInstance = hinstDLL;
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// プラグイン情報取得

DLLExport WORD WINAPI PB_GetPluginInfo(LPSTR buf, int buflen)
{
	// TODO: buf にコピーライト文字列を設定し、以下の値を返してください。
	strncpy(buf, g_szCopyright, buflen);
	return MAKEWORD(PBPLUGIN_FILTER, PBPLUGIN_FILTER_VERSION);
}


///////////////////////////////////////////////////////////////////////////////
// フィルタ数取得

DLLExport int WINAPI PBF_FilterCount(void)
{
	// TODO: プラグインに含まれるフィルタの数を返してください。
	return FILTER_IN_PLUGIN;
}


///////////////////////////////////////////////////////////////////////////////
// フィルタの種類と名前の取得

DLLExport void WINAPI PBF_GetName(int nIndex, LPSTR pszKind, int nKindLen, LPSTR pszName, int nNameLen)
{
	// TODO: kind にフィルタの種類、name にフィルタ名を設定してください。
	strncpy(pszKind, g_szKinds[nIndex], nKindLen);
	strncpy(pszName, g_szNames[nIndex], nNameLen);
}


///////////////////////////////////////////////////////////////////////////////
// 対応しているイメージの種類を取得

DLLExport DWORD WINAPI PBF_GetSupportedFormat(int nIndex)
{
	// TODO: 対応しているフォーマットを設定してください。
	return g_dwFormats[nIndex];
}


///////////////////////////////////////////////////////////////////////////////
// フィルタ実行

DLLExport int WINAPI PBF_Execute(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// TODO: フィルタの内容を記述してください。
	pFunc->ProgressStart(0, pFilterImage->nHeight);

	switch (pFilterImage->dwImageType)
	{
	case IT_MONO:
		ExecMono(nIndex, hWnd, pFilterImage, pFunc);
		break;
		
	case IT_GRAYSCALE:
		ExecGrayScale(nIndex, hWnd, pFilterImage, pFunc);
		break;
		
	case IT_INDEXCOLOR:
		ExecIndexColor(nIndex, hWnd, pFilterImage, pFunc);
		break;
		
	case IT_FULLCOLOR:
		ExecFullColor(nIndex, hWnd, pFilterImage, pFunc);
		break;
	}
	
	pFunc->ProgressEnd();

	return PB_ERR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// フィルタ設定

DLLExport BOOL WINAPI PBF_Setup(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// TODO: プラグインの設定を行います。
	//
	//       (1) 設定を読み込む
	//       (2) if (設定が変更) {
	//       (3)     設定を保存する
	//       (4)     return TRUE;
	//       (5) }
	//       (6) return FALSE;
	//
	//       設定を行わない場合は TRUE を返してください。

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// エクスポート名の変換

#ifdef _MSC_VER
#pragma comment(linker, "/EXPORT:PB_GetPluginInfo=_PB_GetPluginInfo@8")
#pragma comment(linker, "/EXPORT:PBF_FilterCount=_PBF_FilterCount@0")
#pragma comment(linker, "/EXPORT:PBF_GetName=_PBF_GetName@20")
#pragma comment(linker, "/EXPORT:PBF_GetSupportedFormat=_PBF_GetSupportedFormat@4")
#pragma comment(linker, "/EXPORT:PBF_Setup=_PBF_Setup@16")
#pragma comment(linker, "/EXPORT:PBF_Execute=_PBF_Execute@16")
#endif



//-----------------------------------------------------------------------------
// 機能インプリメント
//-----------------------------------------------------------------------------

// モノクロ
int ExecMono(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	return 0;
}

// グレースケール
int ExecGrayScale(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	return 0;
}

// インデックスカラー
int ExecIndexColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// No impl...
	return 0;
}

// フルカラー
int ExecFullColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	for (int y = 0; y < pFilterImage->nHeight; y++) 
	{
		for (int x = 0; x < pFilterImage->nWidth; x++) 
		{
			Pixel32 pixel;
			pixel.color = pFilterImage->pSrc[x + y*pFilterImage->nWidth];
			pixel.item.r = (int)(pixel.item.r / 17) * 17;
			pixel.item.g = (int)(pixel.item.g / 17) * 17;
			pixel.item.b = (int)(pixel.item.b / 17) * 17;
			pixel.item.a = (int)(pixel.item.a / 17) * 17;

			pFilterImage->pDst[x + y*pFilterImage->nWidth] = pixel.color;
		}

		pFunc->ProgressSetPos(y);
	}

	return 0;
}

