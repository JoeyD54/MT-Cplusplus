//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "UnitTest_Log.h"
#include "D.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(ADV_Base_Class, TestConfig::ALL)
{
#if ADV_Base_Class

	TestingLog::Create();

	Trace::out("\ndefault constructor\n");
	{
		TestingLog::Reset();

		C  var;
		CHECK(var.c0 == 0);
		CHECK(var.poString == nullptr);
	}
	std::vector<int> v = TestingLog::GetVector();
	CHECK(v[0] == 1111);
	CHECK(v[1] == 1144);

	Trace::out("\nspecialized constructor\n");
	{
		TestingLog::Reset();

		C var1(11, "ABCD");
		CHECK(var1.c0 == 11);
		CHECK(strcmp(var1.poString,"ABCD")== 0);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1144);

	Trace::out("\ncopy constructor\n");
	{
		TestingLog::Reset();

		C var2_A(21, "0x123x2");
		CHECK(var2_A.c0 == 21);
		CHECK(strcmp(var2_A.poString, "0x123x2") == 0);
		C var2_B(var2_A);
		CHECK(var2_A.c0 == 21);
		CHECK(strcmp(var2_A.poString, "0x123x2") == 0);
		CHECK(var2_B.c0 == 21);
		CHECK(strcmp(var2_B.poString, "0x123x2") == 0);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1122);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 1144);

	Trace::out("\nassignment operator\n");
	{
		TestingLog::Reset();

		C var3_A(31, "0x123x3");
		C var3_B;
		CHECK(var3_A.c0 == 31);
		CHECK(strcmp(var3_A.poString, "0x123x3") == 0);
		CHECK(var3_B.c0 == 0);
		CHECK(var3_B.poString == nullptr);
		var3_B = var3_A;
		CHECK(var3_A.c0 == 31);
		CHECK(strcmp(var3_A.poString, "0x123x3") == 0);
		CHECK(var3_B.c0 == 31);
		CHECK(strcmp(var3_B.poString, "0x123x3") == 0);
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

		C var4_A(41, "0x123x44");
		C var4_B;

		CHECK(var4_A.c0 == 41);
		CHECK(strcmp(var4_A.poString, "0x123x44") == 0);
		char *p4 = var4_A.poString;
		CHECK(var4_B.c0 == 0);
		CHECK(var4_B.poString == nullptr);

		var4_B = std::move(var4_A);

		CHECK(var4_B.c0 == 41);
		CHECK(strcmp(var4_B.poString, "0x123x44") == 0);
		CHECK(p4 == var4_B.poString);
		CHECK(var4_A.c0 == 0);
		CHECK(var4_A.poString == nullptr);
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

		C var5_A(51, "0x123x555");

		CHECK(var5_A.c0 == 51);
		CHECK(strcmp(var5_A.poString, "0x123x555") == 0);
		char *p5 = var5_A.poString;

		C var5_B = std::move(var5_A);

		CHECK(var5_B.c0 == 51);
		CHECK(strcmp(var5_B.poString, "0x123x555") == 0);
		CHECK(p5 == var5_B.poString);
		CHECK(var5_A.c0 == 0);
		CHECK(var5_A.poString == nullptr);
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1155);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 1144);

	Trace::out("\nExpiring Construction\n");
	{
		TestingLog::Reset();
		C::foo1(C::foo());
	}
	v = TestingLog::GetVector();
#ifdef _DEBUG
	CHECK(v[0] == 1177);
	CHECK(v[1] == 1155);
	CHECK(v[2] == 1144);
	CHECK(v[3] == 66);  // data in foo1
	CHECK(v[4] == '0'); //0
	CHECK(v[5] == 'x'); //x
	CHECK(v[6] == '6'); //6
	CHECK(v[7] == 1144);
#else
	CHECK(v[0] == 1177);
	CHECK(v[1] == 66);  // data in foo1
	CHECK(v[2] == '0'); //0
	CHECK(v[3] == 'x'); //x
	CHECK(v[4] == '6'); //6
	CHECK(v[5] == 1144);
#endif

	Trace::out("\nMove for Construction\n");
	{
		TestingLog::Reset();

		C var7_A(71, "0x7");
		C::foo1( std::move(var7_A) );
	}
	v = TestingLog::GetVector();
	CHECK(v[0] == 1177);
	CHECK(v[1] == 71);  // data in foo1
	CHECK(v[2] == '0'); //0
	CHECK(v[3] == 'x'); //x
	CHECK(v[4] == '7'); //7
	CHECK(v[5] == 1144)

	Trace::out("\n");

	TestingLog::Destroy();
#endif
} TEST_END

TEST_TEARDOWN(ADV_Base_Class)
{
	TestingLog::Destroy();
}

// ---  End of File ----
