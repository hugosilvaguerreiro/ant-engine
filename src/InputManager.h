//
// Created by huguntu on 10/05/21.
//

#ifndef ANT_ENGINE_INPUTMANAGER_H
#define ANT_ENGINE_INPUTMANAGER_H

#include <iostream>       // std::cout
#include <ostream>
#include <thread>         // std::thread
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <ncurses.h>
#include "nodes/Node.h"

namespace antEngine {

    class InputManager {

    public:
        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;

        std::unique_ptr<std::thread> m_thread;
        std::queue<std::shared_ptr<Event>> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::string THREAD_NAME;
        bool should_exit;


        /// Constructor
        inline InputManager(std::string threadName) :  m_queue(), m_mutex(), m_cv(), THREAD_NAME(std::move(threadName)), should_exit(false) {}

        /// Destructor
        inline ~InputManager() {}

        inline void PutEvent(Event* ev) {
            if (m_thread != nullptr)  {
                // Create a new ThreadMsg
                std::shared_ptr<Event> event(ev);

                // Add user data msg to queue and notify worker thread
                //std::unique_lock<std::mutex> lk(m_mutex);

                m_mutex.lock();

                m_queue.push(event);

                m_mutex.unlock();
            }
        }

        inline std::shared_ptr<Event> GetEvent() {
            if (m_thread != nullptr)  {

                // Add user data msg to queue and notify worker thread
                //std::unique_lock<std::mutex> lk(m_mutex);
                std::shared_ptr<Event> ev;
                m_mutex.lock();
                {
                    ev = m_queue.front();
                    m_queue.pop();
                }
                m_mutex.unlock();
                return ev;
            }
            return nullptr;
        }

        inline void Work() {
            initscr();

            while(!should_exit) {
                char ch = getch();

                Event* ev = new Event();
                ev->key_pressed = ch;
                this->PutEvent(ev);

                /*Event* ev = new Event();
                ev->key_pressed = ch;
                this->PutEvent(ev);*/
            }
        }

        inline bool HasEvents() {
            return !this->m_queue.empty();
        }

        inline bool Start() {
            this->should_exit=false;

            if (!m_thread)
                this->m_thread = std::unique_ptr<std::thread>(new std::thread(&InputManager::Work, this));
            return true;
        }

        inline void Stop() {
            if (!m_thread)
                return;
            this->should_exit = true;

            m_thread->join();
            m_thread = nullptr;
        }
    };
}


#endif //ANT_ENGINE_INPUTMANAGER_H
