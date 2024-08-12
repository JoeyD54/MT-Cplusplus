//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "List_ReadOnly.h"

List & List::operator = (const List &otherList)
{
	//AZUL_UNUSED_VAR(otherList);

	Node* curr = otherList.poHead, * temp;

	//insert node after ever node of original list
	while (curr)
	{
		temp = curr->pNext;

		//inserting node
		curr->pNext = new Node();
		curr->pNext->element = curr->element;
		curr->pNext->pNext = temp;
		curr = temp;
	}

	curr = otherList.poHead;


	//Adjust random pointers of new list
	while (curr)
	{
		if (curr->pNext)
		{
			curr->pNext->pRand = curr->pRand ? 
				curr->pRand->pNext : curr->pRand;
		}

		//move to next newly added node by skipping the original one
		curr = curr->pNext ? curr->pNext->pNext : curr->pNext;
	}

	Node* original = otherList.poHead, * copy = otherList.poHead->pNext;
	temp = copy;

	//separate the original and copied list
	while (original && copy)
	{
		original->pNext = original->pNext ? 
			original->pNext->pNext : original->pNext;

		copy->pNext = copy->pNext ? copy->pNext->pNext : copy->pNext;
		original = original->pNext;
		copy = copy->pNext;
	}

	this->poHead = temp;

	return *this;
}

// --- End of File ---
