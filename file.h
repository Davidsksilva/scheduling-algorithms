#ifndef _FILE_H_
#define _FILE_H_
#include <iostream>
#include<fstream>
#include "utility.h"
inline int  getLines() // Lê a lista de inteiros do arquivo
{
  std::ifstream f("processos.txt");
  std::string line;
  int lines=0;
  for (int i = 0; std::getline(f, line); ++i)
    lines++;
  return lines;
}
inline void getProcessData(int processo[][2] ) // Lê a lista de inteiros do arquivo
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

#endif /*_FILE_H_*/
