#include <iostream>
#include <vector>
#include <cassert>
#include <stdio.h>
#include <fstream>

using namespace std;

int main()
{
	string aux;
	string palabra;
	int cantProcesos = 0;
	int exits = 0;
	int ult;
	int cores;
	
	int x;
	int y;
	
	for (int i=0;i<4;++i){
		cin >> aux;
	}

	cin >> cores;
	cin.clear();
    	cin.ignore (10000, '\n' );
  	cin >> palabra;
	vector<int> ultVez;
	
	while (palabra == "LOAD"){
		cantProcesos++;
		cin >> ult;
		ultVez.push_back(ult);
		cin.clear();
		cin.ignore(10000,'\n');
		cin >> palabra;
	}
	
	vector<int> loads (cantProcesos);
	vector<double> procesos (cantProcesos);
	vector<double> bloques (cantProcesos);
	vector<bool> sumar (cantProcesos);
	vector<bool> unblocks (cantProcesos);
	
	for (int i=0;i<cantProcesos;++i){
		if (loads[i] == 0) sumar[i]=1;
	}
	
	loads = ultVez;
	
	int proximoX;
	int pos;
	int aux1;
	int aux2;
	int xAnt;
	int yAnt;
	
	while (true){
		if (palabra == "CPU"){
			cin >> x;
			cin >> y;
			if (x==xAnt && y==yAnt){
				cin.clear();
				cin.ignore(1024, '\n');
				cin >> palabra;
			}
			//if (y==0) cout << "CPU" << x << " " << procesos[0] <<endl;
			else if (y!=-1){
				cin.clear();
				cin.ignore(1024, '\n');
				procesos[y]++;
				if (unblocks[y]==1) unblocks[y]=0;
				if (!sumar[y] && unblocks[y] && ultVez[y]!=x-1 && ultVez[y]!=x){
					unblocks[y]=0;
					bloques[y]++;
					sumar[y]=1;					
				}			
				for (int j=0;j<cantProcesos;++j){
					if (!sumar[j] && ultVez[j]!=x-1 && ultVez[j]!=x){
						bloques[j]++;
						sumar[j]=1;
					}
				}
				sumar[y]=0;
				/*cout<<"Ticks:";
				cout<<bloques[0];
				cout<<" CPU:"<<x<<endl;*/							
				ultVez[y]=x;
				cin >> palabra;
	  /*			if (palabra == "CPU"){
					pos = cin.tellg();
					cin >> proximoX;
					if (x!=proximoX){
						for (int j=0;j<cantProcesos;++j){
							//if (j!=y) sumar[j]=1;
							if (sumar[j]==1) procesos[j]++;
						}
					}
					cin.seekg(pos);
				}*/
			}
			else{
				cin.clear();
				cin.ignore(1024, '\n');	
				cin >> palabra;						
			}
			xAnt=x; yAnt=y;
		}
		else if (palabra == "BLOCK"){
			cin >> aux1;
			cin >> y;
			ultVez[y]=aux1;
			sumar[y]=0;
			cin.clear();
			cin.ignore(1024,'\n');
			cin >> palabra;
		}
		else if (palabra == "UNBLOCK"){
			cin >> aux2;
			cin >> y;
			unblocks[y]=1;
			procesos[y]+=aux2-ultVez[y];
			ultVez[y]=aux2;
			cin >> palabra;
		}
		else if (palabra == "EXIT"){
			cin >> x;
			cin >> y;
			cin.clear();
			cin.ignore(1024,'\n');
			loads[y] = x-loads[y];
			exits++;
			if (exits==cantProcesos){
				bloques[y]++;
				break;
			}
			cin >> palabra;
		}
		else if (palabra == "#"){
			cin.clear();
			cin.ignore(10000,'\n');
			cin >> palabra;
		}
	}
	double wt=0;
	double ta=0;
	double ticks;	
	for (int i=0;i<cantProcesos;++i){
		/*cout << "Proceso: " << i << " ";
		cout << "Ticks:" << loads[i]-procesos[i] <<" ";
		cout << "Bloques:" <<bloques[i] <<endl;*/
		ticks=loads[i]-procesos[i];
		//cout << wt << endl;
		wt+=ticks/bloques[i];
		cout<<"wt:"<<ticks/bloques[i]<<endl;
		//cout<<"pt:"<<procesos[i]<<endl;
		ta+=loads[i];
		cout << "ta:" << loads[i] << endl;
	}
	wt/=cantProcesos;
	ta/=cantProcesos;
	cout << "Waiting time: " <<wt<<endl;
	cout << "Turnaround time: "<<ta<<endl;
    return 0;
}
