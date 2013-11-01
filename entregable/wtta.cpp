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
	
	for (int i=0;i<4;++i){
		cin >> aux;
	}
	cin >> cores;
	cin.ignore(1024,'\n');
	cin >> palabra;
	
	vector<int> ultVez;
	while (palabra == "LOAD"){
		cantProcesos++;
		cin >> ult;
		ultVez.push_back(ult);
		cin.ignore(1024,'\n');
	}
	
	vector<int> procesos (cantProcesos);
	vector<int> bloques (cantProcesos);
	vector<bool> sumar (cantProcesos);
	
	while (exits != cantProcesos){
		cin >> palabra;
		if (palabra == "CPU"){
			
		}
		else if (palabra == "BLOCK"){
			
		}
		else if (palabra == "UNBLOCK"){
			
		}
		else if (palabra == "EXIT"){

		}
	}	
	
    return 0;
}
