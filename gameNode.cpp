#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
	crtXsize = 34;	// 64 * 16 = 1024
	crtYsize = 16;	// 64 * 16 = 1024
}


gameNode::~gameNode()
{
}


HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		CAMERA->init();
	}

	return S_OK;
}

void gameNode::setMap(int _plusX, int _plusY)
{
	crtXsize += _plusX;
	crtYsize += _plusY;
	_backBuffer = IMAGEMANAGER->findImage("backBuffer");
	_backBuffer->init(TILESIZE * crtXsize, TILESIZE * crtYsize);
}

void gameNode::release()
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		INIDATA->releaseSingleton();
		CAMERA->release();
		CAMERA->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	SOUNDMANAGER->update();

}

void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));	
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{

				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;

		case WM_MOUSEWHEEL:
		{
			int zDelta = (INT)wParam;

			if (zDelta > 0)
			{
				scrollWheel -= 32;
				if (scrollWheel <= 0) scrollWheel = 0;
			}
			if (zDelta < 0)
			{
				scrollWheel += 32;
				if (scrollWheel >= 1504) scrollWheel = 1504;
			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
