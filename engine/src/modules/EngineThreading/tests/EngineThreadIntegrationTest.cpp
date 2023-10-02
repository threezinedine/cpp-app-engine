#include "PreInclude.hpp"
#include "EngineThreading/Thread.hpp"
#include "EngineThreading/Lock.hpp"
#include "EngineThreading/LockArray.hpp"
#include "EngineDataType/EngineDataType.hpp"


static ntt::Ref<ntt::Data<int>> value 
            = std::make_shared<ntt::Data<int>>("ThreadingTestVariable", 0, 0, 60000);
static ntt::Ref<ntt::Data<int>> count
            = std::make_shared<ntt::Data<int>>("Count Variable", 0, 0, 510000);
static ntt::Ref<ntt::Data<int>> num
            = std::make_shared<ntt::Data<int>>("Num", 0, 0, 510000);



class IntegrationThread: public ntt::Thread
{
    public:
        IntegrationThread(const char* name)
            : ntt::Thread(name), index_(0)
        {

        }

        ~IntegrationThread()
        {

        }

        void StartImpl() override
        {

        }

        void OnRunImpl() override
        {
            if (index_ < 1000)
            {
                ntt::Lock lock(value);
                value->SetValue(value->Value() + 1);
            }
            index_ ++;
        }

        void StopImpl() override
        {

        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {

        }

    protected:
        int index_ = 0;
};


class MultpleLockThread: public IntegrationThread
{
    public:
        MultpleLockThread(const char* name)
            : IntegrationThread(name)
        {

        }

        ~MultpleLockThread()
        {

        }

        void OnRunImpl() override
        {
            if (index_ < 1000)
            {
                ntt::LockArray lock { count, num };
                count->SetValue(count->Value() + 1);
                num->SetValue(num->Value() + 1);
            }
            index_ ++;
        }
};


class EngineThreadingIntegraionTest: public testing::Test
{
    protected:
        void SetUp() override
        {

        }

        void TearDown() override
        {

        }
};


TEST_F(EngineThreadingIntegraionTest, LockingVariableWillTurnOnTheMutex)
{
    IntegrationThread t1("Testing Thread");

    t1.Start();

    for (int i=0; i<50000; i++)
    {
        ntt::Lock lock(value);
        value->SetValue(value->Value() + 1);
    }

    t1.Stop();

    EXPECT_THAT(value->Value(), testing::Eq(51000));
}

TEST_F(EngineThreadingIntegraionTest, LockingMultipleVariablesWillTurnOnTheMutexesAndTurnOffInAFixedOrder)
{
    MultpleLockThread t1("Testing Thread 1");

    t1.Start();

    for (int i=0; i<500000; i++)
    {
        ntt::LockArray lock { count, num };
        count->SetValue(count->Value() + 1);
        num->SetValue(num->Value() + 1);
    }

    t1.Stop();

    EXPECT_THAT(count->Value(), testing::Eq(501000));
    EXPECT_THAT(num->Value(), testing::Eq(501000));
}