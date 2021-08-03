#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	crtCamXpos = crtCamYpos = 0.0f;

	selectTileX = selectTileY = crtButtonKind = 0;
	
	tileSetMouseOn = false;

	imageInit();

	layerButton1 = RectMake(520, 325, 152, 44);
	layerButton2 = RectMake(680, 325, 152, 44);
	notPassTileButton = RectMake(840, 325, 152, 44);
	returnPassTileButton = RectMake(520, 379, 152, 44);
	saveButton = RectMake(680, 379, 102, 44);
	loadButton = RectMake(790, 379, 102, 44);
	zOrderButton = RectMake(900, 379, 102, 44);

	for (int y = 0; y < crtYsize; y++)
	{
		vector<tileInfo> muonVtTile;

		for (int x = 0; x < crtXsize - 18; x++)
		{
			tileInfo muonTile;

			muonTile.tilePos = { x,y };
			muonTile.layerPos1 = { 0,0 };
			muonTile.layerPos2 = { 0,0 };
			muonTile.geography = 0;
			muonTile.rectYes = false;

			muonVtTile.push_back(muonTile);

			if (x == (crtXsize - 18) - 1) tile.push_back(muonVtTile);
		}
	}

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	

}

void playGround::update()
{
	gameNode::update();

	512 > _ptMouse.x ? tileSetMouseOn = false : tileSetMouseOn = true;

	mouseGridX = (int)(((CAMERA->getcamX() * (!tileSetMouseOn)) + _ptMouse.x - (512 * tileSetMouseOn)) / TILESIZE);
	mouseGridY = (int)(((CAMERA->getcamY() * (!tileSetMouseOn)) + _ptMouse.y + scrollWheel * (tileSetMouseOn)) / TILESIZE);

	keyDownGroup();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, _backBuffer->getWidth(), _backBuffer->getHeight(), WHITENESS);
	//================ 위에 건들지 마라 ==============================

	/*char str[128];
	sprintf_s(str, "현재X노드 : %d", mouseGridX);
	TextOut(getMemDC(), CAMERA->getcamX() + 20, CAMERA->getcamY() + 20, str, strlen(str));
	sprintf_s(str, "현재Y노드 : %d", mouseGridY);
	TextOut(getMemDC(), CAMERA->getcamX() + 20, CAMERA->getcamY() + 40, str, strlen(str));
	
	for (int y = 0; y < tile.size(); y++)
	{
		for (int x = 0; x < tile[y].size(); x++)
		{
			sprintf_s(str, "%d", tile[y][x].geography);
			TextOut(getMemDC(), (x * 32), (y * 32), str, strlen(str));
			//sprintf_s(str, "%d", tile[y][x].dcYpos);
			//TextOut(getMemDC(), (x * 32), (y * 32) + 20, str, strlen(str));
		}
	}*/

	for (int y = 0; y < tile.size(); y++)
	{
		for (int x = 0; x < tile[y].size(); x++)
		{
			IMAGEMANAGER->findImage("밀레니어")->render(getMemDC(), tile[y][x].tilePos.x * TILESIZE, tile[y][x].tilePos.y * TILESIZE, tile[y][x].layerPos1.x * TILESIZE, tile[y][x].layerPos1.y * TILESIZE, TILESIZE, TILESIZE);
			IMAGEMANAGER->findImage("밀레니어")->render(getMemDC(), tile[y][x].tilePos.x * TILESIZE, tile[y][x].tilePos.y * TILESIZE, tile[y][x].layerPos2.x * TILESIZE, tile[y][x].layerPos2.y * TILESIZE, TILESIZE, TILESIZE);
			if (tile[y][x].rectYes)
				IMAGEMANAGER->findImage("렉트")->render(getMemDC(), tile[y][x].tilePos.x * TILESIZE, tile[y][x].tilePos.y * TILESIZE);
			if (tile[y][x].geography == 4)
				IMAGEMANAGER->findImage("Z오덜")->render(getMemDC(), tile[y][x].tilePos.x * TILESIZE, tile[y][x].tilePos.y * TILESIZE);
		}
	}
	
	for (int x = 0; x < crtXsize; x++)
	{
		LineMake(getMemDC(), x * TILESIZE, 0, x * TILESIZE, crtYsize * TILESIZE);
	}
	for (int y = 0; y < crtYsize; y++)
	{
		LineMake(getMemDC(), 0, y * TILESIZE, crtXsize * TILESIZE, y * TILESIZE);
	}

	RectangleMake(getMemDC(), CAMERA->getcamX() + 512, CAMERA->getcamY() + 0, 576, 512);

	IMAGEMANAGER->findImage("밀레니어")->render(getMemDC(), CAMERA->getcamX() + (WINSIZEX - 576), CAMERA->getcamY(), 0, scrollWheel, 576, 320);

	IMAGEMANAGER->findImage("레이어1")->render(getMemDC(), CAMERA->getcamX() + 520, CAMERA->getcamY() + 325);
	IMAGEMANAGER->findImage("레이어2")->render(getMemDC(), CAMERA->getcamX() + 680, CAMERA->getcamY() + 325);
	IMAGEMANAGER->findImage("통행불가")->render(getMemDC(), CAMERA->getcamX() + 840, CAMERA->getcamY() + 325);
	IMAGEMANAGER->findImage("통행가능")->render(getMemDC(), CAMERA->getcamX() + 520, CAMERA->getcamY() + 379);
	IMAGEMANAGER->findImage("저장하기")->render(getMemDC(), CAMERA->getcamX() + 680, CAMERA->getcamY() + 379);
	IMAGEMANAGER->findImage("로드")->render(getMemDC(), CAMERA->getcamX() + 790, CAMERA->getcamY() + 379);
	IMAGEMANAGER->findImage("Z오더")->render(getMemDC(), CAMERA->getcamX() + 900, CAMERA->getcamY() + 379);

	if (tileSetMouseOn)
	{
		if (320 > _ptMouse.y)
		{
			IMAGEMANAGER->findImage("선택1")->render(getMemDC(), TILESIZE * (mouseGridX + 16 + (CAMERA->getcamX() / TILESIZE)), TILESIZE * (mouseGridY - ((scrollWheel - CAMERA->getcamY()) / TILESIZE)));
		}
	}
	else
	{
		IMAGEMANAGER->findImage("선택2")->render(getMemDC(), TILESIZE * mouseGridX, TILESIZE * mouseGridY);
	}


	//TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC(), 0, 0, CAMERA->getcamX(), CAMERA->getcamY(), WINSIZEX, WINSIZEY);
}

