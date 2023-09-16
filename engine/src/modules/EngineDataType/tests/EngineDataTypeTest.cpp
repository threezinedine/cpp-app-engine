#include "PreInclude.hpp"
#include "EngineDataType/EngineDataType.hpp"
#include "EngineCores/EngineCores.hpp"


class DataStorageMocking: public ntt::DataStorage
{
    public:
        MOCK_METHOD(void, SaveInteger, (const char*, int), (override));
        MOCK_METHOD(int, GetInteger, (const char*), (override));

        static ntt::Ref<DataStorageMocking> CreateRef()
        {
            return std::make_shared<DataStorageMocking>();
        }

        void SetGetIntegerReturn(int value)
        {
            ON_CALL(*this, GetInteger(testing::_))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetInteger(testing::_)).Times(testing::AnyNumber());
        }
};


class EngineDataTypeTest: public testing::Test
{
    protected:
        void SetUp() override
        {
            storage_ = DataStorageMocking::CreateRef();
        }

        void TearDown() override
        {

        }

        ntt::Ref<DataStorageMocking> storage_;
};


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

TEST_F(EngineDataTypeTest, GivenAnIntegerWithStorageThenBeSavedWhenDeleted)
{
    storage_->SetGetIntegerReturn(2);
    EXPECT_CALL(*storage_, SaveInteger("Scores", 2));

    {
        ntt::Integer value("Scores", 4, 0, 100, storage_);

        EXPECT_THAT(value.Value(), testing::Eq(2));
    }
}