#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		
		TEST_METHOD(SortTest)
		{
			// TODO: Your test code here
			TextBuddy testClass;

			testClass.addLine("cstring");
			testClass.addLine("astring");
			testClass.addLine("bstring");
			testClass.sortFile();

			Assert::AreEqual("1.astring\n", testClass.searchFile("astring").c_str());
		}

		TEST_METHOD(SearchTest)
		{
			TextBuddy testClass;

			testClass.addLine("CS2103");
			testClass.addLine("IE2150");

			Assert::AreEqual("1.CS2103\n", testClass.searchFile("CS2103").c_str());
			Assert::AreEqual("2.IE2150\n", testClass.searchFile("IE2150").c_str());
			Assert::AreEqual("Not Found", testClass.searchFile("LAG3203").c_str());
		}


	};
}