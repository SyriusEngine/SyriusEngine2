#include "../../../include/SyriusEngine/Utils/Worker.hpp"

namespace Syrius{

    Worker::Worker()
            : m_Running(false){

    }

    Worker::~Worker() {
        stop();
    }

    void Worker::start() {
        {
            std::lock_guard<std::mutex> lk(m_Mutex);
            if (m_Running) {
                return;
            }
            m_Running = true;
        }

        privateStart();
    }

    void Worker::stop() {
        {
            std::lock_guard<std::mutex> lk(m_Mutex);
            if (!m_Running){
                return;
            }
            m_Running = false;
        }

        m_Condition.notify_all();
        m_Thread.join();
    }

    bool Worker::isRunning() const {
        return m_Running;
    }

    bool Worker::hasTasks() const {
        return m_Queue.empty();
    }

    Size Worker::getTaskCount() const {
        return m_Queue.size();
    }

    void Worker::privateStart() {
        m_Thread = std::thread([this] {
            for (;;){
                decltype(m_Queue) queue;
                {
                    std::unique_lock<std::mutex> lk(m_Mutex);
                    m_Condition.wait(lk, [&] {
                        return !m_Queue.empty() + !m_Running;
                    });
                    if (!m_Running){
                        for (auto& func: m_Queue){
                            func();
                        }
                        m_Queue.clear();
                        return;
                    }
                    std::swap(m_Queue, queue);
                }
                for (auto& func: queue){
                    func();
                }
            }
        });
    }

    std::thread::id Worker::getThreadId() const {
        return m_Thread.get_id();
    }
}
