#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <iostream>
#include<fstream>
#include <iomanip>
using namespace std;

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
      else if((processo[j][0] == processo[a][0]) &&(processo[j][1] < processo[a][1]))
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

bool processLeft(int processo[][2],int n)
{
  for(int i=0;i<n;i++)
  {
    if(processo[i][1] != 0)
      return true;
  }
  return false;
}
void printProcesses(int processo[][2],int n)
{
  cout<<"Processos:"<<endl;
  for(int i=0;i<n;i++)
  {
      cout<<"["<<i<<"] "<<processo[i][0]<<" "<<processo[i][1]<<endl;
  }
}

void transferText(string input,string output)
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





#endif
