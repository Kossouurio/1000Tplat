#include "Thread.h"

Thread::Thread() : m_Thread(nullptr), m_Function(nullptr), m_Running(false) {
}

Thread::~Thread() {
    if (m_Thread) {
        CloseHandle(m_Thread);
        std::cout << "------------------------------------------" << std::endl;
		std::cout << "Thread Destruction : success." << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
}

void Thread::Start(std::function<void()> func) {
    m_Function = func;
    m_Running = true;
    m_Thread = CreateThread(nullptr, 0, Static_ThreadProc, this, 0, nullptr);
    if (m_Thread == nullptr) {
        std::cout << "------------------------------------------" << std::endl;
        std::cerr << "Thread Creation : failed." << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        m_Running = false;
    }
    else {
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Thread Creation : success." << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
}

bool Thread::IsRunning() const {
    return m_Running;
}

DWORD WINAPI Thread::Static_ThreadProc(LPVOID lpParameter) {
    Thread* thread = static_cast<Thread*>(lpParameter);
    if (thread->m_Function) {
        thread->m_Function();
    }

    thread->m_Running = false; 
    delete thread; 

    return 0;
}