#include <iostream>
#include <vector>
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
  	cout <<palabra;
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
	vector<int> procesos (cantProcesos);
	vector<int> bloques (cantProcesos);
	vector<bool> sumar (cantProcesos);
	
	loads = ultVez;
	
	while (exits != cantProcesos){
		//cout<<"entre"<<endl;
		//cin >> palabra;
		if (palabra == "CPU"){
			for (int i=0;i<cores;i++){
				cin >> x;
				cin >> y;
				if (y==-1) break;
				cin.clear();
				cin.ignore(1024, '\n');				
				sumar[y]=0;
				if (ultVez[y] != x+1) bloques[y]++;
				for (int j=0;j<cantProcesos;++j){
					if (j!=y){
						sumar[j]=1;
					}
				}
				for (int j=0;j<cantProcesos;++j){
					if (sumar[j]==1) procesos[j]++;
				}
				cin >> palabra;
				if (palabra != "CPU") break;
				cout << palabra<<endl;
			}
		}
		if (palabra == "BLOCK"){
			cin >> y;
			cin.clear();
			cin.ignore(1024,'\n');
			sumar[y]=0;
			cin >> palabra;
			cout << palabra<<endl;
		}
		if (palabra == "UNBLOCK"){
			cin >> aux;
			cin >> y;
			sumar[y]=1;
			cin >> palabra;
			cout << palabra<<endl;
		}
		if (palabra == "EXIT"){
			cout << "entre en exit"<<endl;
			cin >> x;
			cin >> y;
			cin.clear();
			cin.ignore(1024,'\n');
			loads[y] = x-loads[y];
			exits++;
			cout <<"Proceso: "<< y << " exits: "<<exits<<endl;			
			cin >> palabra;
			cout << palabra<<endl;
		}
		else{
			cin.clear();
			cin.ignore(10000,'\n');
			cin >> palabra;
			cout << palabra<<endl;
		}
	}
	int wt=0;
	int ta=0;	
	for (int i=0;i<cantProcesos;++i){
		wt+=procesos[i]/bloques[i];
		ta+=loads[i];
	}
	wt/=cantProcesos;
	ta/=cantProcesos;
	cout << "Waiting time: " <<wt<<endl;
	cout << "Turnaround time: "<<ta<<endl;
    return 0;
}
