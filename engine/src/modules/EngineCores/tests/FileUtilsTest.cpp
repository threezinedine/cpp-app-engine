#include "PreInclude.hpp"
#include "EngineCores/FileUtils.hpp"


TEST(FileUtilsTest, GivenAFilePath_WhenGetTheFolderOfThat_ThenReturnTheValidValue)
{
    std::string filePath = "C:/Users/Acer/TestFolder/test.txt";

    EXPECT_THAT(ntt::GetFolder(filePath), testing::StrEq("C:/Users/Acer/TestFolder"));
}