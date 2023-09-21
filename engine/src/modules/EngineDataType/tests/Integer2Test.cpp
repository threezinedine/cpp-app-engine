#include "PreInclude.hpp"


TEST_F(EngineDataTypeTest, GivenIntegerVec2ThenItHasTheSamePropertiesAndMethodLikeTheInteger)
{
    ntt::Array<int, 2> value("Scores", { 1, 1 }, 0, 100);

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 1));
    EXPECT_THAT(value.GetName(), testing::Eq("Scores"));
}

TEST_F(EngineDataTypeTest, Integer2WithoutDefaultValueThenReturnsValue0)
{
    ntt::Array<int, 2> value("Scores");
    ntt::Timestep ts;

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 0));
    EXPECT_NO_THROW(value.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, Integer2WithoutLimit)
{
    ntt::Array<int, 2> value("Scores", { 1, 0 });
    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0));
}

TEST_F(EngineDataTypeTest, Integer2ConstructorWithExceedLimitDefaultValue)
{
    ntt::Array<int, 2> value("Scores", { 11, 0 }, 3, 6);
    EXPECT_THAT(value.Value(), testing::ElementsAre(6, 3));
}

TEST_F(EngineDataTypeTest, Integer2WithStorage)
{
    std::vector<int> defaultValue { 1, 0 };
    storage_->SetGetValues("Scores", { 4, 3 }, defaultValue);

    {
        ntt::Array<int, 2> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(4, 3));
    }
}

TEST_F(EngineDataTypeTest, Integer2InitializeViaStorageWithExceedLimits)
{
    std::vector<int> defaultValue { 1, 0 };
    storage_->SetGetValues("Scores", { 104, 3 }, defaultValue);

    {
        ntt::Array<int, 2> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(100, 3));
    }
}

TEST_F(EngineDataTypeTest, Integer2ChangingValue)
{
    ntt::Array<int, 2> value("Scores", { 2, 3 });

    value.SetValue({ 4, 1 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 1));
}

TEST_F(EngineDataTypeTest, Integer2SetValueWhichIsExceedTheLimits)
{
    ntt::Array<int, 2> value("Scores", { 2, 3 }, 0, 10);

    value.SetValue({ 4, 11 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 10));
}

TEST_F(EngineDataTypeTest, Integer2SetValueWhichIsExceedTheLowLimits)
{
    ntt::Array<int, 2> value("Scores", { 2, 3 }, 0, 10);

    value.SetValue({ -3, 11 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 10));
}

TEST_F(EngineDataTypeTest, Integer2SavingWhenBeDeleted)
{
    std::vector<int> defaultValue { 0, 0 };
    storage_->SetGetValues("Scores", { 2, 3 }, defaultValue);

    {
        ntt::Array<int, 2> value("Scores", defaultValue, 0, 100, storage_);

        value.SetValue({ 1, 1 });
    }

    storage_->ExpectSaveValuesIntCall(1, "Scores", { 1, 1 });
}

TEST_F(EngineDataTypeTest, Integer2WithInValidSetValue)
{
    ntt::Array<int, 2> value("Scores", { 1, 0 }, 0, 100);

    value.SetValue({ 1, 2, 3 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0));
}

TEST_F(EngineDataTypeTest, Integer2ToString)
{
    ntt::Array<int, 2> value ("Scores", { 1, 4 });

    EXPECT_THAT(value.ToString(), testing::Eq("Scores: (1, 4)"));
}