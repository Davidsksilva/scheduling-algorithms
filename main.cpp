#include <iostream>
#include<fstream>
#include <iomanip>

using namespace std;

int  getLines() // Lê a lista de inteiros do arquivo
{
  std::ifstream f("processos.txt");
  std::string line;
  int lines=0;
  for (int i = 0; std::getline(f, line); ++i)
    lines++;
  return lines;
}

void getProcessData(int processo[][2] ) // Lê a lista de inteiros do arquivo
{
  int aux=0;
  int linha=0;
  int data;
  std::ifstream f("processos.txt");

  while(f >> data)
  {
      aux++;
      if((aux%2)==0)
      {
        processo[linha][1]=data;
        linha++;
      }
      else
      {
        processo[linha][0]=data;

      }
  }

}

void printProcesses(int processo[][2],int n)
{
  cout<<"Processos:"<<endl;
  for(int i=0;i<n;i++)
  {
      cout<<processo[i][0]<<" "<<processo[i][1]<<endl;
  }
}

void ordernarProcessosChegada(int processo[][2],int n)
{
  int a;
  int temp[2];
	for(int i = 0;i < n ;i++)
	{
		a=i;
		for(int j=i+1;j < n;j++)
		{
			if(processo[j][0] < processo[a][0])
				a=j;
		}
		temp[0]= processo[i][0];
    temp[1]= processo[i][1];
		processo[i][0]= processo[a][0];
    processo[i][1]= processo[a][1];
		processo[a][0]= temp[0];
    processo[a][1]= temp[1];
  }
}

void ordernarProcessosDuracao(int processo[][2],int n)
{
  int a;
  int temp[2];
	for(int i = 0;i < n ;i++)
	{
		a=i;
		for(int j=i+1;j < n;j++)
		{
			if(processo[j][1] < processo[a][1])
				a=j;
		}
		temp[0]= processo[i][0];
    temp[1]= processo[i][1];
		processo[i][0]= processo[a][0];
    processo[i][1]= processo[a][1];
		processo[a][0]= temp[0];
    processo[a][1]= temp[1];
  }
}

void FCFS(int processo [][2],int n)
{
  ordernarProcessosChegada(processo,n);
  float tempo_retorno_medio=0;
  int tempo_acumulado=0;
  for(int i=0;i<n;i++)
  {
    tempo_retorno_medio=tempo_acumulado+processo[i][1];
    tempo_acumulado+=processo[i][1];
  }
  tempo_retorno_medio/=n;

  cout<<"FCFS "<<std::setprecision(1)<<tempo_retorno_medio<<endl;
}

int main()
{
  int n;
  n=getLines();
  int processo[n][2];
  getProcessData(processo);
  printProcesses(processo,n);
  FCFS(processo,n);
  //

  return 0;
}
