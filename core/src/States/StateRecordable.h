#pragma once
#include <memory>

class StateRecordable
{
public:
    virtual std::shared_ptr<StateRecordable> RecordState() = 0;
};