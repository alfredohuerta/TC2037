#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

void lexerAritmetico(string archivo) {
  fstream pruebas;
  string resultados;
  vector<char>::iterator it;
  pruebas.open(archivo, ios::in);


  while(getline(pruebas, resultados)){
    //regex regex_variables("[a-zA-Z][a-zA-Z_0-9]* | [+-][0-9]+|[+-][0-9]+[\\.][0-9]+ | [+-][0-9]+[\\.][0-9]+[e-E][0-9]+ | [\\*\\/\\^\\=\\+\\-] | [\\(\\)] | [\\/\\/");
    cout << "0" << endl;
    regex regex_exponencial("[+-][0-9]+[\\.][0-9]+[eE][0-9]+");
    cout << "1" << endl;
    regex regex_numeros("[+-][0-9]+|[+-][0-9]+[\\.][0-9]+");
    cout << "2" << endl;
    regex regex_comentarios("[\\/\\/][a-zA-Z]*[0-9]*[\\!]*[\\/n]");
    cout << "3" << endl;
    regex regex_operadores("[\\*\\/\\^\\=\\+\\-]");
    cout << "4" << endl;
    regex regex_especiales("[\\(\\)]");
    cout << "5" << endl;
    regex regex_variables("[a-zA-Z][a-zA-Z_0-9]*");
    cout << "4" << endl;

    break;
  }

}



int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }

  lexerAritmetico(argv[1]);

  return 0;
}
