#include "parserHeader.h"

int main(){
    string espressione = "";
    fstream file;

    cout << "Inserisci espressione:\t";
    cin >> espressione;
    cout << endl << "Risoluzione espressione:" << endl;
    expr(espressione,file);
    return 0;
}