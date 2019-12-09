//-----------------------------------------------------------------------------
//
// RGBA16�ϊ�����v���O�C��
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

// �v���g�^�C�v�錾
int ExecMono(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecGrayScale(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecIndexColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);
int ExecFullColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc);

// TODO: �P�̃v���O�C���ɂ͕����̃t�B���^��o�^�ł��܂��B
//       �o�^����t�B���^�̐����`���Ă��������B
#define FILTER_IN_PLUGIN 1

// TODO: �t�B���^�̎�ނ� �p��\�L|���{��\�L �Œ�`���Ă��������B
const char* g_szKinds[FILTER_IN_PLUGIN] = 
{
	"Color|�J���["
};

// TODO: �t�B���^�̖��O�� �p��\�L|���{��\�L �Œ�`���Ă��������B
const char* g_szNames[FILTER_IN_PLUGIN] = 
{
	"RGBA16|RGBA16"
};

// TODO: �T�|�[�g���Ă���C���[�W�^�C�v�A�y�уI�v�V�������`���Ă��������B 
//
//       �C���[�W�S�̂��Q�Ƃ���ɂ� PBF_REFERENCE_IMAGE ���w�肵�Ă��������B�J
//       �����g���C���[�ƃ^�[�Q�b�g���C���[�͈قȂ邱�Ƃ�����܂��B�t�B���^��
//       �^�[�Q�b�g���C���[�ɑ΂��Ă̂ݍs���Ă��������B
DWORD g_dwFormats[FILTER_IN_PLUGIN] =
{
	/*PBF_TYPE_MONO | PBF_TYPE_GRAYSCALE | PBF_TYPE_INDEXCOLOR | */PBF_TYPE_FULLCOLOR /*| PBF_REFERENCE_IMAGE*/
};


// TODO: �C�ӂ̃R�s�[���C�g�������ݒ肵�Ă��������B
const char* g_szCopyright = "@sapphire_al2o3";

HINSTANCE g_hInstance;


///////////////////////////////////////////////////////////////////////////////
// �G���g���|�C���g

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		g_hInstance = hinstDLL;
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// �v���O�C�����擾

DLLExport WORD WINAPI PB_GetPluginInfo(LPSTR buf, int buflen)
{
	// TODO: buf �ɃR�s�[���C�g�������ݒ肵�A�ȉ��̒l��Ԃ��Ă��������B
	strncpy(buf, g_szCopyright, buflen);
	return MAKEWORD(PBPLUGIN_FILTER, PBPLUGIN_FILTER_VERSION);
}


///////////////////////////////////////////////////////////////////////////////
// �t�B���^���擾

DLLExport int WINAPI PBF_FilterCount(void)
{
	// TODO: �v���O�C���Ɋ܂܂��t�B���^�̐���Ԃ��Ă��������B
	return FILTER_IN_PLUGIN;
}


///////////////////////////////////////////////////////////////////////////////
// �t�B���^�̎�ނƖ��O�̎擾

DLLExport void WINAPI PBF_GetName(int nIndex, LPSTR pszKind, int nKindLen, LPSTR pszName, int nNameLen)
{
	// TODO: kind �Ƀt�B���^�̎�ށAname �Ƀt�B���^����ݒ肵�Ă��������B
	strncpy(pszKind, g_szKinds[nIndex], nKindLen);
	strncpy(pszName, g_szNames[nIndex], nNameLen);
}


///////////////////////////////////////////////////////////////////////////////
// �Ή����Ă���C���[�W�̎�ނ��擾

DLLExport DWORD WINAPI PBF_GetSupportedFormat(int nIndex)
{
	// TODO: �Ή����Ă���t�H�[�}�b�g��ݒ肵�Ă��������B
	return g_dwFormats[nIndex];
}


///////////////////////////////////////////////////////////////////////////////
// �t�B���^���s

DLLExport int WINAPI PBF_Execute(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// TODO: �t�B���^�̓��e���L�q���Ă��������B
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
// �t�B���^�ݒ�

DLLExport BOOL WINAPI PBF_Setup(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// TODO: �v���O�C���̐ݒ���s���܂��B
	//
	//       (1) �ݒ��ǂݍ���
	//       (2) if (�ݒ肪�ύX) {
	//       (3)     �ݒ��ۑ�����
	//       (4)     return TRUE;
	//       (5) }
	//       (6) return FALSE;
	//
	//       �ݒ���s��Ȃ��ꍇ�� TRUE ��Ԃ��Ă��������B

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// �G�N�X�|�[�g���̕ϊ�

#ifdef _MSC_VER
#pragma comment(linker, "/EXPORT:PB_GetPluginInfo=_PB_GetPluginInfo@8")
#pragma comment(linker, "/EXPORT:PBF_FilterCount=_PBF_FilterCount@0")
#pragma comment(linker, "/EXPORT:PBF_GetName=_PBF_GetName@20")
#pragma comment(linker, "/EXPORT:PBF_GetSupportedFormat=_PBF_GetSupportedFormat@4")
#pragma comment(linker, "/EXPORT:PBF_Setup=_PBF_Setup@16")
#pragma comment(linker, "/EXPORT:PBF_Execute=_PBF_Execute@16")
#endif



//-----------------------------------------------------------------------------
// �@�\�C���v�������g
//-----------------------------------------------------------------------------

// ���m�N��
int ExecMono(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	return 0;
}

// �O���[�X�P�[��
int ExecGrayScale(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	return 0;
}

// �C���f�b�N�X�J���[
int ExecIndexColor(int nIndex, HWND hWnd, PFilterImage* pFilterImage, PProvidedFunc* pFunc)
{
	// No impl...
	return 0;
}

// �t���J���[
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

