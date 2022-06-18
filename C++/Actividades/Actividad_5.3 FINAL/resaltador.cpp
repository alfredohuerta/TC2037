#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

using namespace std;

const int THREADS = 8;

string resaltador(string archivo) {
  fstream pruebas;
  string resultados, cuerpo;
  vector<char>::iterator it;
  pruebas.open(archivo, ios::in);

  while(getline(pruebas, resultados)){

    // definimos los operadores aritmeticos
    string variable = "[a-zA-Z][a-zA-Z_0-9]*";
    string operadores = "[\\*|\\/|\\^|\\=|\\+|\\-]";
    string reales = "-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?"; /* con los () y ? decimos que eso puede o 
                                                                              no estar en la funcion establecida*/
    string especiales = "[\\(\\)]";
    string comentarios = "//.*$"; //. cualquier elemento  y el $ indica que continua hasta llegar al final de la linea 
    string reservadas = "alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq";

    // solo debemos tener un regex, entonces juntamos las strings anteriores
    regex regex_tokens(comentarios +"|"+ reales +"|"+ variable +"|"+ especiales +"|"+ operadores); /* +"|"+ ees variable
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
        cuerpo = cuerpo + "<div class= 'Variables'>Variable: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(reales))){
        cuerpo = cuerpo + "<div class= 'Reales'>Número real: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(comentarios))){
        cuerpo = cuerpo + "<div class= 'Comentarios'>Comentario: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(especiales))){
        cuerpo = cuerpo + "<div class= 'Especiales'>Caracter especial: " + caracter + "</div>";
      }else if(regex_match(caracter, regex(operadores))){
        cuerpo = cuerpo + "<div class= 'Operadores'>Operador: " + caracter + "</div>";
      }
    }
  }

  return cuerpo;
}

typedef struct {
	int start, end;
	string* array;
} Block;

void* resaltadorHilos(void* param){
  string cuerpo;
  Block *block;
	block = (Block*)param;
	vector<string> vectorPalabras;
	for (int i = block->start; i < block->end; i++) {
    string line;
    ifstream pruebas(block->array[i]);
    if (pruebas.is_open()){
      while (getline(pruebas, line)){
        ofstream html("FinalHilos.html");
        html << "<!DOCTYPE html><html lang='esp-mx'> <head> <meta charset='UTF-8'> <title>Resaltador de sintaxis</title> <style>body{color: beige;}.PReservadas{color: blue;}.Variables{color: blueviolet;}.Operadores{color: aqua;}.Reales{color: chartreuse;}.Especiales{color: crimson;}.Comentarios{color: gold;}</style> </head> <body>";

        string variable = "[a-zA-Z][a-zA-Z_0-9]*";
        string operadores = "[\\*|\\/|\\^|\\=|\\+|\\-]";
        string reales = "-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?"; /* con los () y ? decimos que eso puede o 
                                                                                  no estar en la funcion establecida*/
        string especiales = "[\\(\\)]";
        string comentarios = "//.*$"; //. cualquier elemento  y el $ indica que continua hasta llegar al final de la linea 
        string reservadas = "alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq";

        // solo debemos tener un regex, entonces juntamos las strings anteriores
        regex regex_tokens(comentarios +"|"+ reales +"|"+ variable +"|"+ especiales +"|"+ operadores); /* +"|"+ ees variable
                                                                                        OR operador y el + es para agregar*/

        // definimos nuestro iterador para ir recorriendo y buscar en regex los tokens
        auto inicio_arch = 
            // iterador para ir recorriendo match por match y detectarlos en regex_tokens
            std::sregex_iterator(line.begin(), line.end(), regex_tokens); /*leer de resultados incio a 
                                                                                        resultados final */
        auto fin_arch = std::sregex_iterator(); // cuando ya no tenga mas elementos se deja de leer 

        // vamos a ir leyendo caracter x caracter, al detectar su token, pasamos al siguiente carcater
        for (std::sregex_iterator i = inicio_arch; i != fin_arch; ++i) {
          string cuerpo;
          std::smatch match = *i; // con el * lo desreferencia, desapuntador                                               
          std::string caracter = match.str(); // lo convertimos a string

          /*ya que tebemos el string, vemos si esta hace match con el regex, que basta solo con poner regex ya que se llama 
          al constructor*/
          if(regex_match(caracter, regex(variable))){
            cuerpo = cuerpo + "<div class= 'Variables'>Variable: " + caracter + "</div>";
            html << cuerpo;
          }else if(regex_match(caracter, regex(reales))){
            cuerpo = cuerpo + "<div class= 'Reales'>Número real: " + caracter + "</div>";
            html << cuerpo;
          }else if(regex_match(caracter, regex(comentarios))){
            cuerpo = cuerpo + "<div class= 'Comentarios'>Comentario: " + caracter + "</div>";
            html << cuerpo;
          }else if(regex_match(caracter, regex(especiales))){
            cuerpo = cuerpo + "<div class= 'Especiales'>Caracter especial: " + caracter + "</div>";
            html << cuerpo;
          }else if(regex_match(caracter, regex(operadores))){
            cuerpo = cuerpo + "<div class= 'Operadores'>Operador: " + caracter + "</div>";
            html << cuerpo;
          }
        }
        html << "</body></html>";
			  html.close();
      }
    }
    pruebas.close();
  }
  

  //cuerpo = resaltador(param);

}

