#pragma once
#include "DataTypes.h"

// Node =================================

typedef struct Node
{
	ScreenElement data;
	struct Node* next;
	struct Node* prev;
} ObjectNode;

// Function =================================

void AddNode(Node** head, ScreenElement value);
void DeleteNode(Node** node, Node** head);
Node* FindNode(Node* head, int index);
int NodeCount(Node* head);
void FreeAllNode(Node** head);