#include "List.h"

void AddNode(Node** head, ScreenElement value)
{
	if (*head == NULL)
	{
		*head = (Node*)malloc(sizeof(Node));
		(*head)->data = value;
		(*head)->next = NULL;
		(*head)->prev = NULL;
	}
	else
	{
		Node* prevNode = *head;

		// 새 노드 생성
		*head = (Node*)malloc(sizeof(Node));
		(*head)->next = prevNode;
		(*head)->prev = NULL;
		(*head)->data = value;

		// prevNode 노드 수정
		prevNode->prev = *head;
	}
}

void DeleteNode(Node** node, Node** head)
{
	if (!node || !(*node)) return;

	Node* prevNode = (*node)->prev;
	Node* nextNode = (*node)->next;

	// 첫 번째 노드인 경우, head를 갱신
	if (prevNode == NULL)
	{
		*head = nextNode;  // 헤드를 다음 노드로 변경
		if (nextNode) {
			nextNode->prev = NULL;
		}
	}
	else
	{
		prevNode->next = nextNode;
	}

	if (nextNode)
	{
		nextNode->prev = prevNode;
	}

	free(*node);  // 메모리 해제
	*node = NULL; // Dangling pointer 방지
}


Node* FindNode(Node* head, int index)
{
	Node* currNode = head;

	int currIndex = 0;
	while (currNode != NULL)
	{
		if (currIndex == index) // 해당 인덱스 찾음
		{
			return currNode;
		}
		else
		{
			currNode = currNode->next;
		}

		currIndex++;
	}

	return NULL; // NULL
}

int NodeCount(Node* head)
{
	Node* currNode = head;

	if (!currNode) return 0;

	int cnt = 0;
	while (currNode != NULL)
	{
		currNode = currNode->next;
		cnt++;
	}

	return cnt;
}


void FreeAllNode(Node** head)
{
	int size = NodeCount(*head);
	for (int i = 0; i < size; i++)
	{
		Node* currNode = FindNode(*head, 0);
		DeleteNode(&currNode, head);
	}
}