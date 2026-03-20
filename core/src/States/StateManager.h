#pragma once
#include "ExpressionTree.h"
#include <vector>
#include <memory>
#include <iterator>
#include "States/StateRecordable.h"

template<typename T> 
class StateManager
{
public:
    StateManager(std::shared_ptr<T> initial_state);
    std::weak_ptr<T> GetLastState()const;
    std::weak_ptr<T> GetFirstState()const;
    std::weak_ptr<T> GetCurrentState()const;
    std::weak_ptr<T> GetNextState()const;
    std::weak_ptr<T> GetPreviousState()const;


    void SaveState();
private:
    std::vector<std::shared_ptr<StateRecordable>> m_states;
    mutable size_t m_currentStateIndex = 0;
    std::weak_ptr<StateRecordable> m_objectPointer;
};

template<typename T>
inline StateManager<T>::StateManager(std::shared_ptr<T> initial_state)
{
    static_assert(std::is_base_of<StateRecordable, T>::value, "T must inherit StateRecordable");

    this->m_objectPointer = initial_state;
}

template<typename T>
inline std::weak_ptr<T> StateManager<T>::GetLastState()const
{
    return std::dynamic_pointer_cast<T>(*this->m_states.end());
}

template<typename T>
inline std::weak_ptr<T> StateManager<T>::GetFirstState()const
{
    return std::dynamic_pointer_cast<T>(*this->m_states.begin());
}

template<typename T>
inline std::weak_ptr<T> StateManager<T>::GetCurrentState()const
{
    return this->GetLastState();
}



template<typename T>
inline void StateManager<T>::SaveState()
{
    if (auto initial_state_shared_cast = this->m_objectPointer.lock())
    {
        this->m_states.push_back(initial_state_shared_cast->RecordState());
    }

}

template<typename T>
inline std::weak_ptr<T> StateManager<T>::GetNextState()const
{
    auto result = std::dynamic_pointer_cast<T>(this->m_states.at(m_currentStateIndex));
    if (this->m_currentStateIndex < this->m_states.size() - 1)
    {
        this->m_currentStateIndex++;
    }
    return result;
}

template<typename T>
inline std::weak_ptr<T> StateManager<T>::GetPreviousState() const
{
    auto result = std::dynamic_pointer_cast<T>(this->m_states.at(m_currentStateIndex));

    if (this->m_currentStateIndex > 0)
    {
        this->m_currentStateIndex--;
    }

    return result;
}
