#include "Precompiled.h"
#include "TileMap.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{

}

void TileMap::CreateTile(Vector2& outStart, Vector2& outEnd)
{
	for (int y = 0; y < kHeight; ++y)
	{
		for (int x = 0; x < kWidth; ++x)
		{
			TileNode* curNode = &m_tileNode[y][x];
			int tileAttribute = tileMapArray[y][x];

			curNode->tileAttribute = (TileAttribute::T)tileAttribute;
			curNode->index = y * kWidth + x;
			curNode->pos.x = x;
			curNode->pos.y = y;

			if (curNode->tileAttribute == TileAttribute::Start)
			{
				outStart.x = x;
				outStart.y = y;
			}
			else if (curNode->tileAttribute == TileAttribute::End)
			{
				outEnd.x = x;
				outEnd.y = y;
			}
		}
	}
}

void TileMap::Display(std::list<TileNode*> moveNodeList)
{
	for (int y = 0; y < kHeight; ++y)
	{
		for (int x = 0; x < kWidth; ++x)
		{
			TileNode* curNode = &m_tileNode[y][x];

			auto fi = std::find(moveNodeList.begin(), moveNodeList.end(), curNode);
			if (fi != moveNodeList.end())
				printf("#  ");
			else
				printf("%d  ", (int)curNode->tileAttribute);
		}
		
		printf("\n");
	}
}

TileNode* TileMap::GetTileNode(int x, int y) const
{
	if (x < 0 ||
		x >= kWidth)
		return NULL;

	if (y < 0 ||
		y >= kHeight)
		return NULL;

	return &m_tileNode[y][x];
}

TileNode* TileMap::GetTileNode(Vector2 pos) const
{
	if (pos.x < 0 ||
		pos.x >= kWidth)
		return NULL;

	if (pos.y < 0 ||
		pos.y >= kHeight)
		return NULL;

	return &m_tileNode[pos.y][pos.x];
}