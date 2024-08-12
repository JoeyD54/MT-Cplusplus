//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "UnitTest_Log.h"
#include "D.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(ADV_Derived_Class, TestConfig::ALL)
{
#if ADV_Derived_Class

	TestingLog::Create();

	Trace::out("\ndefault constructor\n");
	{
		TestingLog::Reset();

		D  var;
		CHECK(var.c0 == 0);
		CHECK(var.poString == nullptr);
		CHECK(var.d0 == 0);
		CHECK(var.poHead == nullptr);
	}
	std::vector<int> v = TestingLog::GetVector();
	CHECK(v[0] == 1111);
	CHECK(v[1] == 2211);
	CHECK(v[2] == 2244);
	CHECK(v[3] == 1144);

	Trace::out("\nspecialized constructor\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var1(11, "0xABCx1", 13, pN0);

		CHECK(var1.c0 == 11);
		CHECK(strcmp(var1.poString, "0xABCx1")==0);
		CHECK(var1.d0 == 13);
		CHECK(var1.poHead == pN0);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 3311);
	CHECK(v[1] == 3311);
	CHECK(v[2] == 3311);

	CHECK(v[3] == 1177);
	CHECK(v[4] == 2277);

	CHECK(v[5] == 3344);
	CHECK(v[6] == 3344);
	CHECK(v[7] == 3344);

	CHECK(v[8] == 2244);
	CHECK(v[9] == 1144);

	Trace::out("\ncopy constructor\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var2_A(21, "0xABCx2", 23, pN0);

		CHECK(var2_A.c0 == 21);
		CHECK(strcmp(var2_A.poString, "0xABCx2") == 0);
		CHECK(var2_A.d0 == 23);
		CHECK(var2_A.poHead == pN0);
		CHECK( D::privCountNodes(var2_A.poHead) == 3);

		D var2_B(var2_A);

		CHECK(var2_A.c0 == 21);
		CHECK(strcmp(var2_A.poString, "0xABCx2") == 0);
		CHECK(var2_A.d0 == 23);
		CHECK(var2_A.poHead == pN0);
		CHECK(D::privCountNodes(var2_A.poHead) == 3);

		CHECK(var2_B.c0 == 21);
		CHECK(strcmp(var2_B.poString, "0xABCx2") == 0);
		CHECK(var2_B.d0 == 23);
		CHECK(var2_B.poHead != pN0);
		CHECK(D::privCountNodes(var2_B.poHead) == 3);
	}
	v = TestingLog::GetVector();
							// src
	CHECK(v[0] == 3311); // Node(default constructor)005FD318
	CHECK(v[1] == 3311); // Node(default constructor)005FD2A0
	CHECK(v[2] == 3311); // Node(default constructor)005FE040
	CHECK(v[3] == 1177); // Base(specialized constructor)00F5FC94
	CHECK(v[4] == 2277); // Derived(specialized constructor)00F5FC94
							// Copy constuctor
	CHECK(v[5] == 1122); // Base(copy constructor)00F5FC7C < -00F5FC94
	CHECK(v[6] == 3322); // Node(copy constructor)005FE0E8 < -005FD318
	CHECK(v[7] == 3322); // Node(copy constructor)005FE458 < -005FD2A0
	CHECK(v[8] == 3322); // Node(copy constructor)005FE420 < -005FE040
	CHECK(v[9] == 2222); // Derived(copy constructor)00F5FC7C < -00F5FC94
							// dest destructor
	CHECK(v[10] == 3344); // Node(destructor)005FE0E8
	CHECK(v[11] == 3344); // Node(destructor)005FE458
	CHECK(v[12] == 3344); // Node(destructor)005FE420
	CHECK(v[13] == 2244); // Derived(destructor)00F5FC7C
	CHECK(v[14] == 1144); // Base(destructor)00F5FC7C
							// src destructor
	CHECK(v[15] == 3344); // Node(destructor)005FD318
	CHECK(v[16] == 3344); // Node(destructor)005FD2A0
	CHECK(v[17] == 3344); // Node(destructor)005FE040
	CHECK(v[18] == 2244); // Derived(destructor)00F5FC94
	CHECK(v[19] == 1144); // Base(destructor)00F5FC94

	Trace::out("\nassignment operator\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var3_A(31, "0xABCx3", 33, pN0);

		Node *pNB0 = new Node();
		Node *pNB1 = new Node();
		pNB0->n0 = 990;
		pNB1->n0 = 991;

		pNB0->pNext = pNB1;
		pNB1->pNext = nullptr;

		D var3_B(331, "0xABCx33", 333, pNB0);

		CHECK(var3_A.c0 == 31);
		CHECK(strcmp(var3_A.poString, "0xABCx3") == 0);
		CHECK(var3_A.d0 == 33);
		CHECK(var3_A.poHead == pN0);
		CHECK(D::privCountNodes(var3_A.poHead) == 3);

		CHECK(var3_B.c0 == 331);
		CHECK(strcmp(var3_B.poString, "0xABCx33") == 0);
		CHECK(var3_B.d0 == 333);
		CHECK(var3_B.poHead == pNB0);
		CHECK(D::privCountNodes(var3_B.poHead) == 2);

		var3_B = var3_A;

		CHECK(var3_A.c0 == 31);
		CHECK(strcmp(var3_A.poString, "0xABCx3") == 0);
		CHECK(var3_A.d0 == 33);
		CHECK(var3_A.poHead == pN0);
		CHECK(D::privCountNodes(var3_A.poHead) == 3);

		CHECK(var3_B.c0 == 31);
		CHECK(strcmp(var3_B.poString, "0xABCx3") == 0);
		CHECK(var3_B.d0 == 33);
		CHECK(var3_B.poHead != pN0);
		CHECK(D::privCountNodes(var3_B.poHead) == 3);

	}
	v = TestingLog::GetVector();
							// A -nodes
	CHECK(v[0] == 3311); // Node(default constructor)001BE228
	CHECK(v[1] == 3311); // Node(default constructor)001BE490
	CHECK(v[2] == 3311); // Node(default constructor)001BE340
							// A special const
	CHECK(v[3] == 1177); // Base(specialized constructor)0059FC80
	CHECK(v[4] == 2277); // Derived(specialized constructor)0059FC80
							// B nodes
	CHECK(v[5] == 3311); // Node(default constructor)001BE260
	CHECK(v[6] == 3311); // Node(default constructor)001BE1F0
							// B construct
	CHECK(v[7] == 1177); // Base(specialized constructor)0059FC60
	CHECK(v[8] == 2277); // Derived(specialized constructor)0059FC60
							// Assignment operator
	CHECK(v[9] == 3344); // Node(destructor)001BE260
	CHECK(v[10] == 3344); // Node(destructor)001BE1F0
	CHECK(v[11] == 1133); // tBase(assignment operator)0059FC60 < -0059FC80
	CHECK(v[12] == 3322); // Node(copy constructor)001BE378 < -001BE228
	CHECK(v[13] == 3322); // Node(copy constructor)001BE3E8 < -001BE490
	CHECK(v[14] == 3322); // Node(copy constructor)001BE4C8 < -001BE340
	CHECK(v[15] == 2233); // tDerived(assignment operator)0059FC60 < -0059FC80
							// delete b
	CHECK(v[16] == 3344); // Node(destructor)001BE378
	CHECK(v[17] == 3344); // Node(destructor)001BE3E8
	CHECK(v[18] == 3344); // Node(destructor)001BE4C8
	CHECK(v[19] == 2244); // Derived(destructor)0059FC60
	CHECK(v[20] == 1144); // Base(destructor)0059FC60
							// delete a
	CHECK(v[21] == 3344); // Node(destructor)001BE228
	CHECK(v[22] == 3344); // Node(destructor)001BE490
	CHECK(v[23] == 3344); // Node(destructor)001BE340
	CHECK(v[24] == 2244); // Derived(destructor)0059FC80
	CHECK(v[25] == 1144); // Base(destructor)0059FC80

	Trace::out("\nMove assignment\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var4_A(41, "0xABCx4", 44, pN0);

		Node *pNB0 = new Node();
		Node *pNB1 = new Node();
		pNB0->n0 = 990;
		pNB1->n0 = 991;

		pNB0->pNext = pNB1;
		pNB1->pNext = nullptr;

		D var4_B(441, "0xABCx44", 444, pNB0);

		CHECK(var4_A.c0 == 41);
		CHECK(strcmp(var4_A.poString, "0xABCx4") == 0);
		CHECK(var4_A.d0 == 44);
		CHECK(var4_A.poHead == pN0);
		CHECK(D::privCountNodes(var4_A.poHead) == 3);

		CHECK(var4_B.c0 == 441);
		CHECK(strcmp(var4_B.poString, "0xABCx44") == 0);
		CHECK(var4_B.d0 == 444);
		CHECK(var4_B.poHead == pNB0);
		CHECK(D::privCountNodes(var4_B.poHead) == 2);

		var4_B = std::move(var4_A);

		CHECK(var4_A.c0 == 0);
		CHECK(var4_A.poString == nullptr);
		CHECK(var4_A.d0 == 0);
		CHECK(var4_A.poHead == nullptr);

		CHECK(var4_B.c0 == 41);
		CHECK(strcmp(var4_B.poString, "0xABCx4") == 0);
		CHECK(var4_B.d0 == 44);
		CHECK(var4_B.poHead != pNB0);
		CHECK(var4_B.poHead == pN0);
		CHECK(D::privCountNodes(var4_B.poHead) == 3);
	}
	v = TestingLog::GetVector();
							// Nodes for A
	CHECK(v[0] == 3311); // Node(default constructor)006BE458
	CHECK(v[1] == 3311); // Node(default constructor)006BE340
	CHECK(v[2] == 3311); // Node(default constructor)006BE228
							// Construct A
	CHECK(v[3] == 1177); // Base(specialized constructor)0019FD0C
	CHECK(v[4] == 2277); // Derived(specialized constructor)0019FD0C
							// Node for B
	CHECK(v[5] == 3311); // Node(default constructor)006BE378
	CHECK(v[6] == 3311); // Node(default constructor)006BE148
							// Construct B
	CHECK(v[7] == 1177); // Base(specialized constructor)0019FCEC
	CHECK(v[8] == 2277); // Derived(specialized constructor)0019FCEC
							// move assignment B = std::move(A)
	CHECK(v[9] == 3344); // Node(destructor)006BE378
	CHECK(v[10] == 3344); // Node(destructor)006BE148
	CHECK(v[11] == 1166); // Base(move assignment)0019FCEC < -0019FD0C
	CHECK(v[12] == 2266); // Derived(move assignment)0019FCEC < -0019FD0C
							// destroy B
	CHECK(v[13] == 3344); // Node(destructor)006BE458
	CHECK(v[14] == 3344); // Node(destructor)006BE340
	CHECK(v[15] == 3344); // Node(destructor)006BE228
	CHECK(v[16] == 2244); // Derived(destructor)0019FCEC
	CHECK(v[17] == 1144); // Base(destructor)0019FCEC
							// destroy A
	CHECK(v[18] == 2244); // Derived(destructor)0019FD0C
	CHECK(v[19] == 1144); // Base(destructor)0019FD0C

	Trace::out("\nMove constructor\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var5_A(51, "0xABCx5", 55, pN0);

		CHECK(var5_A.c0 == 51);
		CHECK(strcmp(var5_A.poString, "0xABCx5") == 0);
		CHECK(var5_A.d0 == 55);
		CHECK(var5_A.poHead == pN0);
		CHECK(D::privCountNodes(var5_A.poHead) == 3);

		D var5_B = std::move(var5_A);

		CHECK(var5_A.c0 == 0);
		CHECK(var5_A.poString == nullptr);
		CHECK(var5_A.d0 == 0);
		CHECK(var5_A.poHead == 0);

		CHECK(var5_B.c0 == 51);
		CHECK(strcmp(var5_B.poString, "0xABCx5") == 0);
		CHECK(var5_B.d0 == 55);
		CHECK(var5_B.poHead == pN0);
		CHECK(D::privCountNodes(var5_B.poHead) == 3);

	}
	v = TestingLog::GetVector();
							// create A nodes
	CHECK(v[0] == 3311);  // Node(default constructor)001DE4C8
	CHECK(v[1] == 3311);  // Node(default constructor)001DE2D0
	CHECK(v[2] == 3311);  // Node(default constructor)001DE260
							// construct A
	CHECK(v[3] == 1177);  // Base(specialized constructor)010FF634
	CHECK(v[4] == 2277);  // Derived(specialized constructor)010FF634
							// move constructor
	CHECK(v[5] == 1155);  // Base(move constructor)010FF61C < -010FF634
	CHECK(v[6] == 2255);  // Derived(move constructor)010FF61C < -010FF634
							// destroy B
	CHECK(v[7] == 3344);  // Node(destructor)001DE4C8
	CHECK(v[8] == 3344);  // Node(destructor)001DE2D0
	CHECK(v[9] == 3344);  // Node(destructor)001DE260
	CHECK(v[10] == 2244);  // Derived(destructor)010FF61C
	CHECK(v[11] == 1144);  // Base(destructor)010FF61C
							// destroy A
	CHECK(v[12] == 2244);  // Derived(destructor)010FF634
	CHECK(v[13] == 1144);  // Base(destructor)010FF634

	Trace::out("\nExpiring Construction\n");
	{
		TestingLog::Reset();
		D::foo1(D::foo());
	}
	v = TestingLog::GetVector();

#ifdef _DEBUG
	CHECK(v[0] == 3311); // Node(default constructor)0096E378
	CHECK(v[1] == 3311); // Node(default constructor)0096E340
	CHECK(v[2] == 3311); // Node(default constructor)0096E4C8
	CHECK(v[3] == 1177); // Base(specialized constructor)006FF4C0
	CHECK(v[4] == 2277); // Derived(specialized constructor)006FF4C0
	CHECK(v[5] == 1155); // Base(move constructor)006FF558 < -006FF4C0
	CHECK(v[6] == 2255); // Derived(move constructor)006FF558 < -006FF4C0
	CHECK(v[7] == 2244); // Derived(destructor)006FF4C0
	CHECK(v[8] == 1144); // Base(destructor)006FF4C0
	CHECK(v[9] == 61 );
	CHECK(v[10] == '0');
	CHECK(v[11] == 'x');
	CHECK(v[12] == '6');
	CHECK(v[13] == 66 );
	CHECK(v[14] == 90 );
	CHECK(v[15] == 91 );
	CHECK(v[16] == 92 );
	CHECK(v[17] == 3344); // Node(destructor)0096E378
	CHECK(v[18] == 3344); // Node(destructor)0096E340
	CHECK(v[19] == 3344); // Node(destructor)0096E4C8
	CHECK(v[20] == 2244); // Derived(destructor)006FF558
	CHECK(v[21] == 1144); // Base(destructor)006FF558

#else
	CHECK(v[0] == 3311); // Node(default constructor)0096E378
	CHECK(v[1] == 3311); // Node(default constructor)0096E340
	CHECK(v[2] == 3311); // Node(default constructor)0096E4C8
	CHECK(v[3] == 1177); // Base(specialized constructor)006FF4C0
	CHECK(v[4] == 2277); // Derived(specialized constructor)006FF4C0

	CHECK(v[5] == 61);
	CHECK(v[6] == '0');
	CHECK(v[7] == 'x');
	CHECK(v[8] == '6');
	CHECK(v[9] == 66);
	CHECK(v[10] == 90);
	CHECK(v[11] == 91);
	CHECK(v[12] == 92);

	CHECK(v[13] == 3344); // Node(destructor)0096E378
	CHECK(v[14] == 3344); // Node(destructor)0096E340
	CHECK(v[15] == 3344); // Node(destructor)0096E4C8
	CHECK(v[16] == 2244); // Derived(destructor)006FF558
	CHECK(v[17] == 1144); // Base(destructor)006FF558
	
#endif

	Trace::out("\nMove for Construction\n");
	{
		TestingLog::Reset();

		Node *pN0 = new Node();
		Node *pN1 = new Node();
		Node *pN2 = new Node();
		pN0->n0 = 90;
		pN1->n0 = 91;
		pN2->n0 = 92;
		pN0->pNext = pN1;
		pN1->pNext = pN2;
		pN2->pNext = nullptr;

		D var6_A(61, "0x6", 66, pN0);
		D::foo1( std::move(var6_A) );
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 3311); // Node(default constructor)01410598
	CHECK(v[1] == 3311); // Node(default constructor)0141DFD8
	CHECK(v[2] == 3311); // Node(default constructor)01415738
	CHECK(v[3] == 1177); // Base(specialized constructor)012FFD54
	CHECK(v[4] == 2277); // Derived(specialized constructor)012FFD54
	CHECK(v[5] == 61);
	CHECK(v[6] == '0');
	CHECK(v[7] == 'x');
	CHECK(v[8] == '6');
	CHECK(v[9] == 66);
	CHECK(v[10] == 90);
	CHECK(v[11] == 91);
	CHECK(v[12] == 92);
	CHECK(v[13] == 3344); // Node(destructor)01410598
	CHECK(v[14] == 3344); // Node(destructor)0141DFD8
	CHECK(v[15] == 3344); // Node(destructor)01415738
	CHECK(v[16] == 2244); // Derived(destructor)012FFD54
	CHECK(v[17] == 1144); // Base(destructor)012FFD54

	Trace::out("\n");

	TestingLog::Destroy();
#endif
} TEST_END

TEST_TEARDOWN(ADV_Derived_Class)
{
	TestingLog::Destroy();
}

// ---  End of File ---
