// ZombieProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string pidStr("17396");
    if (argc == 2) {
        pidStr = argv[1];
    }

    DWORD pid = atoi(pidStr.c_str());
    if (DebugActiveProcess(pid)) 
    {
        DEBUG_EVENT debugEvent;
        while (WaitForDebugEvent(&debugEvent, INFINITE)) {
            std::cout << "debug process:" << pidStr.c_str() << std::endl;
            // 当进程退出时，不调用ContinueDebugEvent
            if (debugEvent.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
                std::cout << "Process exited, keeping as zombie..." << std::endl;
                // 保持调试状态，进程不会完全退出
                while (true) Sleep(1000);
            }
            ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
        }
    } 
    else
    {
        std::cout << "can't find process:" << pidStr.c_str() << std::endl;
    }
    std::cout << "exit..." << pidStr.c_str() << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
