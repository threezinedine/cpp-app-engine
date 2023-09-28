#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EngineCores/EngineCores.hpp"
#include "../Thread.hpp"


class ThreadMock: public ntt::Thread
{
    public:
        ThreadMock(int camId)
            : camId_(camId)
        {

        }

        ~ThreadMock()
        {

        }

        MOCK_METHOD(void, StartImpl, (), (override));
        MOCK_METHOD(void, StopImpl, (), (override));
        MOCK_METHOD(void, OnRunImpl, (), (override));
        MOCK_METHOD(bool, IsRunning, (), (const));
        MOCK_METHOD(void, SetRunning, (bool), (override));


        void IgnoreSetRunning()
        {
            EXPECT_CALL(*this, SetRunning(testing::_)).Times(testing::AnyNumber());
        }

        void IgnoreStartImplExpect()
        {
            EXPECT_CALL(*this, StartImpl()).Times(testing::AnyNumber());
        }

        void IgnoreStopImplExpect()
        {
            EXPECT_CALL(*this, StopImpl()).Times(testing::AnyNumber());
        }

        void SetupIsRunningReturnFalseAt(int period)
        {
            testing::Sequence sequence;
            for (int i=0; i<period; i++)
            {
                EXPECT_CALL(*this, IsRunning())
                        .InSequence(sequence)
                        .WillOnce(testing::Return(true));
            }
            EXPECT_CALL(*this, IsRunning())
                        .InSequence(sequence)
                        .WillOnce(testing::Return(false));
        }

        void IgnoreOnRunImpl()
        {
            EXPECT_CALL(*this, OnRunImpl()).Times(testing::AnyNumber());
        }

        static ntt::Ref<ThreadMock> CreateRef(int id)
        {
            return std::make_shared<ThreadMock>(id);
        }

    private:
        int camId_;
};
