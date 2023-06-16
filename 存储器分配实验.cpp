#include <iostream>

using namespace std;

struct Partition {
    int id;//分区ID 
    int start_address;//起始地址 
    int size;//大小 
    int process_id;//分配的进程ID 
    int end_address;
    int part_size;//内部碎片大小 
};

struct Process {
    int id;//进程ID 
    int size;//进程大小 
};
//内存分配类 
class MemoryAllocationSimulator {
private:
    int total_memory;//总内存 
    Partition partitions[10];//分区数组 
    int partition_count;//分区计数 
    Process processes[10];//进程数组 
    int process_count;//进程计数 

public:
	//初始化 
    MemoryAllocationSimulator(int memory) {
        total_memory = memory;
        partition_count = 0;
        process_count = 0;
    }
    //内存里添加分区 
    void addPartition(int partition_id, int start_address, int size) {
        Partition partition;
        partition.id = partition_id;
        partition.start_address = start_address;
        partition.size = size;
        partition.process_id = -1;//表示无进程 
        partitions[partition_count++] = partition;//将分配的进程存在进程数组里 
    }
    //分配进程 
    void allocateProcess(int process_id, int size) {
        for (int i = 0; i < partition_count; i++) {
            Partition& partition = partitions[i];
            //如果分区的大小大于进程所需大小并且该分组无进程，进入if 
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

                cout << "进程 " << process_id << " 已分配在内存分区 " << partition.id <<" 中 ;"<< endl;
                return;
            }
        }
        cout << "无法分配进程 " << process_id << ", 分区内存不足" << endl;
    }
    //释放进程 
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

                cout << "进程 " << process_id << " 已从分区 " << partition.id<<" 释放 "<< endl;
                return;
            }
        }
        cout << "进程 " << process_id << " 不存在" << endl;
    }

    void showMemoryStatus() {
        cout << "内存状况：" << endl;
        for (int i = 0; i < partition_count; i++) {
            Partition partition = partitions[i];
            if(partition.process_id != -1)
            {
            cout << "分区 " << partition.id << ": ";
            cout << "起始地址: " << partition.start_address << ", ";
            cout << "结束地址: " << partition.end_address <<" ";
            cout << "进程所需大小: " << partition.size << ", ";
            cout << "内部碎片大小: " <<partition.part_size << ", ";
			cout << "内部碎片范围：" <<partition.size << "---" << partition.size + partition.part_size << ", "; 
            }
            else
            {
            	cout<< "分区 " << partition.id << ": ";
            	cout<<"未分配"<< ", ";
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
                cout << "进程ID: " << process_id << ", ";
                cout << "进程大小: " << process_size << ", ";
            } 

            cout << endl;
        }
    }
    

};

int main() {
    MemoryAllocationSimulator simulator(1000);

    // 添加分区
    simulator.addPartition(1, 0, 200);
    simulator.addPartition(2, 200, 300);
    simulator.addPartition(3, 500, 300);
    simulator.addPartition(4, 800, 200);

    // 分配进程
    simulator.allocateProcess(101, 150);
    simulator.allocateProcess(102, 250);
    simulator.allocateProcess(103, 100);
    simulator.allocateProcess(104, 200);
    simulator.allocateProcess(105, 400);

    // 显示内存状态
    simulator.showMemoryStatus();

    // 释放进程
    simulator.deallocateProcess(102);
    simulator.deallocateProcess(105);

    // 再次显示内存状态
    simulator.showMemoryStatus();

    return 0;
}

