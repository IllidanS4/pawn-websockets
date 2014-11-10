#ifndef SYNCHRONIZATION_QUEUE_HPP
#define SYNCHRONIZATION_QUEUE_HPP

#include <queue>
#include <mutex>

#include <boost/optional.hpp>

template<typename T>
class SynchronizationQueue
{
	std::queue<T> m_queue;
	std::mutex m_mutex;

public:
	SynchronizationQueue() { }

	SynchronizationQueue(const SynchronizationQueue&) = delete;
	SynchronizationQueue(SynchronizationQueue&&) = delete;
	SynchronizationQueue& operator=(const SynchronizationQueue&) = delete;

	void operator += (T t)
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		m_queue.push(t);
	}

	boost::optional<T> operator()()
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		if (m_queue.empty())
			return nullptr;

		auto data = m_queue.back();
		m_queue.pop();

		return data;
	}
};

#endif