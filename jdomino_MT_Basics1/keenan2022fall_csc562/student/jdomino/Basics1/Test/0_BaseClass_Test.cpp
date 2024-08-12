//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "UnitTest_Log.h"
#include "B.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Base_Class, TestConfig::ALL)
{
#if Base_Class

	TestingLog::Create();

	Trace::out("\ndefault constructor\n");
	{
		TestingLog::Reset();

		A  var;
		CHECK(var.a0 == 0);
		CHECK(var.a1 == 0);
	}
	std::vector<int> v = TestingLog::GetVector();
	CHECK(v[0] == 1111);
	CHECK(v[1] == 1144);

	Trace::out("\nspecialized constructor\n");
	{
		TestingLog::Reset();

		A var1(11, 12);
		CHECK(var1.a0 == 11);
		CHECK(var1.a1 == 12);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1144);

	Trace::out("\ncopy constructor\n");
	{
		TestingLog::Reset();

		A var2_A(21, 22);
		CHECK(var2_A.a0 == 21);
		CHECK(var2_A.a1 == 22);
		A var2_B(var2_A);
		CHECK(var2_A.a0 == 21);
		CHECK(var2_A.a1 == 22);
		CHECK(var2_B.a0 == 21);
		CHECK(var2_B.a1 == 22);

	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1122);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 1144);

	Trace::out("\nassignment operator\n");
	{
		TestingLog::Reset();

		A var3_A(31, 32);
		A var3_B;
		CHECK(var3_A.a0 == 31);
		CHECK(var3_A.a1 == 32);
		CHECK(var3_B.a0 == 0);
		CHECK(var3_B.a1 == 0);
		var3_B = var3_A;
		CHECK(var3_A.a0 == 31);
		CHECK(var3_A.a1 == 32);
		CHECK(var3_B.a0 == 31);
		CHECK(var3_B.a1 == 32);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1111);
	CHECK(v[2] == 1133);
	CHECK(v[3] == 1144);
	CHECK(v[4] == 1144);

	Trace::out("\nMove assignment\n");
	{
		TestingLog::Reset();

		A var4_A(41, 42);
		A var4_B;
		CHECK(var4_A.a0 == 41);
		CHECK(var4_A.a1 == 42);
		CHECK(var4_B.a0 == 0);
		CHECK(var4_B.a1 == 0);

		var4_B = std::move(var4_A);
		CHECK(var4_A.a0 == 0);
		CHECK(var4_A.a1 == 0);
		CHECK(var4_B.a0 == 41);
		CHECK(var4_B.a1 == 42);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1111);
	CHECK(v[2] == 1166);
	CHECK(v[3] == 1144);
	CHECK(v[4] == 1144);

	Trace::out("\nMove constructor\n");
	{
		TestingLog::Reset();

		A var5_A(51, 52);
		CHECK(var5_A.a0 == 51);
		CHECK(var5_A.a1 == 52);
		A var5_B = std::move(var5_A);
		CHECK(var5_A.a0 == 0);
		CHECK(var5_A.a1 == 0);
		CHECK(var5_B.a0 == 51);
		CHECK(var5_B.a1 == 52);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1155);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 1144);

	Trace::out("\nExpiring Construction\n");
	{
		TestingLog::Reset();
		A::foo1(A::foo());
	}
	v = TestingLog::GetVector();
#ifdef _DEBUG
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1155);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 66);  // data in foo1
	CHECK(v[4] == 77);	// data in foo1
	CHECK(v[5] == 1144);
#else
	CHECK(v[0] == 1177);
	CHECK(v[1] == 66);  // data in foo1
	CHECK(v[2] == 77);	// data in foo1
	CHECK(v[3] == 1144);
#endif

	Trace::out("\nMove for Construction\n");
	{
		TestingLog::Reset();

		A var6_A(61, 62);
		A::foo1( std::move(var6_A) );
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 61);  // data in foo1
	CHECK(v[2] == 62);	// data in foo1
	CHECK(v[3] == 1144)

	Trace::out("\n");

	TestingLog::Destroy();
#endif
} TEST_END

TEST_TEARDOWN(Base_Class)
{
	TestingLog::Destroy();
}

// ---  End of File ---
