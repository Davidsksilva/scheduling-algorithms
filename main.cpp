#include <iostream>
#include<fstream>
#include <queue>
#include <iomanip>
#include "file.h"
#include "utility.h"
#include "diagrams.h"

using namespace std;

void FCFS(int process [][2],int n)
{
  ordernarProcessosChegada(process,n);
  float medium_return_time=0;
  float medium_response_time=0;
  float medium_waiting_time=0;
  int time_passed= process[0][0];
  for(int i=0;i<n;i++)
  {
    if(process[i][0] > time_passed)
        time_passed+= process[i][0] - time_passed;
    medium_return_time+=time_passed+process[i][1] - process[i][0];
    medium_response_time+=time_passed - process[i][0];
    medium_waiting_time+=time_passed - process[i][0];
    time_passed+=process[i][1];

  }
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;

}
void SJF(int process [][2],int n)
{
    ordernarProcessosChegada(process,n);
    float medium_return_time=0;
    float medium_response_time=0;
    float medium_waiting_time=0;
    int time_passed=0;
    int id=0;

    time_passed=process[0][0];

    while((id=nextProcessSJF(process,n,time_passed)) != -1)
    {
      if(process[id][0] > time_passed)
        time_passed+= process[id][0] - time_passed;
      medium_return_time+=time_passed+process[id][1] - process[id][0];
      medium_response_time+=time_passed - process[id][0];//+ idle;
      medium_waiting_time+=time_passed - process[id][0];//+ idle;
      time_passed+=process[id][1];
      process[id][1]=0;
      }
    medium_return_time/=n;
    medium_response_time/=n;
    medium_waiting_time/=n;

    cout<<"SJF "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
    <<medium_response_time<<" "<<medium_waiting_time<<endl;
}
void RR(int process[][2], int const n)
{
    ordernarProcessosChegada(process,n);
    bool iniciated[n]={false};
    float return_time[n]={0};
    float response_time[n]={0};
    float waiting_time[n]={0};
    int time_passed=0;
    queue <int> processQueue;
    int id=0;
    time_passed=process[0][0];
    int quantum=2;
    processQueue.push(0); // Colocar na fila o primeiro processo a chegar
    while(processLeft(process,n)) // Checa se tem processos a ser finalizado
    {
      if(!processQueue.empty()) // Se a fila de prontos nao estiver vazia
      {
        id= processQueue.front();
        processQueue.pop();

        if(process[id][1] != 0) // Se o processo nao está finalizado
        {
          if(process[id][0] > time_passed) // Se o processo está adiantado no tempo atual
            time_passed+=process[id][0]-time_passed;
          if(iniciated[id] == false) // Se o proceso atual nao foi iniacado ainda
          {
            response_time[id]=time_passed; // Definir o tempo de resposta como tempo atual
            iniciated[id]=true; // Definir o proceso como iniciado
          }
          if(process[id][1] >= quantum) // Se o tempo restante do processo é maior ou igual ao quantum
          {
            process[id][1]-=quantum;
            time_passed+=quantum;
            if(process[id][1]==0)
              return_time[id]=time_passed;
            for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
            {
              if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado
              {
                if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
                {
                  if(!isInQueue(processQueue,i))
                    processQueue.push(i);
                  return_time[i]+=quantum;
                  waiting_time[i]+=quantum;
                }
              }
            }
            if(!isInQueue(processQueue,id))
              processQueue.push(id);
          }
          else // Se o tempo que resta do processo for menor que o quantum
          {
            return_time[id]=time_passed;
            time_passed+=process[id][1];
            for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
            {
              if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado
              {
                if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
                {
                  if(!isInQueue(processQueue,i))
                    processQueue.push(i);
                  return_time[i]+=process[id][1];
                  waiting_time[i]+=process[id][1];
                }
              }
            }
            process[id][1]=0;
          }
      }
    }
    else
    {
      id++;
      processQueue.push(id);
    }
  }

  float medium_response_time=0;
  float medium_waiting_time=0;
  float medium_return_time=0;

  getProcessData(process);
  ordernarProcessosChegada(process,n);

  for(int i=0;i<n;i++)
    {
      return_time[i]-=process[i][0];
      response_time[i]-=process[i][0];
      waiting_time[i]=return_time[i]-process[i][1];
      medium_return_time+=return_time[i];
      medium_response_time+=response_time[i];
      medium_waiting_time+=waiting_time[i];
    }
    medium_waiting_time/=n;
    medium_response_time/=n;
    medium_return_time/=n;

    cout<<"RR "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
    <<medium_response_time<<" "<<medium_waiting_time<<endl;
  }
int main()
{
  int n = getLines();
  int process[n][2];
  getProcessData(process);
  FCFS(process,n);
  getProcessData(process);
  SJF(process,n);
  getProcessData(process);
  RR(process,n);

  return 0;
}
