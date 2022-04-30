#lang racket
(require 2htdp/batch-io)
(require racket/trace)

;; Erick Alfredo García Huerta - A01708119
;; Alan Fernando Razo Peña - A01703350 

;; Definición de archivos a utilizar
(define Input "test.cpp")
(define Output "Final.html")

;; Encabezado del archivo html
(define header "<!DOCTYPE html><html lang='esp-mx'> <head> <meta charset='UTF-8'> <title>Resaltador de sintaxis</title> <style>body{color: beige;}.PReservadas{color: blue;}.Variables{color: blueviolet;}.Operadores{color: aqua;}.Reales{color: chartreuse;}.Especiales{color: crimson;}.Comentarios{color: gold;}</style> </head> <body>")

;; Extrae los caracteres del documento y las almacena en una lista. InputFile->characterList
;; Complejidad O(1) debido a que no utiliza ningún ciclo y sus funciones se aplican al mismo tiempo a todos los elementos de la lista gracias a la función map
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

#|Función que obteiene una lista de caracteres (loc) y dos listas vacías (aux, result), recorre toda la lista de caracteres almacenando los valores en el auxiliar,
y cuando se encuentra con un espacio vacío (#\tab, #\space, #\newline) convierte la lista de caracteres que ha extraído en un string que se almacena en resultados|#
;; Complejidad O(n) debido al uso de ciclos recursivos cuya duración depende de la longitud del arreglo de caracteres, ya que el caso base para la ruptura del ciclo es el vaciado de dicha lista.
(define char->string
  (lambda (loc aux result)
    (cond
      [(empty? loc) result]
      [(char-whitespace? (car loc))
       (char->string (cdr loc)
                                       '()
                                       (cons
                                        (list->string aux)
                                        result))]
      [(char-punctuation? (car loc))
       (char->string (cdr loc)
                                       '()
                                       (cons
                                        (list->string
                                         (cons (car loc) '()))
                                        (cons
                                         (list->string aux)
                                         result)))]
      [else
       (char->string (cdr loc)
                                       (append aux (cons (car loc) '()))
                                       result)])))

;; Función auxiliar que simplifica la obtención de la lista de strings
;; Complejidad O(1)+O(n)= O(n) debido a que la complejidad de esta función está ligada a la complejidad de la función char->string
(define string-list
  (lambda (filename)
    (char->string (file->list-of-chars filename) '() '())))

;; Se crean los regex match que contendran las expresiones regulares y filtrará los tokens que serán escritos y almacenados en un string global una vez se haya hecho el regexp-match
;; Complejidad O(n) debido al uso de ciclos recursivos cuya duración depende de la longitud del arreglo de strings, ya que el caso base para la ruptura del ciclo es el vaciado de dicha lista.
(define matches
  (lambda (strList result)
    (cond
      [(empty? strList)
       (string-append result "</body></html>")]

      ;; Palabras reservadas
      [(regexp-match #rx"alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq" (car strList))
       (matches (cdr strList) (string-append "<div class= 'PReservadas'>Palabra reservada: " (car strList) "</div>" result))]
      
      ;; Operadores
      [(regexp-match #rx"[\\*|\\/|\\^|\\=|\\+|\\-]" (car strList))
       (matches (cdr strList) (string-append "<div class= 'Operadores'>Operador: " (car strList) "</div>" result))]
      
      ;; Números reales
      [(regexp-match #rx"-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?" (car strList))
       (matches (cdr strList) (string-append "<div class= 'Reales'>Número real: " (car strList) "</div>" result))]
      
      ;; Caracteres especiales
      [(regexp-match #rx"[\\)\\(\\#\\;\\.\\}\\{\\<\\>]" (car strList))
       (matches (cdr strList) (string-append "<div class= 'Especiales'>Caracter especial: " (car strList) "</div>" result))]
      
      ;; Variables
      [(regexp-match #rx"[a-zA-Z][a-zA-Z_0-9]*" (car strList))
       (matches (cdr strList) (string-append "<div class= 'Variables'>Variable: " (car strList) "</div>" result))]
      
      ;; Comentarios
      [(regexp-match #rx"//.*$" (car strList))
       (matches (cdr strList) (string-append "<div class= 'Comentarios'>Comentario: " (car strList) "</div>" result))]
      
      [else
       (matches (cdr strList) result)])))

;; Función auxiliar que permite obtener el string final con todos los datos del html
;; Complejidad O(1)+O(n)= O(n) debido a que hace uso de una función con complejidad O(n) depende de ella completamente para funcionar.
(define finalList
  (lambda (inputFile)
    (string-append header (matches (reverse(string-list inputFile)) ""))))

;; Función que escribe los datos del string global en un archivo html
;; Complejidad O(1)+O(n)= O(n) debido a que hace uso de una función con complejidad O(n) depende de ella completamente para funcionar.
(define writing
  (lambda (inputFile outputFile)
    (write-file outputFile (finalList inputFile))))