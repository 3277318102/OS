#include <iostream>

using namespace std;

struct Partition {
    int id;//����ID 
    int start_address;//��ʼ��ַ 
    int size;//��С 
    int process_id;//����Ľ���ID 
    int end_address;
    int part_size;//�ڲ���Ƭ��С 
};

struct Process {
    int id;//����ID 
    int size;//���̴�С 
};
//�ڴ������ 
class MemoryAllocationSimulator {
private:
    int total_memory;//���ڴ� 
    Partition partitions[10];//�������� 
    int partition_count;//�������� 
    Process processes[10];//�������� 
    int process_count;//���̼��� 

public:
	//��ʼ�� 
    MemoryAllocationSimulator(int memory) {
        total_memory = memory;
        partition_count = 0;
        process_count = 0;
    }
    //�ڴ�����ӷ��� 
    void addPartition(int partition_id, int start_address, int size) {
        Partition partition;
        partition.id = partition_id;
        partition.start_address = start_address;
        partition.size = size;
        partition.process_id = -1;//��ʾ�޽��� 
        partitions[partition_count++] = partition;//������Ľ��̴��ڽ��������� 
    }
    //������� 
    void allocateProcess(int process_id, int size) {
        for (int i = 0; i < partition_count; i++) {
            Partition& partition = partitions[i];
            //��������Ĵ�С���ڽ��������С���Ҹ÷����޽��̣�����if 
            if (partition.size >= size && partition.process_id == -1) {
                Process process;
                process.id = process_id;
                process.size = size;
                processes[process_count++] = process;

                partition.process_id = process_id;
                partition.start_address = 0;
                partition.end_address = partition.start_address + size;
                partition.part_size =partition.size - size;
                partition.size = size;

                cout << "���� " << process_id << " �ѷ������ڴ���� " << partition.id <<" �� ;"<< endl;
                return;
            }
        }
        cout << "�޷�������� " << process_id << ", �����ڴ治��" << endl;
    }
    //�ͷŽ��� 
    void deallocateProcess(int process_id) {
        for (int i = 0; i < partition_count; i++) {
            Partition& partition = partitions[i];
            if (partition.process_id == process_id) {
                partition.process_id = -1;
                int process_size = 0;
                for (int j = 0; j < process_count; j++) {
                    if (processes[j].id == process_id) {
                        process_size = processes[j].size;
                        for (int k = j; k < process_count - 1; k++) {
                            processes[k] = processes[k + 1];
                        }
                        process_count--;
                        break;
                    }
                }
                partition.size += process_size;

                cout << "���� " << process_id << " �Ѵӷ��� " << partition.id<<" �ͷ� "<< endl;
                return;
            }
        }
        cout << "���� " << process_id << " ������" << endl;
    }

    void showMemoryStatus() {
        cout << "�ڴ�״����" << endl;
        for (int i = 0; i < partition_count; i++) {
            Partition partition = partitions[i];
            if(partition.process_id != -1)
            {
            cout << "���� " << partition.id << ": ";
            cout << "��ʼ��ַ: " << partition.start_address << ", ";
            cout << "������ַ: " << partition.end_address <<" ";
            cout << "���������С: " << partition.size << ", ";
            cout << "�ڲ���Ƭ��С: " <<partition.part_size << ", ";
			cout << "�ڲ���Ƭ��Χ��" <<partition.size << "---" << partition.size + partition.part_size << ", "; 
            }
            else
            {
            	cout<< "���� " << partition.id << ": ";
            	cout<<"δ����"<< ", ";
			}
            int process_id = -1;
            int process_size = 0;
            for (int j = 0; j < process_count; j++) {
                if (processes[j].id == partition.process_id) {
                    process_id = processes[j].id;
                    process_size = processes[j].size;
                    break;
                }
            }

            if (process_id != -1) {
                cout << "����ID: " << process_id << ", ";
                cout << "���̴�С: " << process_size << ", ";
            } 

            cout << endl;
        }
    }
    

};

int main() {
    MemoryAllocationSimulator simulator(1000);

    // ��ӷ���
    simulator.addPartition(1, 0, 200);
    simulator.addPartition(2, 200, 300);
    simulator.addPartition(3, 500, 300);
    simulator.addPartition(4, 800, 200);

    // �������
    simulator.allocateProcess(101, 150);
    simulator.allocateProcess(102, 250);
    simulator.allocateProcess(103, 100);
    simulator.allocateProcess(104, 200);
    simulator.allocateProcess(105, 400);

    // ��ʾ�ڴ�״̬
    simulator.showMemoryStatus();

    // �ͷŽ���
    simulator.deallocateProcess(102);
    simulator.deallocateProcess(105);

    // �ٴ���ʾ�ڴ�״̬
    simulator.showMemoryStatus();

    return 0;
}

