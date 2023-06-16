#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
 
//存放每个进程信息的结构体
struct PROCESS{
    char name;
    double AT;//到达时间
    double ST;//服务时间
    double FT;//完成时间
    double WT;//周转时间
};
 
queue<PROCESS>PROCESSqueue;  //用来模拟进程执行RR调度算法的队列
double SumWT=0,AverageWT =0;//平均周转时间、平均带权周转时间
int time_slice;  //时间片
int n;  //进程个数
PROCESS PROCESSarray[100];  //进程结构体
PROCESS temp;//中间变量 

void Input();
void RR() ;
void output() ;

int main(){
	int i,j;
    cout<<"请输入进程个数: ";
    cin>>n;
    
    for (i=0;i<n;i++){
      PROCESSarray[i].name=i+65;//自动将进程名字顺序编号为A、B、C、D、E等
    }
 
    for (i=0;i<n;i++){
      PROCESSarray[i].AT=0;
    }
 
    cout<<"请输入服务时间: ";
    for (i=0;i<n;i++){
      cin>>PROCESSarray[i].ST;
    }
 	
	cout<<"请输入时间片time_slice的大小: ";
    cin>>time_slice;
    
    //根据达时间排序
    for(i=0;i<n;i++) {
        for(j=i+1;j<n;j++) {
            if(PROCESSarray[i].AT > PROCESSarray[j].AT) {
                temp = PROCESSarray[i];
                PROCESSarray[i] = PROCESSarray[j];
                PROCESSarray[j] = temp;
            }
        }
    }
    RR();//调用RR		函数 
    cout<<"ID"<<"\t";
    cout<<"服务时间"<<"\t";
    cout<<"完成时间"<<"\t";
    cout<<"周转时间"<<"\t";
    cout<<"等待时间"<<endl;
    for (int i=0;i<n;i++){
        cout<<PROCESSarray[i].name<<"\t\t";
        cout<<PROCESSarray[i].ST<<"\t\t";
        cout<<PROCESSarray[i].FT<<"\t\t";
        cout<<PROCESSarray[i].WT<<"\t\t";
        cout<<PROCESSarray[i].WT-PROCESSarray[i].ST<<"\t\t"<<endl;
    }
    cout<<"平均周转时间 = "<<setprecision(3)<<AverageWT<<endl;
    double sum=0;
    for(int i=0;i<n;i++)
    {
    	sum+=PROCESSarray[i].WT-PROCESSarray[i].ST;
	}
    cout<<"平均等待时间 = "<<setprecision(3)<<sum/n<<endl;
    return 0;
}
//执行RR调度算法
void RR(){
    char PROCESScessName[100];   //存储每个时间片p对应的进程名称
   	PROCESSqueue.push(PROCESSarray[0]);   //第一个进程进队列
    int CurrentTime=0;//当前时间 
    int tempTime;   //控制CurrentTime的累加时间，当前进程的服务时间小于时间片time_slice的时候，起到重要作用
    int i=1;  
    int a=0; 
    int PROCESScessNumber = 0;   //执行RR算法后，进程的个数 
    int Time[100] ;
    //判断第一个进程的服务时间是否大于时间片，如果大于CurrentTime=time_slice，如果小于CurrentTime=服务时间
    if (PROCESSarray[0].ST>=time_slice)
        CurrentTime = time_slice;
    else
        CurrentTime = PROCESSarray[0].ST;
  
    while(!PROCESSqueue.empty()){
        for (int j=i;j<n;j++){   //使得满足进程的到达时间小于当前时间的进程都进入队列
            if (CurrentTime >= PROCESSarray[j].AT){
                PROCESSqueue.push(PROCESSarray[j]);
                i++;
            }
        }
        //队列首进程进行执行，进程每执行一次，就将其服务时间 -time_slice
        if (PROCESSqueue.front().ST>=time_slice)
            tempTime = time_slice;
        else
            tempTime = PROCESSqueue.front().ST;
            	
        PROCESSqueue.front().ST -= time_slice;  
 
        //将队首进程的名称放入数组中
        PROCESScessName[a]= PROCESSqueue.front().name;
        a++;
        Time[PROCESScessNumber] = tempTime; 
        PROCESScessNumber++;
 
 
        if (PROCESSqueue.front().ST <= 0)  //把执行完的进程退出队列
            PROCESSqueue.pop();   //如果进程的服务时间小于等于，即该进程已经服务完了，将其退队 
        else{
            //将队首移到队尾
            PROCESSqueue.push(PROCESSqueue.front());
            PROCESSqueue.pop();
        }
         CurrentTime += tempTime;
    }
   //进程输出处理   每个时间段对应的执行的进程
 

	int time = Time[0];
	int count = 0;

  
  //计算完成时间
	for (int i=0;i<PROCESScessNumber;i++)
	{
		count = 0;
		while(PROCESSarray[count].name!=PROCESScessName[i] &&count<n)
		{	
			count++ ;
		} 
		PROCESSarray[count].FT=time ;
		if (i<PROCESScessNumber-1)
		{
			time += Time[i+1];
		}
	}
 	
	//周转时间、带权周转时间、平均周转时间、带权平均周转时间的计算
    for (int i=0;i<n;i++){
        PROCESSarray[i].WT = PROCESSarray[i].FT - PROCESSarray[i].AT;
    }
 
    for (int i=0;i<n;i++){
        SumWT += PROCESSarray[i].WT;
    }
    AverageWT = SumWT/n;
}
 
