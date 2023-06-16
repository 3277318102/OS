/*问题描述：
进程通信实验：模拟多个进程之间进行数据共享，并使用共享内存作为通信机制。每个进程可以读取、修改和写入共享的数据结构，确保数据一致性和正确性
*/
#include <iostream>
#include <windows.h>
using namespace std;
const int BUFFER_SIZE = 9;  // 共享缓冲区大小

struct SharedData {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    HANDLE mutex;

    SharedData() : in(0), out(0), mutex(nullptr) {
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            buffer[i] = 0;
        }
    }
};
int main() {
    // 创建共享内存
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        nullptr,
        PAGE_READWRITE,
        0,
        sizeof(SharedData),
        TEXT("SharedMemory")
    );
    if (hMapFile == nullptr) {
        cerr << "创建共享内存失败" << endl;
        return 1;
    }

    // 附加共享内存
    SharedData* sharedData = (SharedData*)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(SharedData)
    );
    if (sharedData == nullptr) {
        cerr << "创建共享内存失败" << endl;
        CloseHandle(hMapFile);
        return 1;
    }
    SharedData(memory);
    // 创建互斥对象
    sharedData->mutex = CreateMutex(nullptr, FALSE, TEXT("SharedMutex"));
    if (sharedData->mutex == nullptr) {
        cerr << "创建互斥对象失败" << endl;
        UnmapViewOfFile(sharedData);
        CloseHandle(hMapFile);
        return 1;
    }

    // 进程1：修改共享数据
    WaitForSingleObject(sharedData->mutex, INFINITE);  // 等待互斥锁
    cout << "进程1修改的共享内存数据：" << endl;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sharedData->buffer[i] = i * 2;  // 修改共享数据
    }
    ReleaseMutex(sharedData->mutex);  // 释放互斥锁

    // 读取共享缓冲区中的数据
    WaitForSingleObject(sharedData->mutex, INFINITE);  // 等待互斥锁
    cout << "共享内存数据： ";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << sharedData->buffer[i] << " ";
    }
    cout << endl;
    ReleaseMutex(sharedData->mutex);  // 释放互斥锁

    // 进程2：修改共享数据
    WaitForSingleObject(sharedData->mutex, INFINITE);  // 等待互斥锁
    cout << "进程1修改的共享内存数据：" << endl;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sharedData->buffer[i] = i * 3;  // 修改共享数据
    }
    ReleaseMutex(sharedData->mutex);  // 释放互斥锁

    // 读取共享缓冲区中的数据
    WaitForSingleObject(sharedData->mutex, INFINITE);  // 等待互斥锁
    cout << "共享内存数据：";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << sharedData->buffer[i] << " ";
    }
    cout << endl;
    ReleaseMutex(sharedData->mutex);  // 释放互斥锁

    // 关闭句柄和释放资源
    CloseHandle(sharedData->mutex);
    UnmapViewOfFile(sharedData);
    CloseHandle(hMapFile);

    return 0;
}

