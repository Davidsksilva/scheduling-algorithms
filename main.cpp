#include <iostream>
#include<fstream>
#include <iomanip>
#include "file.h"
#include "utility.h"

using namespace std;

void FCFS(int processo [][2],int n)
{
  ordernarProcessosChegada(processo,n); // Orderna os processos em ordem de chegada na fila de prontos
  int idle=0;
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado= processo[0][0];

  for(int i=0;i<n;i++) // Itera entre os processos em ordem de chegada à fila de prontos
  {
    if(processo[i][0] > tempo_acumulado)//Se o t. de chegada do próximo processo excede o t.  de retorno do último processo a cpu fica em idle
      idle= processo[i][0] - tempo_acumulado;
    tempo_retorno_medio+=tempo_acumulado+processo[i][1]; //T. retorno = tempo que o processo inicia + t. de duracao do processo
    tempo_resposta_medio+=tempo_acumulado - processo[i][0]+ idle;//T. resposta = tempo que o processo inicia - tempo de chegada +
    tempo_espera_medio+=tempo_acumulado - processo[i][0] + idle;

    tempo_acumulado+=processo[i][1];
  }
  tempo_retorno_medio/=n;
  tempo_resposta_medio/=n;
  tempo_espera_medio/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<tempo_retorno_medio<<" "
  <<tempo_resposta_medio<<" "<<tempo_espera_medio<<endl;
}
void FCFScomDiagrama(int processo [][2],int n)
{
  ofstream file,file2;
  file.open ("saidaFCFS.txt");
  file2.open("diagramaFCFS.txt");
  file << "\n\n";
  file2<< "Diagrama do tempo do Escalonamento por FCFS:\n\n";
  file2<< "Legenda do diagrama:\nPn: processo n executado\npn: processo n chegou na fila\nidle= cpu sem processo\n\n";
  ordernarProcessosChegada(processo,n);
  int idle=0;
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado= processo[0][0];
  file2<<"|"<<tempo_acumulado<<"|";
  int traco=0;
  for(int u=0;u<n;u++)
  {
    if(traco == processo[u][0])
      file2<<"p"<<u;
  }
  for(int i=0;i<n;i++)
  {
    if(processo[i][0] > tempo_acumulado)
    {
        idle= processo[i][0] - tempo_acumulado;
        tempo_acumulado+=idle;
        cout<<"ta "<<tempo_acumulado<<endl;
        for(int k=0;k<idle;k++)
        {
          if(k==idle/2)
            file2<<"idle";

          file2<<"-";
          traco++;
          for(int u=0;u<n;u++)
          {
            if(traco == processo[u][0])
              file2<<"p"<<u;
          }
        }
        file2<<"|"<<tempo_acumulado<<"|";

    }
    tempo_retorno_medio+=tempo_acumulado+processo[i][1] - processo[i][0];
    tempo_resposta_medio+=tempo_acumulado - processo[i][0];//+ idle;
    tempo_espera_medio+=tempo_acumulado - processo[i][0];// + idle;

    for(int j=0;j<processo[i][1];j++)
    {
      if(j == processo[i][1]/2)
        file2<<"P"<<i;
      file2<<"-";
      traco++;
      for(int u=0;u<n;u++)
      {
        if(traco == processo[u][0])
          file2<<"p"<<u;
      }
    }

    file<<"P["<<i<<"] "<<processo[i][0]<<" "<<processo[i][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"Tempo de retorno: "<<tempo_acumulado+processo[i][1]-processo[i][0]<<endl
    <<"Tempo de resposta: "<<tempo_acumulado - processo[i][0]+ idle<<endl<<
    "Tempo de espera: "<<tempo_acumulado - processo[i][0] + idle<<endl<<endl;

    tempo_acumulado+=processo[i][1];



  file2<<"|"<<tempo_acumulado+idle<<"|";

  }
  file<<endl<<endl;
  tempo_retorno_medio/=n;
  tempo_resposta_medio/=n;
  tempo_espera_medio/=n;

  cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<tempo_retorno_medio<<" "
  <<tempo_resposta_medio<<" "<<tempo_espera_medio<<endl;

  file<<"Tempo de retorno medio: "<<tempo_retorno_medio<<endl<<"Tempo de resposta medio: "<<
  tempo_resposta_medio<<endl<<"Tempo de espera medio: "<<tempo_espera_medio<<endl;

  file.close();
  file2.close();
  transferText("saidaFCFS.txt","diagramaFCFS.txt");
}
int proximoProcessoSJF(int processo[][2], int n, int t)
{
  int id_min_duration=2147483647;
  if(processLeft(processo,n))
  {
    for(int i=0;i<n;i++)
    {

        if((processo[i][0]<=t) && (processo[i][1]!= 0)) // Se processo disponivel estiver em tempo
        {
          if(id_min_duration==2147483647)
            id_min_duration=i;
          else if(processo[i][1]< processo[id_min_duration][1])
              id_min_duration=i;
        }
    }
    if(id_min_duration == 2147483647) // Se o processo disponivel nao estiver no tempo
    {
      for(int i=0;i<n;i++)
      {
        if((processo[i][0]>t) && (processo[i][1]!= 0)) // Se processo disponivel nao estiver em tempo
        {
          t=processo[i][0];
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
void SJF(int processo [][2],int n)
{
  ordernarProcessosChegada(processo,n);
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado=0;
  int id=0;
  int idle=0;
  tempo_acumulado=processo[0][0];
  while((id=proximoProcessoSJF(processo,n,tempo_acumulado)) != -1)
  {
    if(processo[id][0] > tempo_acumulado)
    {
      idle= processo[id][0] - tempo_acumulado;
    }

    tempo_retorno_medio+=tempo_acumulado+processo[id][1];
    tempo_resposta_medio+=tempo_acumulado - processo[id][0]+ idle;
    tempo_espera_medio+=tempo_acumulado - processo[id][0]+ idle;
    tempo_acumulado+=processo[id][1];
    processo[id][1]=0;
  }
  tempo_retorno_medio/=n;
  tempo_resposta_medio/=n;
  tempo_espera_medio/=n;

  cout<<"SJF "<<std::fixed<<std::setprecision(1)<<tempo_retorno_medio<<" "
  <<tempo_resposta_medio<<" "<<tempo_espera_medio<<endl;
}
void SJFcomDiagrama(int processo [][2],int n)
{
  ofstream file,file2;
  file.open ("saidaSJF.txt");
  file2.open("diagramaSJF.txt");
  file << "\n\n";
  file2<< "Diagrama do tempo do Escalonamento por SJF:\n\n";
  file2<< "Legenda do diagrama:\nPn: processo n executado\npn: processo n chegou na fila\nidle= cpu sem processo\n\n";
  ordernarProcessosChegada(processo,n);
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado=0;
  int id=0;
  int traco=0;
  int idle=0;
  tempo_acumulado=processo[0][0];

  file2<<"|"<<tempo_acumulado<<"|";
  for(int u=0;u<n;u++)
  {
    if(traco == processo[u][0])
      file2<<"p"<<u;
  }
  while((id=proximoProcessoSJF(processo,n,tempo_acumulado)) != -1)
  {
    if(processo[id][0] > tempo_acumulado)
    {
      idle= processo[id][0] - tempo_acumulado;
      tempo_acumulado+=idle;
      for(int k=0;k<idle;k++)
      {
        if(k==idle/2)
          file2<<"idle";
        traco++;
        for(int u=0;u<n;u++)
        {
          if(traco == processo[u][0])
          file2<<"p"<<u;
        }
        file2<<"-";
      }
      file2<<"|"<<tempo_acumulado<<"|";
    }
    tempo_retorno_medio+=tempo_acumulado+processo[id][1] - processo[id][0];
    tempo_resposta_medio+=tempo_acumulado - processo[id][0];//+ idle;
    tempo_espera_medio+=tempo_acumulado - processo[id][0];//+ idle;

    for(int j=0;j<processo[id][1];j++)
    {
      if(j == processo[id][1]/2)
        file2<<"P"<<id;
      file2<<"-";
      traco++;
      for(int u=0;u<n;u++)
      {
        if(traco == processo[u][0])
          file2<<"p"<<u;
      }
    }

    file<<"P["<<id<<"] "<<processo[id][0]<<" "<<processo[id][1]<<endl<<
    std::fixed<<std::setprecision(1)<<"Tempo de retorno: "<<tempo_acumulado+processo[id][1] - processo[id][0]<<endl
    <<"Tempo de resposta: "<<tempo_acumulado - processo[id][0]+ idle<<endl<<
    "Tempo de espera: "<<tempo_acumulado - processo[id][0] + idle<<endl<<endl;

    tempo_acumulado+=processo[id][1];
    processo[id][1]=0;
    file2<<"|"<<tempo_acumulado+idle<<"|";
    }
  file<<endl<<endl;
  tempo_retorno_medio/=n;
  tempo_resposta_medio/=n;
  tempo_espera_medio/=n;

  cout<<"SJF "<<std::fixed<<std::setprecision(1)<<tempo_retorno_medio<<" "
  <<tempo_resposta_medio<<" "<<tempo_espera_medio<<endl;
  file<<"Tempo de retorno medio: "<<tempo_retorno_medio<<endl<<"Tempo de resposta medio: "<<
  tempo_resposta_medio<<endl<<"Tempo de espera medio: "<<tempo_espera_medio<<endl;
  file.close();
  file2.close();
  transferText("saidaSJF.txt","diagramaSJF.txt");
}
int main()
{
  int n;
  n=getLines();
  int processo[n][2];
  getProcessData(processo);
  FCFScomDiagrama(processo,n);
  getProcessData(processo);
  SJFcomDiagrama(processo,n);


  return 0;
}
