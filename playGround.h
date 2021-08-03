#pragma once
#include "gameNode.h"

struct tileInfo
{
	RECT rect;		
	int geography;		//�Ӽ�
	bool rectYes;		//��Ʈ ��, ���� �ִ°�?
	POINT tilePos;
	POINT layerPos1;	
	POINT layerPos2;
};

class playGround : public gameNode
{
private:
	//��ư��
	RECT 
		layerButton1,		//���������ִ� Ÿ�ϻ�����ư
		layerButton2,		//������������ Ÿ�ϻ�����ư
		notPassTileButton,	//����Ұ���ư
		returnPassTileButton,
		zOrderButton,
		eraseButton,		//Ÿ�� ����¹�ư
		plusXtileButton,	//x�� ��ũ�� �����ϴ� ��ư
		plusYtileButton,	//y�� ��ũ�� �����ϴ� ��ư
		saveButton,			//�����ư
		loadButton,
		scrollButton,		//��Ÿ�� ��ũ�ѹ�ư
		scrollUpButton,		//��Ÿ�� ��ũ�� ����ư
		scrollDownButton,	//��Ÿ�� ��ũ�� �ٿ��ư
		select1,			//��Ÿ�� ������ư1
		select2;			//��Ÿ�� ������ư2

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

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void addXtile();
	void removeXtile();
	void removeYtile();
	void keyDownGroup();
	void addYtile();
	void imageInit();
	void save();
	void load();
};

