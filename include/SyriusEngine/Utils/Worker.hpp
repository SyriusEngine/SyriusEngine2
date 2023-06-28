#pragma once

#include "../Debug.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

namespace Syrius{

    class SR_API Worker{
    public:
        Worker();

        ~Worker();

        void start();

        void stop();

        template<typename... Args>
        void pushTask(Args&&... args) {
            SR_PRECONDITION(m_Running, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Worker is not running");

            {
                std::lock_guard<std::mutex> lk(m_Mutex);
                m_Queue.push_back(std::bind(std::forward<Args>(args)...));
            }

            m_Condition.notify_all();
        }

        template<typename... Args>
        void pushTaskSync(Args&&... args) {
            SR_PRECONDITION(m_Running, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Worker is not running");
            SR_PRECONDITION(m_Thread.get_id() != std::this_thread::get_id(), SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Cannot push synchronized task from worker thread to itself");

            bool isTaskFinished = false;

            {
                std::lock_guard<std::mutex> lk(m_Mutex);
                m_Queue.push_back([func = std::bind(std::forward<Args>(args)...), &isTaskFinished]() {
                    func();
                    isTaskFinished = true;
                });
            }

            m_Condition.notify_all();

            while (!isTaskFinished) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        [[nodiscard]] bool isRunning() const;

        [[nodiscard]] bool hasTasks() const;

        [[nodiscard]] Size getTaskCount() const;

        [[nodiscard]] std::thread::id getThreadId() const;

    private:

        void privateStart();

    private:
        std::condition_variable m_Condition;
        std::list<std::function<void()>> m_Queue;
        std::mutex m_Mutex;
        std::thread m_Thread;
        bool m_Running = false;
    };

}