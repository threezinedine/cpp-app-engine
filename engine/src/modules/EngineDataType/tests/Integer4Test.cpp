#include "PreInclude.hpp"


TEST_F(EngineDataTypeTest, GivenIntegerVec4ThenItHasTheSamePropertiesAndMethodLikeTheInteger)
{
    ntt::Array<int, 4> value("Scores", { 1, 1, 2, 3 }, 0, 100);

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 1, 2, 3));
    EXPECT_THAT(value.GetName(), testing::Eq("Scores"));
}

TEST_F(EngineDataTypeTest, Integer4WithoutDefaultValueThenReturnsValue0)
{
    ntt::Array<int, 4> value("Scores");
    ntt::Timestep ts;

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 0, 0, 0));
    EXPECT_NO_THROW(value.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, Integer4WithoutLimit)
{
    ntt::Array<int, 4> value("Scores", { 1, 0, 12, 12 });
    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0, 12, 12));
}

TEST_F(EngineDataTypeTest, Integer4ConstructorWithExceedLimitDefaultValue)
{
    ntt::Array<int, 4> value("Scores", { 11, 0, 11, 2 }, 3, 6);
    EXPECT_THAT(value.Value(), testing::ElementsAre(6, 3, 6, 3));
}

TEST_F(EngineDataTypeTest, Integer4WithStorage)
{
    std::vector<int> defaultValue = { 1, 0, 1, 1 };
    storage_->SetGetValues("Scores", { 4, 3, 8, 2 }, defaultValue);

    {
        ntt::Array<int, 4> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(4, 3, 8, 2));
    }
}

TEST_F(EngineDataTypeTest, Integer4InitializeViaStorageWithExceedLimits)
{
    std::vector<int> defaultValue { 1, 0, 0, 0 };
    storage_->SetGetValues("Scores", { 104, 3, 10, 100 }, defaultValue);

    {
        ntt::Array<int, 4> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(100, 3, 10, 100));
    }
}

TEST_F(EngineDataTypeTest, Integer4ChangingValue)
{
    ntt::Array<int, 4> value("Scores", { 2, 3, 4, 5 });

    value.SetValue({ 4, 1, 5, 2 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 1, 5, 2));
}

TEST_F(EngineDataTypeTest, Integer4SetValueWhichIsExceedTheLimits)
{
    ntt::Array<int, 4> value("Scores", { 2, 3, 3, 1 }, 0, 10);

    value.SetValue({ 4, 11, 15, 12 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 10, 10, 10));
}

TEST_F(EngineDataTypeTest, Integer4SetValueWhichIsExceedTheLowLimits)
{
    ntt::Array<int, 4> value("Scores", { 2, 3, 5, 3 }, 0, 10);

    value.SetValue({ -3, 11, 4, 2 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 10, 4, 2));
}

TEST_F(EngineDataTypeTest, Integer4SavingWhenBeDeleted)
{
    std::vector<int> defaultValue { 0, 0, 0, 0 };
    storage_->SetGetValues("Scores", { 2, 3, 4, 5 }, defaultValue);

    {
        ntt::Array<int, 4> value("Scores", defaultValue, 0, 100, storage_);

        value.SetValue({ 1, 1, 1, 1 });
    }

    storage_->ExpectSaveValuesIntCall(1, "Scores", { 1, 1, 1, 1 });
}

TEST_F(EngineDataTypeTest, Integer4WithInValidSetValue)
{
    ntt::Array<int, 4> value("Scores", { 1, 0, 1, 3 }, 0, 100);

    value.SetValue({ 1, 2, 4 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0, 1, 3));
}