#include "parserHeader.h"

int main(){
    string espressione = "";
    fstream file;

    cout << "Inserisci espressione:\t";
    cin >> espressione;
    cout << endl << "Risoluzione espressione:" << endl << endl;
    expr(espressione,file,true,true);
    cout << endl;
    system("pause");
    return 0;
}
