#include "pch.h"
#include <gtest/gtest.h>
#include "../softServe_task1/My_list.h"
#include "../softServe_task1/FileName.c"

class StringListTest :public ::testing::Test
{
protected:
	char** list;
public:
	void SetUp() override
	{
		list = NULL;
		StringListInit(&list);
	}

	void TearDown()override
	{
		StringListDestroy(&list);
	}
};

TEST_F(StringListTest, InitAndAddTest)
{
	EXPECT_EQ(StringListSize(list), 0);
	StringListAdd(&list, (char*)"roman");
	StringListAdd(&list, (char*)"tom");
	EXPECT_EQ(StringListSize(list), 2);
	EXPECT_STREQ(list[0], (char*)"roman");
	EXPECT_STREQ(list[1], (char*)"tom");
	EXPECT_EQ(list[2], nullptr);
}

TEST_F(StringListTest, IndexOfTest)
{
	char test[] = "roman";
	char test_not_found[] = "tom";
	StringListAdd(&list, (char*)"roman");
	EXPECT_EQ(StringListIndexOf(list, test), 0);
	EXPECT_EQ(StringListIndexOf(list, test_not_found), -1);
}

TEST_F(StringListTest, RemoveTest)
{
	StringListAdd(&list, (char*)"roman");
	StringListAdd(&list, (char*)"roman");
	StringListAdd(&list, (char*)"bob");
	StringListRemove(&list, (char*)"roman");
	EXPECT_EQ(StringListIndexOf(list, (char*)"roman"), -1);
	EXPECT_EQ(StringListSize(list), 1);
}

TEST_F(StringListTest, RemoveDuplicatesTest)
{
	StringListAdd(&list, (char*)"roman");
	StringListAdd(&list, (char*)"roman");
	StringListAdd(&list, (char*)"bob");
	StringListRemoveDuplicates(&list);
	EXPECT_EQ(StringListSize(list), 2);
}

TEST_F(StringListTest, SortTest) 
{
	StringListAdd(&list, (char*)"Zebra");
	StringListAdd(&list, (char*)"Apple");
	StringListAdd(&list, (char*)"Mango");
	StringListSort(list);
	EXPECT_EQ(StringListSize(list), 3);
	EXPECT_STREQ(list[0], (char*)"Apple");
	EXPECT_STREQ(list[1], (char*)"Mango");
	EXPECT_STREQ(list[2], (char*)"Zebra");
}

TEST_F(StringListTest, ReplaceInStringsTest) 
{
	StringListAdd(&list, (char*)"hello world");
	StringListAdd(&list, (char*)"world of tanks");
	StringListAdd(&list, (char*)"no matches here");
	StringListReplaceInStrings(list, (char*)"world", (char*)"C++");
	EXPECT_STREQ(list[0], (char*)"hello C++");
	EXPECT_STREQ(list[1], (char*)"C++ of tanks");
	EXPECT_STREQ(list[2], (char*)"no matches here");
	StringListAdd(&list, (char*)"a a a");
	StringListReplaceInStrings(list, (char*)"a", (char*)"bbb");
	EXPECT_STREQ(list[3],(char*)"bbb bbb bbb");
}