int main(int argc, char* argv[]) {  
  double ms, ms2;
  string *rutasArchivos;
  int blockSize;
  Block blocks[THREADS];
  const int sizeArray = argc;

  rutasArchivos = new string[sizeArray];

	for (int i = 0; i < argc; i++) {
		rutasArchivos[i] = argv[i];
	}

  if (argc != 3) {
    cout << "usage: " << argv[0] << " filename1,..., filenamen\n";
    return -1;
  }

  /*-----------------------------------------Resaltador secuencial-----------------------------------------*/
  string encabezado = "<!DOCTYPE html><html lang='esp-mx'> <head> <meta charset='UTF-8'> <title>Resaltador de sintaxis</title> <style>body{color: beige;}.PReservadas{color: blue;}.Variables{color: blueviolet;}.Operadores{color: aqua;}.Reales{color: chartreuse;}.Especiales{color: crimson;}.Comentarios{color: gold;}</style> </head> <body>";
  string *cuerpo;
  for(int i = 1; i < argc; i++){
    encabezado = encabezado + resaltador(argv[i]);
  }
  encabezado = encabezado + "</body></html>";

  ms = 0;
	start_timer();
  ofstream file;
  file.open("FinalSecuencial.html");

  file << encabezado;

  file.close();
  ms = stop_timer();
  /*-----------------------------------------Resaltador multihilos-----------------------------------------*/
  pthread_t analisis[argc];

  blockSize = sizeArray / THREADS;

	for (int i = 0; i < THREADS; i++) {
		blocks[i].array = rutasArchivos;
		blocks[i].start = i * blockSize;
		blocks[i].end = i != (THREADS - 1) ? (i + 1) * blockSize : sizeArray;
	}

  ms2 = 0;
	start_timer();
	for (int i = 0; i < THREADS; i++) {
		pthread_create(&analisis[i], NULL, resaltadorHilos, (void*)&blocks[i]);
	}

	for (int i = 0; i < THREADS; i++) {
		pthread_join(analisis[i], NULL);
	}
	ms2 += stop_timer();

  cout << "*********** Secuencial ***********\n";
	cout << "Time = " << setprecision(5) << (ms) << "\n";
	cout << "*********** Multihilos ***********\n";
	cout << "Time = " << setprecision(5) << (ms2 / THREADS) << "\n";
  /* for(int i = 0; i < argc; i++){
    pthread_create(&analisis[i], NULL, resaltadorHilos, NULL);
  } */
 /*  for(int i = 0; i < argc; i++){
    pthread_join(analisis[i], (void **) &cuerpo);
    encabezado += (*cuerpo);
    delete cuerpo;
  } */

  /* file.open("FinalHilos.html");

  file << encabezado;

  file.close(); */

  return 0;
}