void playGround::addXtile()
{
	for (int y = 0; y < crtYsize; y++)
	{
		tileInfo muonTile;

		muonTile.tilePos = { crtXsize - 19, y };
		muonTile.layerPos1 = { 0,0 };
		muonTile.layerPos2 = { 0,0 };
		muonTile.geography = 0;
		muonTile.rectYes = false;

		tile[y].push_back(muonTile);
	}
}

void playGround::removeXtile()
{
	for (int y = 0; y < crtYsize; y++)
	{
		tile[y].pop_back();
	}
}

void playGround::addYtile()
{
	vector<tileInfo> muonVtTile;

	for (int x = 0; x < crtXsize - 18; x++)
	{
		tileInfo muonTile;

		muonTile.tilePos = { x, crtYsize -1 };
		muonTile.layerPos1 = { 0,0 };
		muonTile.layerPos2 = { 0,0 };
		muonTile.geography = 0;
		muonTile.rectYes = false;

		muonVtTile.push_back(muonTile);

		if (x == (crtXsize - 18) - 1) tile.push_back(muonVtTile);
	}
}

void playGround::removeYtile()
{
	tile.pop_back();
}

void playGround::keyDownGroup()
{
	if (KEYMANAGER->isStayKeyDown('A')) CAMERA->setcamPos(-10, 0);
	if (KEYMANAGER->isStayKeyDown('D')) CAMERA->setcamPos( 10, 0);
	if (KEYMANAGER->isStayKeyDown('W')) CAMERA->setcamPos( 0,-10);
	if (KEYMANAGER->isStayKeyDown('S')) CAMERA->setcamPos( 0, 10);

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		setMap(1, 0);
		addXtile();
	}
	if (KEYMANAGER->isOnceKeyDown('2')) 
	{ 
		setMap(-1, 0);
		removeXtile();
	}
	if (KEYMANAGER->isOnceKeyDown('3')) 
	{ 
		setMap(0, 1); 
		addYtile();
	}
	if (KEYMANAGER->isOnceKeyDown('4')) 
	{ 
		setMap(0, -1);
		removeYtile();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!tileSetMouseOn && selectTileX != -1)
		{
			if (crtButtonKind == 0)
			{
				tile[mouseGridY][mouseGridX].layerPos1 = { selectTileX , selectTileY };
			}
			else if (crtButtonKind == 1)
			{
				tile[mouseGridY][mouseGridX].layerPos2 = { selectTileX , selectTileY };
			}
			else if (crtButtonKind == 2)
			{
				tile[mouseGridY][mouseGridX].rect = RectMake(
					tile[mouseGridY][mouseGridX].tilePos.x,
					tile[mouseGridY][mouseGridX].tilePos.y,
					TILESIZE * 2,
					TILESIZE * 2
				);
				tile[mouseGridY][mouseGridX].rectYes = true;
			}
			else if (crtButtonKind == 3)
			{
				tile[mouseGridY][mouseGridX].rectYes = false;
			}

			tile[mouseGridY][mouseGridX].geography = crtButtonKind;
		}
		else if(tileSetMouseOn && 512 < _ptMouse.x && 320 > _ptMouse.y)
		{
			selectTileX = mouseGridX;
			selectTileY = mouseGridY;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&layerButton1, _ptMouse))
		{
			crtButtonKind = 0;
		}
		else if (PtInRect(&layerButton2, _ptMouse))
		{
			crtButtonKind = 1;
		}
		else if (PtInRect(&notPassTileButton, _ptMouse))
		{
			crtButtonKind = 2;
		}
		else if (PtInRect(&returnPassTileButton, _ptMouse))
		{
			crtButtonKind = 3;
		}
		else if (PtInRect(&saveButton, _ptMouse))
		{
			save();
		}
		else if (PtInRect(&loadButton, _ptMouse))
		{
			load();
		}
		else if (PtInRect(&zOrderButton, _ptMouse))
		{
			crtButtonKind = 4;
		}
	}
}

