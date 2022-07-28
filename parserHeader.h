#include <iostream>
#include <sstream>

using namespace std;

void eraser(string& str, short n1, short n2);
short last(string str, short n);
string insert(string str, string aux, short n);
bool checkVal(string str, short n1, short n2);
bool checkOp(string str, short n);
double subExprVal(string str, short n1, short n2);
string subExpr(string str, short n1, short n2);
double expr(string str);

// serve a cancellare la parte appena calcolata
void eraser(string& str, short n1=0, short n2=0){
	str.erase(n1,n2-n1);
}

// serve a separare le sottoespressioni dando l'ultimo indice di ciascuna
short last(string str, short n=0){
	int i=n;
	if(str[i] == '-') i++;
	while(isdigit(str[i])) i++;
	if(str[i] == '.'){
		i++;
		while(isdigit(str[i])) i++;
	}
	switch(str[i]){
		case '+':
        case '-':
        case '*':
        case '/':
        	i++;
        	break;
        default:
        	return i;
	}
	while(isdigit(str[i])) i++;
	if(str[i] == '.'){
		i++;
		while(isdigit(str[i])) i++;
	}
	return i;	
}

// serve a risistemare la stringa
string insert(string str, string aux, short n=0){
	str = aux + str;
	return str;
}

// questo serve a vedere se l'espressione data � un singolo valore
bool checkVal(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
	int i=n1;
	if(str[n1] == '-') i++;
	for(i=i; i<n2; i++){
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
string subExpr(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
    string a = "", b = "";
    double num1, num2;
    char oper = ' ';
    short iter=n1;
    double ret;
    
    if(str[n1] == '-'){
		a += '-';
		iter++;
	}

	while(iter<n2){
		for(iter=iter; isdigit(str[iter]); iter++) a += str[iter];
		if(str[iter] == '.'){
			a += '.';
			for(iter=iter+1; isdigit(str[iter]); iter++) a += str[iter];
		}

		stringstream ss1;
		ss1 << a;
		ss1 >> num1;

		switch(str[iter]){
		case '+':
        case '-':
        case '*':
        case '/':
			oper = str[iter];
        	break;
        default:
        	cerr << "ERRORE: operatore non valido" << endl;
			exit(-1);
		}

		if(str[iter+1] == '-'){
			b += '-';
			iter++;
		}

		for(iter=iter+1; isdigit(str[iter]); iter++) b += str[iter];
		if(str[iter] == '.'){
			b += '.';
			for(iter=iter+1; isdigit(str[iter]); iter++) b += str[iter];
		}

		stringstream ss2;
		ss2 << b;
		ss2 >> num2;
	}

	switch(oper){
		case '+':
			ret = num1+num2;
			break;
        case '-':
			ret = num1-num2;
			break;
        case '*':
			ret = num1*num2;
			break;
        case '/':
			ret = num1/num2;
	}

	stringstream ss;
	ss << ret;
	ss >> str;
	return str;
}

double expr(string str){
	while(!checkVal(str)){
		string aux = subExpr(str,0,last(str));
		eraser(str,0,last(str));
		str = insert(str,aux);
		expr(str);
	}
	return subExprVal(str);
}
