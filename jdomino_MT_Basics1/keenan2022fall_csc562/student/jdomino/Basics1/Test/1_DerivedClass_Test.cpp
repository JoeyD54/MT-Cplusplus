//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "UnitTest_Log.h"
#include "B.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Derived_Class, TestConfig::ALL)
{
#if Derived_Class

	TestingLog::Create();

	Trace::out("\ndefault constructor\n");
	{
		TestingLog::Reset();

		B  var;
		CHECK(var.a0 == 0);
		CHECK(var.a1 == 0);
		CHECK(var.b0 == 0);
		CHECK(var.b1 == 0);
	}
	std::vector<int> v = TestingLog::GetVector();
	CHECK(v[0] == 1111);
	CHECK(v[1] == 2211);
	CHECK(v[2] == 2244);
	CHECK(v[3] == 1144);

	Trace::out("\nspecialized constructor\n");
	{
		TestingLog::Reset();

		B var1(11, 12, 13, 14);
		CHECK(var1.a0 == 11);
		CHECK(var1.a1 == 12);
		CHECK(var1.b0 == 13);
		CHECK(var1.b1 == 14);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 2244);
	CHECK(v[3] == 1144);

	Trace::out("\ncopy constructor\n");
	{
		TestingLog::Reset();

		B var2_A(21, 22, 23, 24);
		CHECK(var2_A.a0 == 21);
		CHECK(var2_A.a1 == 22);
		CHECK(var2_A.b0 == 23);
		CHECK(var2_A.b1 == 24);

		B var2_B(var2_A);
		CHECK(var2_A.a0 == 21);
		CHECK(var2_A.a1 == 22);
		CHECK(var2_A.b0 == 23);
		CHECK(var2_A.b1 == 24);
		CHECK(var2_B.a0 == 21);
		CHECK(var2_B.a1 == 22);
		CHECK(var2_B.b0 == 23);
		CHECK(var2_B.b1 == 24);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 1122);
	CHECK(v[3] == 2222);
	CHECK(v[4] == 2244);
	CHECK(v[5] == 1144);
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144);

	Trace::out("\nassignment operator\n");
	{
		TestingLog::Reset();

		B var3_A(31, 32, 33, 34);
		B var3_B;
		CHECK(var3_A.a0 == 31);
		CHECK(var3_A.a1 == 32);
		CHECK(var3_A.b0 == 33);
		CHECK(var3_A.b1 == 34);
		CHECK(var3_B.a0 == 0);
		CHECK(var3_B.a1 == 0);
		CHECK(var3_B.b0 == 0);
		CHECK(var3_B.b1 == 0);
		var3_B = var3_A;
		CHECK(var3_A.a0 == 31);
		CHECK(var3_A.a1 == 32);
		CHECK(var3_A.b0 == 33);
		CHECK(var3_A.b1 == 34);
		CHECK(var3_B.a0 == 31);
		CHECK(var3_B.a1 == 32);
		CHECK(var3_B.b0 == 33);
		CHECK(var3_B.b1 == 34);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 1111);
	CHECK(v[3] == 2211);
	CHECK(v[4] == 1133);
	CHECK(v[5] == 2233);
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144);
	CHECK(v[8] == 2244);
	CHECK(v[9] == 1144);

	Trace::out("\nMove assignment\n");
	{
		TestingLog::Reset();

		B var4_A(41, 42, 43, 44);
		B var4_B;
		CHECK(var4_A.a0 == 41);
		CHECK(var4_A.a1 == 42);
		CHECK(var4_A.b0 == 43);
		CHECK(var4_A.b1 == 44);
		CHECK(var4_B.a0 == 0);
		CHECK(var4_B.a1 == 0);
		CHECK(var4_B.b0 == 0);
		CHECK(var4_B.b1 == 0);
		var4_B = std::move(var4_A);
		CHECK(var4_A.a0 == 0);
		CHECK(var4_A.a1 == 0);
		CHECK(var4_A.b0 == 0);
		CHECK(var4_A.b1 == 0);
		CHECK(var4_B.a0 == 41);
		CHECK(var4_B.a1 == 42);
		CHECK(var4_B.b0 == 43);
		CHECK(var4_B.b1 == 44);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 1111);
	CHECK(v[3] == 2211);
	CHECK(v[4] == 1166);
	CHECK(v[5] == 2266);
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144);
	CHECK(v[8] == 2244);
	CHECK(v[9] == 1144);

	Trace::out("\nMove constructor\n");
	{
		TestingLog::Reset();

		B var5_A(51, 52, 53, 54);
		CHECK(var5_A.a0 == 51);
		CHECK(var5_A.a1 == 52);
		CHECK(var5_A.b0 == 53);
		CHECK(var5_A.b1 == 54);
		B var5_B = std::move(var5_A);
		CHECK(var5_A.a0 == 0);
		CHECK(var5_A.a1 == 0);
		CHECK(var5_A.b0 == 0);
		CHECK(var5_A.b1 == 0);
		CHECK(var5_B.a0 == 51);
		CHECK(var5_B.a1 == 52);
		CHECK(var5_B.b0 == 53);
		CHECK(var5_B.b1 == 54);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 1155);
	CHECK(v[3] == 2255);
	CHECK(v[4] == 2244);
	CHECK(v[5] == 1144);
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144);

	Trace::out("\nExpiring Construction\n");
	{
		TestingLog::Reset();
		B::foo1(B::foo());
	}
	v = TestingLog::GetVector();
#ifdef _DEBUG
	CHECK(v[0] == 1177);    // special
	CHECK(v[1] == 2277);
	CHECK(v[2] == 1155);   // move
	CHECK(v[3] == 2255);
	CHECK(v[4] == 2244);   // destruct 
	CHECK(v[5] == 1144);
	CHECK(v[6] == 66);  // data in foo1
	CHECK(v[7] == 77);	// data in foo1
	CHECK(v[8] == 88);	// data in foo1
	CHECK(v[9] == 99);  // data in foo1
	CHECK(v[10] == 2244); // destruct
	CHECK(v[11] == 1144);
#else
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 66);  // data in foo1
	CHECK(v[3] == 77);	// data in foo1
	CHECK(v[4] == 88);	// data in foo1
	CHECK(v[5] == 99);  // data in foo1
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144);
#endif

	Trace::out("\nMove for Construction\n");
	{
		TestingLog::Reset();

		B var6_A(61, 62, 63, 64);
		B::foo1( std::move(var6_A) );
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 2277);
	CHECK(v[2] == 61);  // data in foo1
	CHECK(v[3] == 62);	// data in foo1
	CHECK(v[4] == 63);	// data in foo1
	CHECK(v[5] == 64);  // data in foo1
	CHECK(v[6] == 2244);
	CHECK(v[7] == 1144)

	Trace::out("\n");	
	
	TestingLog::Destroy();
#endif
} TEST_END

TEST_TEARDOWN(Derived_Class)
{
	TestingLog::Destroy();
}


// ---  End of File ---
