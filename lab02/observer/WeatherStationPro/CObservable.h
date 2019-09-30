#pragma once
#include "pch.h"
#include "IObservable.h"

template <typename T>
struct PrioritySetCompare
{
	bool operator()(const std::pair<T, size_t>& rp, const std::pair<T, size_t>& lp) const
	{
		return rp.first != lp.first && (rp.second < lp.second || (rp.second == lp.second  && rp.first < lp.first));
	}
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, size_t priority) override
	{
		m_observers.insert(std::make_pair(&observer, priority));
	}

	void NotifyObservers() override
	{
		ClearRemoveList();
		T data = GetChangedData();
		for (auto& observer : m_observers)
		{
			observer.first->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_removeList.insert(&observer);
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::set<std::pair<ObserverType*, size_t>, PrioritySetCompare<ObserverType*>> m_observers;
	std::set<ObserverType*> m_removeList;

	void ClearRemoveList()
	{
		for (auto& observer : m_removeList)
		{
			std::pair<ObserverType*, size_t> val(observer, NULL);
			m_observers.erase(val);
		}
		m_removeList.clear();
	}
};
