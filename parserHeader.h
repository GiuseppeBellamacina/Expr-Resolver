#include <iostream>
#include <sstream>

using namespace std;

bool checkVal(string str, short n1=0, short n2=0);
bool checkOp(string str, short n);
double subExprVal(string str, short n1=0, short n2=0);
double subExpr(string str, short n1=0, short n2=0);
double expr(string str);


// questo serve a vedere se l'espressione data è un singolo valore
bool checkVal(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
	for(int i=n1; i<n2; i++){
		if(str[n1] == '-') continue;
		if(str[i] == '.') continue;
		if(!isdigit(str[i])) return false;	
	}
	return true;
}

// questo serve a vedere le precedenze degli operatori
bool checkOp(string str, short n){
    for(int i=n+1; i<str.length(); i++){
        if(str[i] == '*' || str[i] == '/')
            return true;
    }
    return false;
}

// questa e' la sottoespressione a valore singolo
double subExprVal(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
	string a = "";
	double num;
	short iter = n1;
	
	for(iter=n1; iter<n2; iter++)
		a += str[iter];
	
	stringstream ss;
    ss << a;
    ss >> num;
    
    return num;
}

// serve a eseguire le operazioni elementari tra 2 operandi
double subExpr(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
    string a = "", b = "";
    double num1, num2;
    char oper = ' ';
    short iter=n1;
    
    if(str[n1] == '-'){
		a += '-';
		iter++;
	}
  
	for(iter=iter; (isdigit(str[iter])) || (str[iter] == '.'); iter++)
		a += str[iter];
    
	stringstream ss1;
    ss1 << a;
    ss1 >> num1;
    
	switch (str[iter]){
        case '+':
        case '-':
        case '*':
        case '/':
			oper = str[iter];
			break;
		default:
			cerr << "ERRORE" << endl << "d" <<str[iter] << "d";
			exit(-1);
    }
    
    for(iter=iter+1; iter<n2; iter++){
    	if(!isdigit(str[iter])){
    		if(str[iter] == '.' || str[iter] == '-'){
				b += str[iter];
				continue;
			}
    		cerr << "ERRORE" << endl;
			exit(-1);
    	}
    	else b += str[iter];
	}
	
    stringstream ss2;
    ss2 << b;
    ss2 >> num2;
    
    switch((char)oper){
        case '+':
            return num1+num2;
    	case '-':
            return num1-num2;
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
    }
}

double expr(string str){
	// sistemare la cosa degli indici
	// serve un eraser
	// serve un linker
	// vedere come fare le precendenze
	// chiamate ricorsive per le ()
}
