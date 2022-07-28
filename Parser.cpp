#include "parserHeader.h"

int main(){
    string espressione = "";
    cout << "Inserisci espressione:\t";
    cin >> espressione;
    cout << endl << "Il risultato dell'espressione inserita e':\t" << expr("4*-5");
    return 0;
}