#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

const int TREADS = 4;

void resaltadorSecuencial(string archivo) {
  fstream pruebas;
  string resultados;
  vector<char>::iterator it;
  pruebas.open(archivo, ios::in);


  while(getline(pruebas, resultados)){
    string encabezado = "<!DOCTYPE html><html lang='esp-mx'> <head> <meta charset='UTF-8'> <title>Resaltador de sintaxis</title> <style>body{color: beige;}.PReservadas{color: blue;}.Variables{color: blueviolet;}.Operadores{color: aqua;}.Reales{color: chartreuse;}.Especiales{color: crimson;}.Comentarios{color: gold;}</style> </head> <body>";

    // definimos los operadores aritmeticos
    string variable = "[a-zA-Z][a-zA-Z_0-9]*";
    string operadores = "[\\*|\\/|\\^|\\=|\\+|\\-]";
    string reales = "-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?"; /* con los () y ? decimos que eso puede o 
                                                                              no estar en la funcion establecida*/
    string especiales = "[\\(\\)]";
    string comentarios = " //.*$"; //. cualquier elemento  y el $ indica que continua hasta llegar al final de la linea 
    string reservadas = "alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq";

    // solo debemos tener un regex, entonces juntamos las strings anteriores
    regex regex_tokens(variable +"|"+ operadores +"|"+ reales +"|"+ especiales +"|"+ comentarios); /* +"|"+ ees variable
                                                                                     OR operador y el + es para agregar*/

    // definimos nuestro iterador para ir recorriendo y buscar en regex los tokens
   auto inicio_arch = 
        // iterador para ir recorriendo match por match y detectarlos en regex_tokens
        std::sregex_iterator(resultados.begin(), resultados.end(), regex_tokens); /*leer de resultados incio a 
                                                                                    resultados final */
    auto fin_arch = std::sregex_iterator(); // cuando ya no tenga mas elementos se deja de leer 

    // vamos a ir leyendo caracter x caracter, al detectar su token, pasamos al siguiente carcater
    for (std::sregex_iterator i = inicio_arch; i != fin_arch; ++i) {
      std::smatch match = *i; // con el * lo desreferencia, desapuntador                                               
      std::string caracter = match.str(); // lo convertimos a string

      /*ya que tebemos el string, vemos si esta hace match con el regex, que basta solo con poner regex ya que se llama 
      al constructor*/
      if(regex_match(caracter, regex(variable))){
        encabezado = "<div class= 'Variables'>Variable: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(reales))){
        encabezado = "<div class= 'Reales'>Número real: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(comentarios))){
        encabezado = "<div class= 'Comentarios'>Comentario: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(especiales))){
        encabezado = "<div class= 'Especiales'>Caracter especial: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(operadores))){
        encabezado = "<div class= 'Operadores'>Operador: " + caracter + "</div>";
      }
    }
  }
}

void resaltadorHilos(){
  
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }

  resaltadorSecuencial(argv[1]);

  return 0;
}