#include "PreInclude.hpp"
#include "EngineDataTypeTest.hpp"


TEST_F(EngineDataTypeTest, GivenAnIntegerValueIsCreatedWithThenItHasTheImguiRender)
{
    ntt::Integer value("Scores");

    EXPECT_THAT(value.Value(), testing::Eq(0));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithDefaultValueThenItHasDefaultValue)
{
    ntt::Integer value("Scores", 5);

    EXPECT_THAT(value.Value(), testing::Eq(5));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerThenItCanRunOnUpdate)
{
    ntt::Integer value("Scores");
    ntt::Timestep ts;

    EXPECT_NO_THROW(value.OnUpdate(ts));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerThenItHasGetName)
{
    ntt::Integer value("Scores");

    EXPECT_THAT(value.GetName(), testing::StrEq("Scores"));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithDefaultMinMax)
{
    ntt::Integer value("Scores", 0, 0, 100);
}

TEST_F(EngineDataTypeTest, IntegerConstructorWithDefaultValueExceedTheLimits)
{
    ntt::Integer value("Scores", 0, 10, 100);

    EXPECT_THAT(value.Value(), 10);
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithStorageThenBeSavedWhenDeleted)
{
    storage_->SetGetIntegerReturn("Scores", 2, 4);
    storage_->IgnoreSetInteger("Scores");

    ntt::Integer value("Scores", 4, 0, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(2));
}

TEST_F(EngineDataTypeTest, TestIntegerChange)
{
    ntt::Integer value("Scores", 4);
    value.SetValue(3);

    EXPECT_THAT(value.Value(), testing::Eq(3));
}

TEST_F(EngineDataTypeTest, TestIntegerChangeValueLessThanMin)
{
    ntt::Integer value("Scores", 10, 10, 100);
    value.SetValue(3);

    EXPECT_THAT(value.Value(), testing::Eq(10));
}

TEST_F(EngineDataTypeTest, SaveValueWhenBeDeleted)
{
    storage_->SetGetIntegerReturn("Scores", 2, 4);
    EXPECT_CALL(*storage_, SaveInteger("Scores", 3));

    {
        ntt::Integer value("Scores", 4, 0, 100, storage_);
        value.SetValue(3);
    }
}

TEST_F(EngineDataTypeTest, GetDataWithExceedTheLimits)
{
    storage_->SetGetIntegerReturn("Scores", 101, 4);
    storage_->IgnoreSetInteger("Scores");

    ntt::Integer value("Scores", 4, 0, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(100));
}

TEST_F(EngineDataTypeTest, GetDataWithLessThanTheLimit)
{
    storage_->SetGetIntegerReturn("Scores", 3, 10);
    storage_->IgnoreSetInteger("Scores");

    ntt::Integer value("Scores", 10, 10, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(10));
}