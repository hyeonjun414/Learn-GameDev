#pragma once


// ������Ʈ �׷�
enum class OBJ_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BULLET,
	MISSILE,

	TEXT,
	IMAGE,

	SIZE,
};

// ��� �׷�
enum class SCENE_TYPE
{
	NONE,
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	SIZE,
};

// Ű ����
enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����	
	HOLD,	// ������ �ִ� ����
	AWAY,	// �� �� ����
};

// Ű ����
enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,Z,X,C,V,B,
	ALT,LSHIFT,CTRL,
	SPACE,ENTER,ESC,

	SIZE
};

// �׸��⿡ ����� �귯���� �� �׷�
enum class BRUSH_TYPE
{
	HOLLOW,

	SIZE
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	SIZE
};