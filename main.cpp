#include <iostream>
#include<fstream>

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
int main()
{
  int n;
  n=getLines();
  int processo[n][2];
  getProcessData(processo);
  printProcesses(processo,n);

  return 0;
}
