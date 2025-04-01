#include "ItemManager.h"

#include "DebugUtility.h"

#include "GameManager.h"

namespace ItemManager
{
	void CheckItemHealth(Node* item);

	Node*& ItemList = GameManager::GetItemList();

	void Initialize()
	{
		ItemList = GameManager::GetItemList();
	}
	
	void CreateItem(Vector2 spawnPos, Vector2 speed, ItemType type)
	{
		ScreenElement ItemData = SetItemElementValue({ 1, 1 }, MAX_BOUNCE_NUMBER, { (spawnPos.x + 1), spawnPos.y }, speed, type);
		AddNode(&ItemList, ItemData);
	}
	
	void ItemUpdate()
	{
		int ItemCount = NodeCount(ItemList);
		for (int i = 0; i < ItemCount; i++)
		{
			Node* currItem = FindNode(ItemList, i);
			if (!currItem) return;

			CheckItemHealth(currItem);

			// Item 움직임 - 화면 끝에 도달하면 바운스
			if(GameManager::CheckVaildPosition(currItem->data.position, currItem->data.scale) == 0)
			{
				if (currItem->data.position.x <= 0 || currItem->data.position.x >= MAXWIDTH)
				{
					currItem->data.speed.x *= -1;
					currItem->data.health--;
				}
				if (currItem->data.position.y <= 0 || currItem->data.position.y >= MAXHEIGHT)
				{
					currItem->data.speed.y *= -1;
					currItem->data.health--;
				}
			}
			currItem->data.position.x += (currItem->data.speed.x * Time::GetDeltaTime());
			currItem->data.position.y += (currItem->data.speed.y * Time::GetDeltaTime());
		}
	}
	
	void ItemRender()
	{
		int itemCount = NodeCount(ItemList);
		for (int i = 0; i < itemCount; i++)
		{
			Node* currItem = FindNode(ItemList, i);

			for (int i = 1; i <= currItem->data.scale.y; i++)
			{
				for (int j = 1; j <= currItem->data.scale.x; j++)
				{
					int currX = (int)(currItem->data.position.x - currItem->data.scale.x / 2 + j);
					int currY = (int)(currItem->data.position.y - currItem->data.scale.y / 2 + i);
					// 중앙
					ItemType currItemType = currItem->data.additionalElement.itemtype;

					switch (currItemType)
					{
					case WeaponUpgrade:
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'U', FG_SKY_DARK);
						break;
					case BoomItem:
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'B', FG_YELLOW);
						break;
					case HpRestore:
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'H', FG_GREEN);
						break;
					default:
						ConsoleRenderer::ScreenDrawChar(currX, currY, L'M', FG_SKY_DARK);
						break;
					}
				}
			}
		}
	}

	void CheckItemHealth(Node* item)
	{
		if (item->data.health <= 0)
		{
			DeleteNode(&item, &ItemList);
		}
	}
}
