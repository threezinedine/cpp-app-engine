#pragma once
#include <iostream>
#include <string>
#include "PreInclude.hpp"
#include "InputType.hpp"


namespace ntt
{
    class TimeStep;

    class DataTypeBase
    {
        public:
            DataTypeBase(const char* name);

            virtual ~DataTypeBase();

            inline virtual const char* GetName() const { return name_; }

            virtual void OnUpdate(Timestep ts, InputType type = NONE, void* args = nullptr) = 0;
            virtual std::string ToString() const = 0;

            friend std::ostream& operator<< (std::ostream& os, const DataTypeBase& obj)
            {
                os << obj.ToString() << std::endl;
                return os;
            }

        private:
            const char* name_;
    }; 
} // namespace ntt
