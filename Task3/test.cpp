#include "pch.h" 
#include <gmock/gmock.h>
#include "../soft_serveTask3/statistic.hpp"
#include "../soft_serveTask3/analyzer.cpp"
#include <filesystem>
#include <fstream>

class CodeAnalyzerTest :public ::testing::Test
{
protected:
	CodeAnalyzer obj;
	std::string folder_test_path = "D:\\laboratorni\\CodeAnalyzer";
	std::string test_file = "D:\\laboratorni\\CodeAnalyzer\\TempForTest.txt";

	void RunParseTestPath()
	{
		obj.ParseFilePath(folder_test_path);
	}

	size_t GetVectorSize()
	{
		return obj.file_paths.size();
	}

	void ParseTestFile()
	{
		obj.ParseFile(test_file);
	}

	void SetFakeStats(int files, int blank, int comment, int code) 
	{
		obj.stats.total_files = files;
		obj.stats.blank_lines = blank;
		obj.stats.comment_lines = comment;
		obj.stats.code_lines = code;
	}

	void WriteTestStats()
	{
		obj.WriteStats(14.4);
	}

	void StartProgramTest() 
	{
		obj.StartProgram(folder_test_path);
	}

	int GetCodeLines() 
	{ 
		return obj.stats.code_lines.load(); 
	}

	int GetCommentLines() 
	{
		return obj.stats.comment_lines.load(); 
	}

	int GetBlankLines() 
	{
		return obj.stats.blank_lines.load(); 
	}

	int GetTotalFiles() 
	{ 
		return obj.stats.total_files.load(); 
	}
};

TEST_F(CodeAnalyzerTest, ParseFilePathTest)
{
	RunParseTestPath();
	EXPECT_EQ(GetVectorSize(), 2);
}

TEST_F(CodeAnalyzerTest, ParseFileTest)
{
	ParseTestFile();
	EXPECT_EQ(GetCodeLines(), 1);     
	EXPECT_EQ(GetCommentLines(), 3);  
	EXPECT_EQ(GetBlankLines(), 1);
	EXPECT_EQ(GetTotalFiles(), 1);
}

TEST_F(CodeAnalyzerTest, WriteStatsTest)
{
	SetFakeStats(12, 32, 432, 32);
	WriteTestStats();
	std::string file_for_stats = "Statistick.txt";
	EXPECT_TRUE(std::filesystem::exists(file_for_stats));
	std::ifstream fp(file_for_stats);
	ASSERT_TRUE(fp.is_open());
	std::stringstream buffer;
	buffer << fp.rdbuf();
	std::string file_content = buffer.str();
	EXPECT_NE(file_content.find("Total files processed:12"), std::string::npos);
	EXPECT_NE(file_content.find("Blank lines:32"), std::string::npos);
	EXPECT_NE(file_content.find("Comment lines:432"), std::string::npos);
	EXPECT_NE(file_content.find("Code lines:32"), std::string::npos);
	fp.close();
	std::filesystem::remove(file_for_stats);
}

TEST_F(CodeAnalyzerTest, StartProgramTest)
{
	StartProgramTest();
	EXPECT_TRUE(std::filesystem::exists("Statistick.txt"));
	std::filesystem::remove("Statistick.txt");
}