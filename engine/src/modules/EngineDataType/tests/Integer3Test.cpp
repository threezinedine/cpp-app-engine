#include "PreInclude.hpp"
#include "EngineDataTypeTest.hpp"


TEST_F(EngineDataTypeTest, GivenIntegerVec3ThenItHasTheSamePropertiesAndMethodLikeTheInteger)
{
    ntt::Data<int, 3> value("Scores", { 1, 1, 2 }, 0, 100);

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 1, 2));
    EXPECT_THAT(value.GetName(), testing::Eq("Scores"));
}

TEST_F(EngineDataTypeTest, Integer3WithoutDefaultValueThenReturnsValue0)
{
    ntt::Data<int, 3> value("Scores");
    ntt::Timestep ts;

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 0, 0));
    EXPECT_NO_THROW(value.OnUpdate(ts));
}

TEST_F(EngineDataTypeTest, Integer3WithoutLimit)
{
    ntt::Data<int, 3> value("Scores", { 1, 0, 12 });
    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0, 12));
}

TEST_F(EngineDataTypeTest, Integer3ConstructorWithExceedLimitDefaultValue)
{
    ntt::Data<int, 3> value("Scores", { 11, 0, 11 }, 3, 6);
    EXPECT_THAT(value.Value(), testing::ElementsAre(6, 3, 6));
}

TEST_F(EngineDataTypeTest, Integer3WithStorage)
{
    std::vector<int> defaultValue = { 1, 0, 1 };
    storage_->SetGetIntegersReturn("Scores", { 4, 3, 8 }, defaultValue);
    storage_->IgnoreSetIntegers("Scores");

    {
        ntt::Data<int, 3> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(4, 3, 8));
    }
}

TEST_F(EngineDataTypeTest, Integer3InitializeViaStorageWithExceedLimits)
{
    std::vector<int> defaultValue { 1, 0, 0 };
    storage_->SetGetIntegersReturn("Scores", { 104, 3, 10 }, defaultValue);
    storage_->IgnoreSetIntegers("Scores");

    {
        ntt::Data<int, 3> value("Scores", defaultValue, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::ElementsAre(100, 3, 10));
    }
}

TEST_F(EngineDataTypeTest, Integer3ChangingValue)
{
    ntt::Data<int, 3> value("Scores", { 2, 3, 4 });

    value.SetValue({ 4, 1, 5 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 1, 5));
}

TEST_F(EngineDataTypeTest, Integer3SetValueWhichIsExceedTheLimits)
{
    ntt::Data<int, 3> value("Scores", { 2, 3, 3 }, 0, 10);

    value.SetValue({ 4, 11, 15 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(4, 10, 10));
}

TEST_F(EngineDataTypeTest, Integer3SetValueWhichIsExceedTheLowLimits)
{
    ntt::Data<int, 3> value("Scores", { 2, 3, 5 }, 0, 10);

    value.SetValue({ -3, 11, 4 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(0, 10, 4));
}

TEST_F(EngineDataTypeTest, Integer3SavingWhenBeDeleted)
{
    std::vector<int> defaultValue { 0, 0, 0 };
    storage_->SetGetIntegersReturn("Scores", { 2, 3, 4 }, defaultValue);

    EXPECT_CALL(*storage_, SaveIntegers("Scores", std::vector<int>{ 1, 1, 1 })).Times(1);

    {
        ntt::Data<int, 3> value("Scores", defaultValue, 0, 100, storage_);

        value.SetValue({ 1, 1, 1 });
    }
}

TEST_F(EngineDataTypeTest, Integer3WithInValidSetValue)
{
    ntt::Data<int, 3> value("Scores", { 1, 0, 1 }, 0, 100);

    value.SetValue({ 1, 2 });

    EXPECT_THAT(value.Value(), testing::ElementsAre(1, 0, 1));
}