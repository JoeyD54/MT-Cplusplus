//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "List_ReadOnly.h"

// -----------------------------------------
//     DO NOT MODIFY THIS FILE
// -----------------------------------------

bool List::Once = false;

void List::CreateListForTest()
{
	if (Once == false)
	{
		Once = true;

		Node *pLast = new Node();
		for (int i = 0; i < NodeCount - 1; i++)
		{
			Node *pNode = new Node();
			pNode->pNext = pLast;
			pLast = pNode;
		}
		this->poHead = pLast;

		srand(2020);

		Node *pTmp;

		pTmp = this->poHead;
		while (pTmp != nullptr)
		{
			std::string s0(1, 'A' + rand() % 26);
			std::string s1(1, 'A' + rand() % 26);
			std::string s3(1, '_');
			std::string s4(1, '0' + rand() % 10);
			std::string s5(1, '0' + rand() % 10);
			std::string s6(1, '0' + rand() % 10);

			pTmp->element = s0 + s1 + s3 + s4 + s5 + s6;
			pTmp = pTmp->pNext;
		}

		pTmp = this->poHead;
		while (pTmp)
		{
			pTmp->pRand = pTmp;
			while (pTmp->pRand == pTmp)
			{
				int index = rand() % NodeCount;

				Node *p = this->poHead;
				while (index--)
				{
					p = p->pNext;
				}
				pTmp->pRand = p;
			}


	//		pTmp->Print();
			pTmp = pTmp->pNext;
		}

	}
}


List::List()
{
	this->poHead = nullptr;
}

List::~List()
{
	Node *pTmp = this->poHead;
	while (pTmp != nullptr)
	{
		Node *pDeleteMe = pTmp;
		pTmp = pTmp->pNext;
		delete pDeleteMe;
	}
}

void List::Print() const
{
	Trace::out("\n");
	Node *pTmp = this->poHead;
	while (pTmp != nullptr)
	{
		pTmp->Print();
		pTmp = pTmp->pNext;
	}
	Trace::out("\n");
}

bool List::operator==(const List &other) const
{
	bool status(true);
	Node *pTmp    = this->poHead;
	Node *pOther  = other.poHead;

	if (pOther == nullptr)
	{
		status = false;
	}
	if (pTmp == nullptr)
	{
		status = false;
	}

	int count = 0;
	while (pTmp != nullptr && pOther != nullptr)
	{
		count++;		
		
		if (count == List::NodeCount)
		{
			if (pOther->element == pTmp->element &&
				pOther->pRand->element == pTmp->pRand->element &&
				pOther->pRand != pTmp->pRand &&
				pOther->pNext == nullptr &&
				pTmp->pNext == nullptr &&
				pOther != pTmp )
			{
				// true
			}
			else
			{
				status = false;
				break;
			}
		}
		else
		{
			if (pOther->element == pTmp->element &&
				pOther->pRand->element == pTmp->pRand->element &&
				pOther->pNext->element == pTmp->pNext->element &&
				pOther->pRand != pTmp->pRand &&
				pOther->pNext != pTmp->pNext &&
				pOther != pTmp)
			{
				// true
			}
			else
			{
				status = false;
				break;
			}
		}

		pOther = pOther->pNext;
		pTmp = pTmp->pNext;
	}

	if (count != List::NodeCount)
	{
		status = false;
	}

	return status;
}

// --- End of File ---