void playGround::imageInit()
{
	IMAGEMANAGER->addImage("밀레니어", "maptoolIMG/사이즈바꾸기전/밀레니얼타일.bmp", 576, 1824, true, RGB(179, 38, 189));
	IMAGEMANAGER->addImage("선택1", "maptoolIMG/선택.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("선택2", "maptoolIMG/선택2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("렉트", "maptoolIMG/렉트.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("레이어1", "maptoolIMG/레이어1.bmp", 152, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("레이어2", "maptoolIMG/레이어2.bmp", 152, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("통행불가", "maptoolIMG/통행불가.bmp", 152, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("통행가능", "maptoolIMG/통행가능.bmp", 152, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("저장하기", "maptoolIMG/저장버튼.bmp", 102, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드", "maptoolIMG/로드.bmp", 102, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Z오더", "maptoolIMG/z오더.bmp", 102, 44, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Z오덜", "maptoolIMG/Z오덜.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("프롭", "maptoolIMG/프롭.bmp", 80, 134, 3, 4, true, RGB(0, 0, 0));
}

void playGround::save()
{
	HANDLE file;
	DWORD write;

	int idx = ((crtXsize - 18) * crtYsize)+1;	
	tileInfo* _tiles = new tileInfo[idx];

	for (int y = 0; y < crtYsize; y++)
	{
		for (int x = 0; x < crtXsize - 18; x++)
		{
			_tiles[x + (y * (crtXsize - 18))].geography = tile[y][x].geography;
			_tiles[x + (y * (crtXsize - 18))].layerPos1 = { tile[y][x].layerPos1.x , tile[y][x].layerPos1.y };
			_tiles[x + (y * (crtXsize - 18))].layerPos2 = { tile[y][x].layerPos2.x , tile[y][x].layerPos2.y };
			_tiles[x + (y * (crtXsize - 18))].rect = tile[y][x].rect;
			_tiles[x + (y * (crtXsize - 18))].rectYes = tile[y][x].rectYes;
			_tiles[x + (y * (crtXsize - 18))].tilePos = { tile[y][x].tilePos.x , tile[y][x].tilePos.y };
		}
	}

	file = CreateFile("saveMap1.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tileInfo) * (crtXsize - 18) * crtYsize, &write, NULL);

	SAFE_DELETE(_tiles);

	CloseHandle(file);

}

void playGround::load()
{
	HANDLE file;
	DWORD read;

	int 
		idxX,
		idxY,
		tempX = -1000,
		tempY = -1000;

	tileInfo _tiles[2000];

	file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tileInfo) * 2000, &read, NULL);

	for (int i = 0; i < 2000; i++)
	{
		if (tempX < _tiles[i].tilePos.x)
		{
			tempX = _tiles[i].tilePos.x;
			idxX = i;
		}
		if (tempY < _tiles[i].tilePos.y)
		{
			tempY = _tiles[i].tilePos.y;
			idxY = i;
		}
	}

	int tempXsize = crtXsize;
	int tempYsize = crtYsize;

	setMap((tempX + 1) - (crtXsize - 18), (tempY + 1) - (crtYsize));

	if ((tempY + 1) - (tempYsize) > 0)
	{
		for (int i = 0; i < (tempY + 1) - (tempYsize); i++)
		{
			addYtile();
		}
	}
	if ((tempY + 1) - (tempYsize) < 0)
	{
		for (int i = 0; i < (tempYsize) - (tempYsize); i++)
		{
			removeYtile();
		}
	}
	if ((tempX + 1) - (tempXsize - 18) > 0)
	{
		for (int i = 0; i < ((tempX + 1) - (tempXsize - 18)); i++)
		{
			addXtile();
		}
	}
	if ((tempX + 1) - (tempXsize - 18) < 0)
	{
		for (int i = 0; i < ((tempXsize - 18) - (tempX + 1)); i++)
		{
			removeXtile();
		}
	}

	//crtXsize = (idxX + 19);
	//crtYsize = (idxY / idxX);

	for (int y = 0; y < crtYsize; y++)
	{
		for (int x = 0; x < crtXsize - 18; x++)
		{
			tile[y][x].tilePos	 = { _tiles[x + (y * (crtXsize - 18))].tilePos.x   , _tiles[x + (y * (crtXsize - 18))].tilePos.y };
			tile[y][x].layerPos1 = { _tiles[x + (y * (crtXsize - 18))].layerPos1.x , _tiles[x + (y * (crtXsize - 18))].layerPos1.y };
			tile[y][x].layerPos2 = { _tiles[x + (y * (crtXsize - 18))].layerPos2.x , _tiles[x + (y * (crtXsize - 18))].layerPos2.y };
			tile[y][x].geography = _tiles[x + (y * (crtXsize - 18))].geography;
			tile[y][x].rectYes   = _tiles[x + (y * (crtXsize - 18))].rectYes;
		}
	}	
	CloseHandle(file);
}