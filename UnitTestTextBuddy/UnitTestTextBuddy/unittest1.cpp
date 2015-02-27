#include "stdafx.h"
#include "CppUnitTest.h"
#include "\\psf\Home\Desktop\CS2103\TextBuddy_CE2\Source Tree\TB_CE2\TB_CE2\TextBuddy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTextBuddy
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestSearch)
		{
			TextBuddy testClass;

			testClass.addLine("CS2103");
			testClass.addLine("IE2150");

			Assert::AreEqual("1.CS2103", testClass.searchFile("CS2103").c_str());
			Assert::AreEqual("2.IE2150", testClass.searchFile("IE2150").c_str());
			Assert::AreEqual("Not Found", testClass.searchFile("LAG3203").c_str());
		}

		TEST_METHOD(TestSort)
		{
			TextBuddy testClass;

			testClass.addLine("cstring");
			testClass.addLine("astring");
			testClass.addLine("bstring");
			testClass.sortFile();

			Assert::AreEqual("astring", testClass.searchFile("astring").c_str());
		}

	};
}