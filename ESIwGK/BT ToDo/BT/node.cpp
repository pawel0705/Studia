#include "node.h"


ReturnCode Conditional::tick()
{
	return predicate();
}

ReturnCode Action::tick()
{
	return action();
}

ReturnCode Sequence::tick()
{
	//TODO definicja metody
    for (auto& child : this->children)
    {
        ReturnCode code = child->tick();

        if (code == ReturnCode::FAILURE) {
            return ReturnCode::FAILURE;
        }
        else if (code == ReturnCode::RUNNING) {
            return ReturnCode::RUNNING;
        }
    }

	return ReturnCode::SUCCESS;
};

ReturnCode Selector::tick()
{
	//TODO definicja metody
    for (auto& child : this->children)
    {
        ReturnCode code = child->tick();
        if (code == ReturnCode::SUCCESS)
        {
            return ReturnCode::SUCCESS;
        }
        else if (code == ReturnCode::RUNNING) {
            return ReturnCode::RUNNING;
        }
    }

	return ReturnCode::FAILURE;
};