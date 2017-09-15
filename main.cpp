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
void FCFS(int processo [][2],int n)
{
  ordernarProcessosChegada(processo,n);
  int idle=0;
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado= processo[0][0];

  for(int i=0;i<n;i++)
  {
    if(processo[i][0] > tempo_acumulado)
        idle= processo[i][0] - tempo_acumulado;
    tempo_retorno_medio+=tempo_acumulado+processo[i][1];
    tempo_resposta_medio+=tempo_acumulado - processo[i][0]+ idle;
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
  ordernarProcessosChegada(processo,n);
  int idle=0;
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado= processo[0][0];

  file2<<"|"<<tempo_acumulado<<"|";

  for(int i=0;i<n;i++)
  {
    if(processo[i][0] > tempo_acumulado)
    {
        idle= processo[i][0] - tempo_acumulado;
        for(int k=0;k<idle;k++)
        {
          if(k==idle/2)
            file2<<"idle";

          file2<<"=";
        }
        file2<<"|"<<idle+tempo_acumulado<<"|";

    }
    tempo_retorno_medio+=tempo_acumulado+processo[i][1];
    tempo_resposta_medio+=tempo_acumulado - processo[i][0]+ idle;
    tempo_espera_medio+=tempo_acumulado - processo[i][0] + idle;

    int linha=0;
    for(int j=0;j<processo[i][1];j++)
    {
      if(j == processo[i][1]/2)
        file2<<"P"<<i;
      file2<<"-";
    }

    file<<"P["<<i<<"] "<<endl<<
    std::fixed<<std::setprecision(1)<<"Tempo de chegada: "<<processo[i][0]<<endl<<
    "Tempo de duracao: "<<processo[i][1]<<endl<<"Tempo de retorno: "<<tempo_acumulado+processo[i][1]<<endl
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
    file.close();
  file2.close();
  transferText("saidaFCFS.txt","diagramaFCFS.txt");
}
int proximoProcessoSJF(int processo[][2], int n, int t)
{
  int id_min_duration=2147483647;
  if(processLeft)
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
  ordernarProcessosChegada(processo,n);
  float tempo_retorno_medio=0;
  float tempo_resposta_medio=0;
  float tempo_espera_medio=0;
  int tempo_acumulado=0;
  int id=0;
  int idle=0;
  tempo_acumulado=processo[0][0];

  file2<<"|"<<tempo_acumulado<<"|";

  while((id=proximoProcessoSJF(processo,n,tempo_acumulado)) != -1)
  {
    if(processo[id][0] > tempo_acumulado)
    {
      idle= processo[id][0] - tempo_acumulado;
      for(int k=0;k<idle;k++)
      {
        if(k==idle/2)
          file2<<"idle";

        file2<<"=";
      }
      file2<<"|"<<idle+tempo_acumulado<<"|";
    }
    tempo_retorno_medio+=tempo_acumulado+processo[id][1];
    tempo_resposta_medio+=tempo_acumulado - processo[id][0]+ idle;
    tempo_espera_medio+=tempo_acumulado - processo[id][0]+ idle;

    int linha=0;
    for(int j=0;j<processo[id][1];j++)
    {
      if(j == processo[id][1]/2)
        file2<<"P"<<id;
      file2<<"-";
    }

    file<<"P["<<id<<"] "<<endl<<
    std::fixed<<std::setprecision(1)<<"Tempo de chegada: "<<processo[id][0]<<endl<<
    "Tempo de duracao: "<<processo[id][1]<<endl<<"Tempo de retorno: "<<tempo_acumulado+processo[id][1]<<endl
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
  SJFcomDiagrama(processo,n);


  return 0;
}
