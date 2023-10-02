#include "PreInclude.hpp"
#include "EngineCores/StringUtils.hpp"


TEST(StringUtilsTest, GivenAString_WhenUseSplitString_ThenReturnTheListOfWords)
{
    std::string str = "Hello World";

    std::vector<std::string> words = ntt::SplitString(str, ' ');

    EXPECT_THAT(words, testing::ElementsAre("Hello", "World"));
}

TEST(StringUtilsTest, GivenAStringWithTheSeparateCharacterIsAtTheEnd_WhenUseSplitString_ThenReturnTheListOfWordsWithTheEmptyString)
{
    std::string str = "Hello World ";

    std::vector<std::string> words = ntt::SplitString(str, ' ');

    EXPECT_THAT(words, testing::ElementsAre("Hello", "World", ""));
}

TEST(StringUtilsTest, GivenAStringWithoutSeparateCharacter_WhenUseSplitString_TheReturnThatString)
{
    std::string str = "Hello World ";

    std::vector<std::string> words = ntt::SplitString(str, '/');

    EXPECT_THAT(words, testing::ElementsAre("Hello World "));
}

TEST(StringUtilsTest, GivenAStringWithOnlySeparateCharacter_WhenUseSplitString_ThenReturn2EmptyString)
{
    std::string str = "/";

    std::vector<std::string> words = ntt::SplitString(str, '/');

    EXPECT_THAT(words, testing::ElementsAre("", ""));
}

TEST(StringUtilsTest, GivenAnEmptyString_WhenUseSplitString_ThenReturnTheEmptyElement)
{
    std::string str = "";

    std::vector<std::string> words = ntt::SplitString(str, '/');

    EXPECT_THAT(words, testing::ElementsAre(""));
}

TEST(StringUtilsTest, GivenAVectorOfStrings_WhenUseConcatString_ThenReturnACompleteString)
{
    std::vector<std::string> vector { "Hello", "Wolrd" };

    EXPECT_THAT(ntt::ConcatString(vector, ' '), testing::StrEq("Hello Wolrd"));
}

TEST(StringUtilsTest, GivenAnEmptyVector_WhenUseConcatString_ThenReturnEmptyString)
{
    std::vector<std::string> vector;

    EXPECT_THAT(ntt::ConcatString(vector, ' '), testing::StrEq(""));
}

TEST(StringUtilsTest, GivenAVector_WhenUseConcatStringWithEmptyLink_ThenReturnEmptyString)
{
    std::vector<std::string> vector { "He", "llo"};

    EXPECT_THAT(ntt::ConcatString(vector), testing::StrEq("Hello"));
}