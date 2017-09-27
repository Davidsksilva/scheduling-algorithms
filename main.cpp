#include <iostream>
#include<fstream>
#include <queue>
#include <iomanip>
#include "file.h"
#include "utility.h"

using namespace std;

void FCFS(int process [][2],int n)
{
  ordernarProcessosChegada(process,n); // Orderna os processs em ordem of chegada na fila of prontos
  int idle=0;
  float medium_return_time=0;
  float medium_response_time=0;
  float medium_waiting_time=0;
  int time_passed= process[0][0];

  for(int i=0;i<n;i++) // Itera entre os processs em ordem of chegada à fila of prontos
  {
    if(process[i][0] > time_passed)//Se o t. of chegada do próximo process excede o t.  of return do último process a cpu fica em idle
      idle= process[i][0] - time_passed;
    medium_return_time+=time_passed+process[i][1]; //T. return = time que o process inicia + t. of duracao do process
    medium_response_time+=time_passed - process[i][0]+ idle;//T. resposta = time que o process inicia - time of chegada +
    medium_waiting_time+=time_passed - process[i][0] + idle;

    time_passed+=process[i][1];
  }
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;
}
static void FCFScomDiagrama(int process [][2],int n)
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
  int traco=0;
  for(int u=0;u<n;u++)
  {
    if(traco == process[u][0])
      file2<<"p"<<u;
  }
  for(int i=0;i<n;i++)
  {
    if(process[i][0] > time_passed)
    {
        idle= process[i][0] - time_passed;
        time_passed+=idle;
        cout<<"ta "<<time_passed<<endl;
        for(int k=0;k<idle;k++)
        {
          if(k==idle/2)
            file2<<"idle";

          file2<<"-";
          traco++;
          for(int u=0;u<n;u++)
          {
            if(traco == process[u][0])
              file2<<"p"<<u;
          }
        }
        file2<<"|"<<time_passed<<"|";

    }
    medium_return_time+=time_passed+process[i][1] - process[i][0];
    medium_response_time+=time_passed - process[i][0];//+ idle;
    medium_waiting_time+=time_passed - process[i][0];// + idle;

    for(int j=0;j<process[i][1];j++)
    {
      if(j == process[i][1]/2)
        file2<<"P"<<i;
      file2<<"-";
      traco++;
      for(int u=0;u<n;u++)
      {
        if(traco == process[u][0])
          file2<<"p"<<u;
      }
    }

    file<<"P["<<i<<"] "<<process[i][0]<<" "<<process[i][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of retorno: "<<time_passed+process[i][1]-process[i][0]<<endl
    <<"time of return: "<<time_passed - process[i][0]+ idle<<endl<<
    "time of espera: "<<time_passed - process[i][0] + idle<<endl<<endl;

    time_passed+=process[i][1];



  file2<<"|"<<time_passed+idle<<"|";

  }
  file<<endl<<endl;
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;

  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"time of espera medio: "<<medium_waiting_time<<endl;

  file.close();
  file2.close();
  transferText("saidaFCFS.txt","diagramaFCFS.txt");
}
static int proximoprocessSJF(int process[][2], int n, int t)
{
  int id_min_duration=2147483647;
  if(processLeft(process,n))
  {
    for(int i=0;i<n;i++)
    {

        if((process[i][0]<=t) && (process[i][1]!= 0)) // Se process disponivel estiver em time
        {
          if(id_min_duration==2147483647)
            id_min_duration=i;
          else if(process[i][1]< process[id_min_duration][1])
              id_min_duration=i;
        }
    }
    if(id_min_duration == 2147483647) // Se o process disponivel nao estiver no time
    {
      for(int i=0;i<n;i++)
      {
        if((process[i][0]>t) && (process[i][1]!= 0)) // Se process disponivel nao estiver em time
        {
          t=process[i][0];
          id_min_duration=i;
        }

      }

    }
  }
  if(id_min_duration==2147483647)
    return -1;
  else
   return id_min_duration;
}
void SJF(int process [][2],int n)
{
  ordernarProcessosChegada(process,n);
  float medium_return_time=0;
  float medium_response_time=0;
  float medium_waiting_time=0;
  int time_passed=0;
  int id=0;
  int idle=0;
  time_passed=process[0][0];
  while((id=proximoprocessSJF(process,n,time_passed)) != -1)
  {
    if(process[id][0] > time_passed)
    {
      idle= process[id][0] - time_passed;
    }

    medium_return_time+=time_passed+process[id][1];
    medium_response_time+=time_passed - process[id][0]+ idle;
    medium_waiting_time+=time_passed - process[id][0]+ idle;
    time_passed+=process[id][1];
    process[id][1]=0;
  }
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"SJF "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;
}
static void SJFcomDiagrama(int process [][2],int n)
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
  int traco=0;
  int idle=0;
  time_passed=process[0][0];

  file2<<"|"<<time_passed<<"|";
  for(int u=0;u<n;u++)
  {
    if(traco == process[u][0])
      file2<<"p"<<u;
  }
  while((id=proximoprocessSJF(process,n,time_passed)) != -1)
  {
    if(process[id][0] > time_passed)
    {
      idle= process[id][0] - time_passed;
      time_passed+=idle;
      for(int k=0;k<idle;k++)
      {
        if(k==idle/2)
          file2<<"idle";
        traco++;
        for(int u=0;u<n;u++)
        {
          if(traco == process[u][0])
          file2<<"p"<<u;
        }
        file2<<"-";
      }
      file2<<"|"<<time_passed<<"|";
    }
    medium_return_time+=time_passed+process[id][1] - process[id][0];
    medium_response_time+=time_passed - process[id][0];//+ idle;
    medium_waiting_time+=time_passed - process[id][0];//+ idle;

    for(int j=0;j<process[id][1];j++)
    {
      if(j == process[id][1]/2)
        file2<<"P"<<id;
      file2<<"-";
      traco++;
      for(int u=0;u<n;u++)
      {
        if(traco == process[u][0])
          file2<<"p"<<u;
      }
    }

    file<<"P["<<id<<"] "<<process[id][0]<<" "<<process[id][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of retorno: "<<time_passed+process[id][1] - process[id][0]<<endl
    <<"time of return: "<<time_passed - process[id][0]+ idle<<endl<<
    "time of espera: "<<time_passed - process[id][0] + idle<<endl<<endl;

    time_passed+=process[id][1];
    process[id][1]=0;
    file2<<"|"<<time_passed+idle<<"|";
    }
  file<<endl<<endl;
  medium_return_time/=n;
  medium_response_time/=n;
  medium_waiting_time/=n;

  cout<<"SJF "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;
  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"time of espera medio: "<<medium_waiting_time<<endl;
  file.close();
  file2.close();
  transferText("saidaSJF.txt","diagramaSJF.txt");
}
void RR(int process[][2], int const n)
{
  ordernarProcessosChegada(process,n);
  bool iniciated[n]={false};
  float return_time[n]={0};
  float response_time[n]={0};
  float waiting_time[n]={0};
  int time_passed=0;
  int id=0;
  int idle=0;
  time_passed=process[0][0];
  int const quantum=2;
  while(processLeft(process,n)) // Checa se tem process a ser finalizado
  {
    if(process[id][1] != 0) // Se o processo atual nao estiver finalizado
    {
    if(process[id][0] > time_passed) // Se o process atual nao estiver na fila
    {
      for(int j=0;j<n;j++)
      {
        if((process[j][0] <=time_passed)&&(process[j][1] != 0)) // Procura processs na fila
        {
          id=j; // Escalona esse process
          break;
        }
      }
      /* Se nao tiver processs na fila, pular o time*/
      if(process[id][0] > time_passed)
      {
        idle=process[id][0]-time_passed;
        time_passed+=idle;
      }

    }

    for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
    {
      if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado

      {
        if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
        {
          return_time[i]+=quantum;
          waiting_time[i]+=quantum;
        }

      }
    }
    if(process[id][1] != 0) // Se o procesos ainda nao finalizou ( resta time )
    {
      if(iniciated[id] == false)
      {
        response_time[id]=time_passed;
        iniciated[id]=true;
      }
      if(process[id][1] > quantum)
      {
        return_time[id]+=2;
        process[id][1]-=quantum;
        time_passed+=quantum;
      }
      else
      {
        return_time[id]+=process[id][1];
        time_passed+=process[id][1];
        process[id][1]=0;
      }
    }
  }
    if(id == (n-1)) // Se o while tiver no ultimo process, reiniciar o loop, senao incrementar id
      id=0;
    else
      id++;
  }
  float medium_response_time=0;
  float medium_waiting_time=0;
  float medium_return_time=0;
  for(int i=0;i<n;i++)
  {
    cout<<"process: "<<i<<" time of retorno: "<<return_time[i]<<endl;
    response_time[i]-=process[i][0];
    waiting_time[i]-=process[i][0];
    return_time[i]-=process[i][0];
    medium_return_time+=return_time[i];
    medium_response_time+=response_time[i];
    medium_waiting_time+=waiting_time[i];
  }
  //cout<<"time return medio: "<<"time of return: "<<medium_return_time<<endl;
  medium_waiting_time/=n;
  medium_response_time/=n;
  medium_return_time/=n;

  cout<<"RR "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;


}
static void RRcomDiagrama(int process[][2], int n)
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
  int traco=0;
  int idle=0;
  time_passed=process[0][0];
  int quantum=2;
  file2<<"|"<<time_passed<<"|";
  for(int u=0;u<n;u++)
  {
    if(traco == process[u][0])
      file2<<"p"<<u;
  }
  /*for(int i=0;i<n;i++)
  {
    if(process[i][0] <= time_passed)
      processQueue.push(i);
  }*/
  processQueue.push(0);
  while(processLeft(process,n)) // Checa se tem process sem ser finalizado
  {
    if(!processQueue.empty())
    {
      id= processQueue.front();
      processQueue.pop();
    }

    if(process[id][1] != 0)
    {
    if(process[id][0] > time_passed)
    {
      for(int j=0;j<n;j++)
      {
        if((process[j][0] <=time_passed)&&(process[j][1] != 0)) // Procura processs na fila que nao foram finalizados
        {
          id=j; // Escalona esse process
          break;
        }
      }
      idle=process[id][0]-time_passed;
      time_passed+=idle;
      for(int k=0;k<idle;k++)
      {
        if(k==idle/2)
          file2<<"idle";
        traco++;
        for(int u=0;u<n;u++)
        {
          if(traco == process[u][0])
          file2<<"p"<<u;
        }
        file2<<"-";
      }
      file2<<"|"<<time_passed<<"|";
    }

    if(process[id][1] != 0) // Se o procesos ainda nao finalizou ( resta time )
    {
      if(iniciated[id] == false)
      {
        response_time[id]=time_passed;
        iniciated[id]=true;
      }
      if(process[id][1] >= quantum)
      {
        for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
        {
          if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado

          {
            if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
            {
              return_time[i]+=quantum;
              waiting_time[i]+=quantum;
            }

          }
        }
        return_time[id]+=quantum;
        process[id][1]-=quantum;
        time_passed+=quantum;
        if(process[id][1]==0)
          return_time[id]=time_passed;
        //cout<<"P"<<id<<" left "<<process[id][1]<<" to run"<< " time "<<time_passed<<endl;
        for(int j=0;j<quantum;j++)
        {
          if(j == quantum/2)
            file2<<"P"<<id;
          file2<<"-";
          traco++;
          for(int u=0;u<n;u++)
          {
            if(traco == process[u][0])
              file2<<"p"<<u;
          }
        }
        for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
        {
          if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado

          {
            if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
            {
              if(!isInQueue(processQueue,i))
                processQueue.push(i);
            }

          }
        }
        file2<<"|"<<time_passed<<"|";
      }
      else
      {
        return_time[id]+=process[id][1];
        time_passed+=process[id][1];
        for(int j=0;j<process[id][1];j++)
        {
          if(j == (process[id][1]/2)-1)
            file2<<"P"<<id;
          file2<<"-";
          traco++;
          for(int u=0;u<n;u++)
          {
            if(traco == process[u][0])
              file2<<"p"<<u;
          }
        }
        file2<<"|"<<time_passed<<"|";
        for(int i=0;i<n;i++) // Quando nao é o process da vez, incrementar time of espera deles
        {
          if((process[i][0] <= time_passed)&&(process[i][1] != 0)) // Se o process tiver chegado ate aqui e nao estiver finalizado

          {
            if(i != id) // Se nao for o process a ser escalonado no instante, incrementar o time of espera
            {
              return_time[i]+=process[id][1];
              waiting_time[i]+=process[id][1];
            }

          }
        }
        process[id][1]=0;
      }
    }
  }
    /*if(id == (n-1)) // Se o while tiver no ultimo process, reiniciar o loop, senao incrementar id
      id=0;
    else
      id++;*/
  }
  float medium_response_time=0;
  float medium_waiting_time=0;
  float medium_return_time=0;
  getProcessData(process);
  ordernarProcessosChegada(process,n);
  for(int i=0;i<n;i++)
  {
    file<<"P["<<i<<"] "<<process[i][0]<<" "<<process[i][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"time of return: "<<return_time[i]<<endl
    <<"time of response: "<<response_time[i]<<endl<<
    "time of espera: "<<waiting_time[i]<<endl<<endl;
    return_time[i]-=process[i][0];
    response_time[i]-=process[i][0];
  //  waiting_time[i]-=process[i][0];
    waiting_time[i]=return_time[i]-process[i][1];
    medium_return_time+=return_time[i];
    medium_response_time+=response_time[i];
    medium_waiting_time+=waiting_time[i];
  }
  //cout<<"time return medio: "<<"time of return: "<<medium_return_time<<endl;
  medium_waiting_time/=n;
  medium_response_time/=n;
  medium_return_time/=n;

  cout<<"RR "<<std::fixed<<std::setprecision(1)<<medium_return_time<<" "
  <<medium_response_time<<" "<<medium_waiting_time<<endl;

  file<<"time of return medio: "<<medium_return_time<<endl<<"time of resposta medio: "<<
  medium_response_time<<endl<<"time of espera medio: "<<medium_waiting_time<<endl;
  file.close();
  file2.close();
  transferText("saidaRR.txt","diagramaRR.txt");


}
int main()
{
  int n;
  n=getLines();
  int process[n][2];
  getProcessData(process);
  FCFScomDiagrama(process,n);
  getProcessData(process);
  SJFcomDiagrama(process,n);
  getProcessData(process);
  RRcomDiagrama(process,n);

  return 0;
}
