#include "Precompiled.h"
#include <stdio.h>
#include "TileMap.h"
#include "PathFinder.h"

void main()
{
	TileMap tileMap;
	PathFinder pathFinder(&tileMap);
		
	Vector2 startPos;
	Vector2 endPos;
	tileMap.CreateTile(startPos, endPos);

	tileMap.Display(std::list<TileNode*>());
	printf("\n\n");
	auto nodeList = pathFinder.DoFindPath(startPos, endPos);
	tileMap.Display(nodeList);
}