#include "parserHeader.h"

int main(){
    string espressione = "";
    fstream file;

    cout << "Inserisci espressione:\t";
    cin >> espressione;
    cout << endl << "Il risultato dell'espressione inserita e':\t" << expr(espressione, file);
    return 0;
}