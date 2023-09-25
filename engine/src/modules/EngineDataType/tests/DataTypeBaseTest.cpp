#include "PreInclude.hpp"
#include "EngineDataType/DataTypeBase.hpp"


struct DataTypeDerivedOptions
{
    int value;
    float score;
};


class DataTypeDerived: public ntt::DataTypeBase
{
    public:
        DataTypeDerived(const char* name)
            : ntt::DataTypeBase(name)
        {

        }

        ~DataTypeDerived() override
        {

        }

        bool OnUpdate(ntt::Timestep ts, ntt::InputType type, void* args = nullptr) override
        {
            return true;
        }

        std::string ToString() const
        {
            return GetName();
        }
};


TEST_F(EngineDataTypeTest, DataTypeBaseHasTheGetName)
{
    DataTypeDerived data("Hello");

    EXPECT_THAT(data.GetName(), testing::StrEq("Hello"));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedWillHaveTheVirtualMethodForOnUpdate)
{
    ntt::Timestep ts;
    DataTypeDerived data("Hello");

    EXPECT_NO_THROW(data.OnUpdate(ts, ntt::NONE));
}
TEST_F(EngineDataTypeTest, DataTypeDerivedWithOptions)
{
    ntt::Timestep ts;
    DataTypeDerivedOptions options { 3, 4.5f };
    DataTypeDerived data("Hello");

    EXPECT_NO_THROW(data.OnUpdate(ts, ntt::NONE, (void*)&options));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedToString)
{
    DataTypeDerived data("Hello");

    EXPECT_THAT(data.ToString(), "Hello");
}

TEST_F(EngineDataTypeTest, DataTypeDerivedIsCouted)
{
    DataTypeDerived data("Hello");

    EXPECT_NO_THROW(std::cout << data << std::endl);
}