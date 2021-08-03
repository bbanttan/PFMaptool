#pragma once
#include "gameNode.h"

struct tileInfo
{
	RECT rect;		
	int geography;		//속성
	bool rectYes;		//렉트 즉, 벽이 있는가?
	POINT tilePos;
	POINT layerPos1;	
	POINT layerPos2;
};

class playGround : public gameNode
{
private:
	//버튼들
	RECT 
		layerButton1,		//지나갈수있는 타일생성버튼
		layerButton2,		//지나갈수없는 타일생성버튼
		notPassTileButton,	//통행불가버튼
		returnPassTileButton,
		zOrderButton,
		eraseButton,		//타일 지우는버튼
		plusXtileButton,	//x축 맵크기 조절하는 버튼
		plusYtileButton,	//y축 맵크기 조절하는 버튼
		saveButton,			//저장버튼
		loadButton,
		scrollButton,		//맵타일 스크롤버튼
		scrollUpButton,		//맵타일 스크롤 업버튼
		scrollDownButton,	//맵타일 스크롤 다운버튼
		select1,			//맵타일 종류버튼1
		select2;			//맵타일 종류버튼2

	float crtCamXpos;
	float crtCamYpos;

	int mouseGridX;
	int mouseGridY;
	int selectTileX;
	int selectTileY;
	int crtButtonKind;

	bool tileSetMouseOn;

	vector<vector<tileInfo>> tile;

public:
	
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void addXtile();
	void removeXtile();
	void removeYtile();
	void keyDownGroup();
	void addYtile();
	void imageInit();
	void save();
	void load();
};

