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
	
	loads = ultVez;
	
	int proximoX;
	int pos;
	
	while (true){
		if (palabra == "CPU"){
			cin >> x;
			cin >> y;
			if (y!=-1){
				cin.clear();
				cin.ignore(1024, '\n');			
				sumar[y]=0;
				cin >> palabra;
				if (palabra == "CPU"){
					pos = cin.tellg();
					cin >> proximoX;
					if (x!=proximoX){
						for (int j=0;j<cantProcesos;++j){
							if (j!=y && sumar[j]==0) bloques[j]++;
							if (j!=y) sumar[j]=1;
							if (sumar[j]==1) procesos[j]++;
						}
					}
					cin.seekg(pos);
				}
			}
			else{
				cin.clear();
				cin.ignore(1024, '\n');							
			}
		}
		else if (palabra == "BLOCK"){
			cin >> y;
			cin.clear();
			cin.ignore(1024,'\n');
			sumar[y]=0;
			cin >> palabra;
		}
		else if (palabra == "UNBLOCK"){
			cin >> aux;
			cin >> y;
			sumar[y]=1;
			cin >> palabra;
		}
		else if (palabra == "EXIT"){
			cin >> x;
			cin >> y;
			cin.clear();
			cin.ignore(1024,'\n');
			loads[y] = x-loads[y];
			exits++;
			if (exits==cantProcesos) break;
			cin >> palabra;
		}
		else{
			cin.clear();
			cin.ignore(10000,'\n');
			cin >> palabra;
			//cout << palabra<<endl;
		}
	}
	double wt=0;
	double ta=0;	
	for (int i=0;i<cantProcesos;++i){
		cout << "Procesos:" << procesos[i] <<endl;
		cout << "Bloques:" <<bloques[i] <<endl;
		wt+=procesos[i]/bloques[i];
		ta+=loads[i];
	}
	wt/=cantProcesos;
	ta/=cantProcesos;
	cout << "Waiting time: " <<wt<<endl;
	cout << "Turnaround time: "<<ta<<endl;
    return 0;
}
