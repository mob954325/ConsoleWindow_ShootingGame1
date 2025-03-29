#include "ItemManager.h"

#include "GameManager.h"

namespace ItemManager
{
	Node*& ItemList = GameManager::GetItemList();

	void ItemManagerInitialize()
	{
		ItemList = GameManager::GetItemList();
	}
	
	void CreateItem(Vector2 spawnPos, Vector2 speed, ItemType type)
	{
		ScreenElement ItemData = SetItemElementValue({ 0, 0 }, 1, { (spawnPos.x + 1), spawnPos.y }, speed, type);
		AddNode(&ItemList, ItemData);
	}
	
	void ItemUpdate()
	{
		int ItemCount = NodeCount(ItemList);
		for (int i = 0; i < ItemCount; i++)
		{
			Node* currItem = FindNode(ItemList, i);
			if (!currItem) return;

			if ((currItem->data.position.x >= MAXWIDTH)
				|| (currItem->data.position.x <= 0)
				|| (currItem->data.health <= 0))
			{
				DeleteNode(&currItem, &ItemList);
				continue;
			}
			currItem->data.position.x += (currItem->data.speed.x * Time::GetDeltaTime());
			currItem->data.position.x += (currItem->data.speed.y * Time::GetDeltaTime());
		}
	}
	
	void ItemRender()
	{
		int itemCount = NodeCount(ItemList);
		for (int i = 0; i < itemCount; i++)
		{
			Node* currItem = FindNode(ItemList, i);

			for (int i = 0; i <= currItem->data.scale.y; i++)
			{
				for (int j = 0; j <= currItem->data.scale.x; j++)
				{
					int currX = (int)currItem->data.position.x - currItem->data.scale.x / 2 + j;
					int currY = (int)currItem->data.position.y - currItem->data.scale.y / 2 + i;
					if (currX == (int)currItem->data.position.x && currY == (int)currItem->data.position.y)
					{
						// 중앙
						ItemType currItemType = currItem->data.additionalElement.itemtype;

						switch (currItemType)
						{
						case WeaponUpgrade:
							ConsoleRenderer::ScreenDrawChar(currX, currY, L'力', FG_SKY_DARK);
							break;
						case Boom:
							ConsoleRenderer::ScreenDrawChar(currX, currY, L'爆', FG_SKY_DARK);
							break;
						case HpRestore:
							ConsoleRenderer::ScreenDrawChar(currX, currY, L'体', FG_SKY_DARK);
							break;
						default:
							ConsoleRenderer::ScreenDrawChar(currX, currY, L'M', FG_SKY_DARK);
							break;
						}
					}
					else
					{
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'▉', FG_RED);
					}
				}
			}
		}
	}
}
