#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

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
	if(str[i] == '-') i++;
	while(isdigit(str[i])) i++;
	if(str[i] == '.'){
		i++;
		while(isdigit(str[i])) i++;
	}
	return i;	
}

// serve a risistemare la stringa
string insert(string str, string aux, short n=0){
	if(n==0){
		str = aux + str;
	}
	else{
		string a = str.substr(0,n);
		str.erase(0,n);
		str = a + aux + str;
	}
	return str;
}

// questo serve a vedere se l'espressione data e' un singolo valore
bool checkVal(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
	int i=n1;
	while(str[i] == '-') i++;
	for(i=i; i<n2; i++){
		if(str[i] == '.') continue;
		if(!isdigit(str[i])) return false;	
	}
	return true;
}

// questo serve a vedere le precedenze degli operatori
short checkOp(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
    for(int i=n1; i<n2; i++){
        if(str[i] == '*' || str[i] == '/')
            return i;
    }
    return -1;
}

// serve a tornare la posizione da cui far partire la sottoespressione
short findSub(string str, int n, int n1=0, int n2=0){
	short iter = checkOp(str,n1,n2)-1;
	while(isdigit(str[iter])) iter--;
	if(str[iter] == '.'){
		iter--;
		while(isdigit(str[iter])) iter--;
	}
	return iter+1;
}

// questa e' la sottoespressione a valore singolo
string subExprVal(string str, short n1=0, short n2=0){
	if(!n2) n2 = str.length();
	string a = "";
	bool br = false;
	str = str.substr(n1, n2-n1);
	int i=str.length()-1;

	while(isdigit(str[i])) i--;
	if(str[i] == '.'){
		i--;
		while(isdigit(str[i])) i--;
	}

	a = str.substr(i+1);
	stringstream ss;
	ss << a;
	double aux;
	ss >> aux;

	str.erase(i+1);
	if(str.length()%2) aux = -aux;

	stringstream ss1;
	ss1 << aux;
	ss1 >> str;
	return str;
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

//serve a stampare i passaggi
void print(fstream& file, string str, bool output, bool print_file){
	if(!(output || print_file)) return;
	if(checkVal(str)){
		if(str[0]=='-' && str[1]=='-'){
			if(print_file) file << str << "=" << endl;
			if(output) cout << str << "=" << endl;
		}
		else{
			if(print_file) file << str << endl;
			if(output) cout << str << endl;
		}
	}
	else{
		if(print_file) file << str << "=" << endl;
		if(output) cout << str << "=" << endl;
	}
	if(file.fail()){
		cerr << "Errore durante la scrittura su file" << endl;
		exit(-1);
	}
}

// serve a dare il nome al file
string setName(string str){
	string ret = "Expr_";
	for(int i=0; i<str.length(); i++){
		switch(str[i]){
			case '*':
				ret += 'x';
				break;
			case '/':
				ret += 'v';
				break;
			default: ret += str[i];
		}
	}
	ret += ".txt";
	return ret;
}

// controlla se ci sono le parentesi
bool checkPar(string str){
	for(int i=0; i<str.length(); i++)
		if(str[i] == '(') return true;
	return false;
}

// serve a trovare gli indici delle parentesi corrispondenti
short* parHandler(string str){
	short* ret = new short[2];
	short f=0;
	for(int i=0; i<str.length(); i++){
		if(str[i] == '('){
			ret[0] = i;
			f = i+1;
		}
	}
	for(int i=f; i<str.length(); i++){
		if(str[i] == ')'){
			ret[1] = i;
			break;
		}
	}
	return ret;
}

// serva a cancellare le parentesi dopo il calcolo
string parDel(string str, short n1, short n2){
	string aux = subExprVal(str,n1+1,n2);
	eraser(str,n1,n2+1);
	str = insert(str,aux,n1);
	return str;
}

// si tratta della funzione principale
double expr(string str, fstream& file, bool output=false, bool print_file=false){
	if(print_file){
		string name = setName(str);
		file.open(name, fstream::out | fstream::app);
		if(!file){
			cerr << "Errore nella creazione del file" << endl;
			exit(-1);
		}
	}
	print(file,str,output,print_file);

	while(checkPar(str)){
		short* par = parHandler(str);
		
		while(checkOp(str,par[0]+1,par[1]) != -1){
			short n = findSub(str,checkOp(str,par[0]+1,par[1]),par[0]+1,par[1]);
			string aux = subExpr(str,n,last(str,n));
			eraser(str,n,last(str,n));
			str = insert(str,aux,n);
			par = parHandler(str);
			print(file,str,output,print_file);
		}

		while(!checkVal(str,par[0]+1,par[1])){
			short n = par[0]+1;
			string aux = subExpr(str,n,last(str,n));
			eraser(str,n,last(str,n));
			str = insert(str,aux,n);
			par = parHandler(str);
			print(file,str,output,print_file);
		}

		par = parHandler(str);
		str = parDel(str,par[0],par[1]);
		print(file,str,output,print_file);
	}

	while(checkOp(str) != -1){
		short n = findSub(str,checkOp(str));
		string aux = subExpr(str,n,last(str,n));
		eraser(str,n,last(str,n));
		str = insert(str,aux,n);
		print(file,str,output,print_file);
	}

	while(!checkVal(str)){
		string aux = subExpr(str,0,last(str));
		eraser(str,0,last(str));
		str = insert(str,aux);
		if(checkVal(str)) print(file,str,output,print_file);
		else print(file,str,output,print_file);
	}
	
	string aux = str;
	double ret;
	str = subExprVal(str);
	if(str != aux) print(file,str,output,print_file);

	stringstream ss;
	ss << str;
	ss >> ret;
	if(print_file) file.close();
	if(!output) cout << ret << endl;

	return ret;
}