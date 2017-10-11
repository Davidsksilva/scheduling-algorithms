#ifndef _DIAGRAMS_H_
#define _DIAGRAMS_H_
#include "utility.h"
#include "file.h"

void FCFScomDiagrama(int process [][2],int n)
{
  ofstream file,file2;
  file.open ("saidaFCFS.txt");
  file2.open("diagramaFCFS.txt");
  file << "\n\n";
  file2<< "Diagrama do time do Escalonamento por FCFS:\n\n";
  file2<< "Legenda do diagrama:\nPn: process n executado\npn: process n chegou na fila\nidle= cpu sem process\n\n";
  ordernarProcessosChegada(process,n);
  int idle=0;
  float medium_return_time=0;
  float medium_response_time=0;
  float medium_waiting_time=0;
  int time_passed= process[0][0];
  file2<<"|"<<time_passed<<"|";
  int trace=0;
  for(int u=0;u<n;u++)
  {
    if(trace == process[u][0])
      file2<<"p"<<u;
  }
  for(int i=0;i<n;i++)
  {
    if(process[i][0] > time_passed)
    {
        time_passed= process[i][0];
        file2<<"|"<<time_passed<<"|";

    }
    medium_return_time+=time_passed+process[i][1] - process[i][0];
    medium_response_time+=time_passed - process[i][0];//+ idle;
    medium_waiting_time+=time_passed - process[i][0];// + idle;

    for(int j=0;j<process[i][1];j++)
    {
      if(j == 0)
        file2<<"P"<<i;
      //file2<<"-";
      trace++;
    }

    file<<"P["<<i<<"] "<<process[i][0]<<" "<<process[i][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of retorno: "<<time_passed+process[i][1]-process[i][0]<<endl
    <<"time of response: "<<time_passed - process[i][0]+ idle<<endl<<
    "waiting time: "<<time_passed - process[i][0] + idle<<endl<<endl;

    time_passed+=process[i][1];



  file2<<"|"<<time_passed<<"|";

  }
  file<<endl<<endl;
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;

  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"waiting time medio: "<<medium_waiting_time<<endl;

  file.close();
  file2.close();
  transferText("saidaFCFS.txt","diagramaFCFS.txt");
}

void SJFcomDiagrama(int process [][2],int n)
{
  ofstream file,file2;
  file.open ("saidaSJF.txt");
  file2.open("diagramaSJF.txt");
  file << "\n\n";
  file2<< "Diagrama do time do Escalonamento por SJF:\n\n";
  file2<< "Legenda do diagrama:\nPn: process n executado\npn: process n chegou na fila\nidle= cpu sem process\n\n";
  ordernarProcessosChegada(process,n);
  float medium_return_time=0;
  float medium_response_time=0;
  float medium_waiting_time=0;
  int time_passed=0;
  int id=0;
  int trace=0;
  int idle=0;
  time_passed=process[0][0];

  file2<<"|"<<time_passed<<"|";

  while((id=nextProcessSJF(process,n,time_passed)) != -1)
  {
    if(process[id][0] > time_passed)
    {
      time_passed= process[id][0];// - time_passed;
      file2<<"|"<<time_passed<<"|";
    }
    medium_return_time+= time_passed+process[id][1] - process[id][0];
    medium_response_time+=time_passed - process[id][0];//+ idle;
    medium_waiting_time+=time_passed - process[id][0];//+ idle;

    for(int j=0;j<process[id][1];j++)
    {
      if(j == 0)
        file2<<"P"<<id;
      //file2<<"-";
      trace++;
    }

    file<<"P["<<id<<"] "<<process[id][0]<<" "<<process[id][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of retorno: "<<time_passed+process[id][1] - process[id][0]<<endl
    <<"time of response: "<<time_passed - process[id][0]+ idle<<endl<<
    "waiting time: "<<time_passed - process[id][0] + idle<<endl<<endl;

    time_passed+=process[id][1];
    process[id][1]=0;
    file2<<"|"<<time_passed<<"|";
    }
  file<<endl<<endl;
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"SJF "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;
  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"waiting time medio: "<<medium_waiting_time<<endl;
  file.close();
  file2.close();
  transferText("saidaSJF.txt","diagramaSJF.txt");
}

void RRcomDiagrama(int process[][2], int n)
{
  ofstream file,file2;
  file.open ("saidaRR.txt");
  file2.open("diagramaRR.txt");
  file << "\n\n";
  file2<< "Diagrama do time do Escalonamento por RR:\n\n";
  file2<< "Legenda do diagrama:\nPn: process n executado\npn: process n chegou na fila\nidle= cpu sem process\n\n";
  ordernarProcessosChegada(process,n);
  bool iniciated[n]={false};
  float return_time[n]={0};
  float response_time[n]={0};
  float waiting_time[n]={0};
  int time_passed=0;
  queue <int> processQueue;
  int id=0;
  int trace=0;
  time_passed=process[0][0];
  int quantum=2;
  file2<<"|"<<time_passed<<"|";
  processQueue.push(0); // Colocar na fila o primeiro processo a chegar
  while(processLeft(process,n)) // Checa se tem processos a ser finalizado
  {
    if(!processQueue.empty()) // Se a fila de prontos nao estiver vazia
    {
      id= processQueue.front();
      processQueue.pop();
    }
    if(process[id][1] != 0) // Se o processo nao está finalizado
    {
    if(process[id][0] > time_passed) // Se o processo está adiantado no tempo atual
    {
      time_passed=process[id][0];
      //idle=process[id][0]-time_passed;
      //time_passed+=idle;
      file2<<"|"<<time_passed<<"|";
    }

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
      for(int j=0;j<quantum;j++)
      {
        if(j == 0)
          file2<<"P"<<id;
        //file2<<"-";
        trace++;
      }
      for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar waiting time deles
      {
        if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado
        {
          if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o waiting time
          {
            if(!isInQueue(processQueue,i))
              processQueue.push(i);
            //waiting_time[i]+=quantum;
          }
        }
      }
      if(!isInQueue(processQueue,id))
        processQueue.push(id);
      file2<<"|"<<time_passed<<"|";
      }
      else
      {
        //return_time[id]+=process[id][1];
        time_passed+=process[id][1];
        for(int j=0;j<process[id][1];j++)
        {
          if(j == 0)
            file2<<"P"<<id;
          //file2<<"-";
          trace++;
        }
        file2<<"|"<<time_passed<<"|";
        for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar waiting time deles
        {
          if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado

          {
            if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o waiting time
            {
              if(!isInQueue(processQueue,i))
                processQueue.push(i);
              //waiting_time[i]+=process[id][1];
            }

          }
        }
        return_time[id]=time_passed;
        process[id][1]=0;
      }

  }
  else
  {
    id++;
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
    //waiting_time[i]-=process[i][0];
    waiting_time[i]=return_time[i]-process[i][1];
    medium_return_time+=return_time[i];
    medium_response_time+=response_time[i];
    medium_waiting_time+=waiting_time[i];

    file<<"P["<<i<<"] "<<process[i][0]<<" "<<process[i][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of return: "<<return_time[i]<<endl
    <<"time of response: "<<response_time[i]<<endl<<
    "waiting time: "<<waiting_time[i]<<endl<<endl;
  }
  //cout<<"time return medio: "<<"time of return: "<<medium_return_time<<endl;
  medium_waiting_time/=n;
  medium_response_time/=n;
  medium_return_time/=n;

  cout<<"RR "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;

  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"waiting time medio: "<<medium_waiting_time<<endl;
  file.close();
  file2.close();
  transferText("saidaRR.txt","diagramaRR.txt");
}

#endif
