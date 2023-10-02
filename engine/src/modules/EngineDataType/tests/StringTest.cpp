#include "PreInclude.hpp"
#include "EngineDataType/String.hpp"


TEST_F(EngineDataTypeTest, InitializeStringData)
{
    ntt::String<256> str("String");

    EXPECT_THAT(str.Value(), testing::StrEq(""));
}

TEST_F(EngineDataTypeTest, GetNameOfTheData)
{
    ntt::String<256> str("String");

    EXPECT_THAT(str.GetName(), testing::StrEq("String"));
}

TEST_F(EngineDataTypeTest, InitializeWithDefaultVaulue)
{
    std::string defaultString = "default string";
    ntt::String<256> str("String", defaultString);

    EXPECT_THAT(str.Value(), testing::StrEq(defaultString));
}

TEST_F(EngineDataTypeTest, InitializeWithDefaultValueAndStorage)
{
    storage_->SetGetValue("String", "Storage", "default");

    std::string defaultString = "default";
    ntt::String<256> str("String", defaultString, storage_);

    EXPECT_THAT(str.Value(), testing::StrEq("Storage"));
}

TEST_F(EngineDataTypeTest, StringWithOnUpdateMethod)
{
    ntt::Timestep ts;
    ntt::String<256> str("String");

    EXPECT_NO_THROW(str.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, StringToStringMethod)
{
    ntt::String<256> str("String", "test");

    EXPECT_THAT(str.ToString(), testing::StrEq("String: test"));
}

TEST_F(EngineDataTypeTest, StringInitiailizeWithStorage)
{
    storage_->SetGetValue("String", "storage string", "");

    ntt::String<256> str("String", storage_);

    EXPECT_THAT(str.Value(), testing::StrEq("storage string"));
}

TEST_F(EngineDataTypeTest, StringSetValueMethod)
{
    ntt::String<256> str("String");

    str.SetValue("Hello World");

    EXPECT_THAT(str.Value(), testing::StrEq("Hello World"));
}

TEST_F(EngineDataTypeTest, StringBeSavedWhenBeDeleted)
{
    storage_->SetGetValue("String", "storage string", "");

    {
        ntt::String<256> str("String", storage_);

        str.SetValue("test");
    }

    storage_->ExpectSaveValueStringCall(1, "String", "test");
}

TEST_F(EngineDataTypeTest, InitializeWithLengthExceed)
{
    ntt::String<3> str("String", "1234");

    EXPECT_THAT(str.Value(), testing::StrEq("123"));
}

TEST_F(EngineDataTypeTest, StringSetValueWithExceedLengthLimit)
{
    ntt::String<3> str("String");

    str.SetValue("12345");

    EXPECT_THAT(str.Value(), testing::StrEq("123"));
}

TEST_F(EngineDataTypeTest, InitializeStringWithStorageReturnsExceedLengthLimit)
{
    storage_->SetGetValue("String", "storage string", "");

    ntt::String<3> str("String", storage_);

    EXPECT_THAT(str.Value(), testing::StrEq("sto"));
}

TEST_F(EngineDataTypeTest, StringOnUpdateWithChoices)
{
    ntt::Timestep ts;
    ntt::String<7> str("String");
    ntt::StringOptions options{ .choices = std::vector<std::string> { "Hello", "Test" } };

    EXPECT_NO_THROW(str.OnUpdate(ts, ntt::NONE, (void*)&options));
}