#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <iostream>
#include<fstream>
#include <queue>
#include <iomanip>
using namespace std;

inline bool isInQueue(queue <int> ProcessQueue,int value)
{
  int aux;
  while(!ProcessQueue.empty())
  {

    aux=ProcessQueue.front();
    ProcessQueue.pop();
    if(aux == value)
      return true;
  }
  return false;
}
inline void ordernarProcessosChegada(int processo[][2],int n)
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
      /*else if((processo[j][0] == processo[a][0]) &&(processo[j][1] < processo[a][1]))
      a=j;*/
		}
		temp[0]= processo[i][0];
    temp[1]= processo[i][1];
		processo[i][0]= processo[a][0];
    processo[i][1]= processo[a][1];
		processo[a][0]= temp[0];
    processo[a][1]= temp[1];
  }
}
inline bool processLeft(int processo[][2],int n)
{
  for(int i=0;i<n;i++)
  {
    if(processo[i][1] != 0)
      return true;
  }
  return false;
}
inline void printProcesses(int processo[][2],int n)
{
  cout<<"Processos:"<<endl;
  for(int i=0;i<n;i++)
  {
      cout<<"["<<i<<"] "<<processo[i][0]<<" "<<processo[i][1]<<endl;
  }
}

inline void transferText(string input,string output)
{
  ifstream infile(input);
  ofstream outfile(output,std::ios::app);
  string content = "";
  int i;

  for(i=0 ; infile.eof()!=true ; i++) // get content of infile
      content += infile.get();

  i--;
  content.erase(content.end()-1);     // erase last character

  infile.close();

  outfile << content;                 // output
  outfile.close();
}

int nextProcessSJF(int process[][2], int n, int t)
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

#endif
