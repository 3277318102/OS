/*����������
����ͨ��ʵ�飺ģ��������֮��������ݹ�����ʹ�ù����ڴ���Ϊͨ�Ż��ơ�ÿ�����̿��Զ�ȡ���޸ĺ�д�빲������ݽṹ��ȷ������һ���Ժ���ȷ��
*/
#include <iostream>
#include <windows.h>
using namespace std;
const int BUFFER_SIZE = 9;  // ����������С

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
    // ���������ڴ�
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        nullptr,
        PAGE_READWRITE,
        0,
        sizeof(SharedData),
        TEXT("SharedMemory")
    );
    if (hMapFile == nullptr) {
        cerr << "���������ڴ�ʧ��" << endl;
        return 1;
    }

    // ���ӹ����ڴ�
    SharedData* sharedData = (SharedData*)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(SharedData)
    );
    if (sharedData == nullptr) {
        cerr << "���������ڴ�ʧ��" << endl;
        CloseHandle(hMapFile);
        return 1;
    }
    SharedData(memory);
    // �����������
    sharedData->mutex = CreateMutex(nullptr, FALSE, TEXT("SharedMutex"));
    if (sharedData->mutex == nullptr) {
        cerr << "�����������ʧ��" << endl;
        UnmapViewOfFile(sharedData);
        CloseHandle(hMapFile);
        return 1;
    }

    // ����1���޸Ĺ�������
    WaitForSingleObject(sharedData->mutex, INFINITE);  // �ȴ�������
    cout << "����1�޸ĵĹ����ڴ����ݣ�" << endl;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sharedData->buffer[i] = i * 2;  // �޸Ĺ�������
    }
    ReleaseMutex(sharedData->mutex);  // �ͷŻ�����

    // ��ȡ���������е�����
    WaitForSingleObject(sharedData->mutex, INFINITE);  // �ȴ�������
    cout << "�����ڴ����ݣ� ";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << sharedData->buffer[i] << " ";
    }
    cout << endl;
    ReleaseMutex(sharedData->mutex);  // �ͷŻ�����

    // ����2���޸Ĺ�������
    WaitForSingleObject(sharedData->mutex, INFINITE);  // �ȴ�������
    cout << "����1�޸ĵĹ����ڴ����ݣ�" << endl;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sharedData->buffer[i] = i * 3;  // �޸Ĺ�������
    }
    ReleaseMutex(sharedData->mutex);  // �ͷŻ�����

    // ��ȡ���������е�����
    WaitForSingleObject(sharedData->mutex, INFINITE);  // �ȴ�������
    cout << "�����ڴ����ݣ�";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << sharedData->buffer[i] << " ";
    }
    cout << endl;
    ReleaseMutex(sharedData->mutex);  // �ͷŻ�����

    // �رվ�����ͷ���Դ
    CloseHandle(sharedData->mutex);
    UnmapViewOfFile(sharedData);
    CloseHandle(hMapFile);

    return 0;
}

