#include "PreInclude.hpp"
#include "EngineThreading/WorkPool/Command.hpp"
#include "EngineThreading/WorkPool/Pool.hpp"


class TestCommand: public ntt::Command
{
    public:
        MOCK_METHOD(void, OnExecute, (), (override));
        MOCK_METHOD(bool, IsExecutable, (), (const));

        void IgnoreOnExecute()
        {
            EXPECT_CALL(*this, OnExecute()).Times(testing::AnyNumber());
        }

        void SetIsExecutableAfter(int times)
        {
            testing::Sequence sequence;

            for (int i=0; i<times; i++)
            {
                EXPECT_CALL(*this, IsExecutable())
                            .InSequence(sequence)
                            .WillOnce(testing::Return(false));
            }

            EXPECT_CALL(*this, IsExecutable())
                        .InSequence(sequence)
                        .WillRepeatedly(testing::Return(true));
        }

        static ntt::Ref<TestCommand> CreateRef()
        {
            return std::make_shared<TestCommand>();
        }
};


class EngineThreadPoolTest : public testing::Test
{
    protected:
        void SetUp() override
        {
            workPool = std::make_shared<ntt::WorkPool>("Test Work Pool");
        }

        void TearDown() override
        {

        }

        ntt::Ref<ntt::WorkPool> workPool;
};


TEST_F(EngineThreadPoolTest, TheCommandShouldHaveTheOnExecuteMethod)
{
    auto command = TestCommand::CreateRef();
    command->IgnoreOnExecute();

    EXPECT_NO_THROW(command->OnExecute());
}

TEST_F(EngineThreadPoolTest, TheCommandShouldHaveTheIsExecutable)
{
    auto command = TestCommand::CreateRef();
    command->SetIsExecutableAfter(0);

    EXPECT_NO_THROW(command->IsExecutable());
}

TEST_F(EngineThreadPoolTest, CreateCommandFromFunction)
{
    bool isExecuted = false;

    auto command = ntt::Command::CreateRef([&isExecuted]()
    {
        isExecuted = true;
    });

    command->OnExecute();

    EXPECT_THAT(isExecuted, testing::IsTrue());
}


TEST_F(EngineThreadPoolTest, GivenTheThreadDoesNotHaveAnyCommand_ThenTheThreadDoesNotRun)
{
    EXPECT_THAT(workPool->IsEmpty(), testing::IsTrue());
}

TEST_F(EngineThreadPoolTest, WhenAddANewCommand_ThenThePoolIsNotEmpty)
{
    workPool->AddWork(TestCommand::CreateRef());

    EXPECT_THAT(workPool->IsEmpty(), testing::IsFalse());
}

TEST_F(EngineThreadPoolTest, GivenTheWorkPoolWithACommand_WhenThreadRun_ThenTheCommandIsExecuted)
{
    auto command = TestCommand::CreateRef();
    command->SetIsExecutableAfter(0);
    workPool->AddWork(command);

    EXPECT_CALL(*command, OnExecute()).Times(1);

    workPool->OnRunImpl();
    
    EXPECT_THAT(workPool->IsEmpty(), testing::IsTrue());
}

TEST_F(EngineThreadPoolTest, GivenTheEmptyWorkPool_WhenThreadRun_ThenDoesNotThrowError)
{
    EXPECT_NO_THROW(workPool->OnRunImpl());
}

TEST_F(EngineThreadPoolTest, GivenTheWorkPoolWith2Commands_WhenThreadRun_ThenTheCommandIsExecutedSequentially)
{
    testing::Sequence sequence;

    auto command1 = TestCommand::CreateRef();
    command1->SetIsExecutableAfter(0);
    auto command2 = TestCommand::CreateRef();
    command2->SetIsExecutableAfter(0);
    workPool->AddWork(command1);
    workPool->AddWork(command2);

    EXPECT_CALL(*command1, OnExecute()).Times(1).InSequence(sequence);
    EXPECT_CALL(*command2, OnExecute()).Times(1).InSequence(sequence);

    for (int i=0; i<10; i++)
    {
        workPool->OnRunImpl();
    }
}

TEST_F(EngineThreadPoolTest, GivenTheWorkPoolWith2CommandsAndFirstCommandReturnTrueAtTheSecond_WhenRun_ThenTheFirstCommandIsExecutedAfterTheSecondOne)
{
    testing::Sequence sequence;

    auto command1 = TestCommand::CreateRef();
    command1->SetIsExecutableAfter(1);
    auto command2 = TestCommand::CreateRef();
    command2->SetIsExecutableAfter(0);
    workPool->AddWork(command1);
    workPool->AddWork(command2);

    EXPECT_CALL(*command2, OnExecute()).Times(1).InSequence(sequence);
    EXPECT_CALL(*command1, OnExecute()).Times(1).InSequence(sequence);

    for (int i=0; i<10; i++)
    {
        workPool->OnRunImpl();
    }
}

TEST_F(EngineThreadPoolTest, GivenTheWorkPoolWith3CommandsAndFirstCommandReturnTrueAtTheSecond_WhenRun_ThenTheFirstCommandIsExecutedAfterTheSecondOneAndTheThirdOne)
{
    testing::Sequence sequence;

    auto command1 = TestCommand::CreateRef();
    command1->SetIsExecutableAfter(1);

    auto command2 = TestCommand::CreateRef();
    command2->SetIsExecutableAfter(0);

    auto command3 = TestCommand::CreateRef();
    command3->SetIsExecutableAfter(0);
    workPool->AddWork(command1);
    workPool->AddWork(command2);
    workPool->AddWork(command3);

    EXPECT_CALL(*command2, OnExecute()).Times(1).InSequence(sequence);
    EXPECT_CALL(*command3, OnExecute()).Times(1).InSequence(sequence);
    EXPECT_CALL(*command1, OnExecute()).Times(1).InSequence(sequence);

    for (int i=0; i<10; i++)
    {
        workPool->OnRunImpl();
    }
}

TEST_F(EngineThreadPoolTest, ThePoolIsClearedWhenStart)
{
    auto command = TestCommand::CreateRef();

    workPool->AddWork(command);
    
    workPool->StartImpl();

    EXPECT_THAT(workPool->IsEmpty(), testing::IsTrue());
}

TEST_F(EngineThreadPoolTest, ThePoolIsClearedWhenStop)
{
    auto command = TestCommand::CreateRef();

    workPool->StartImpl();
    workPool->AddWork(command);

    workPool->StopImpl();

    EXPECT_THAT(workPool->IsEmpty(), testing::IsTrue());
}