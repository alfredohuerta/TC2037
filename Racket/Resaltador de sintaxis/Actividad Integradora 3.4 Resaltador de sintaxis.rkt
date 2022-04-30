#lang racket
(require 2htdp/batch-io)
(require racket/trace)

(define Input "test.cpp")
(define Output "testOutput.txt")

;; Listas de tokens
(define variables '("variables"))
(define operadores '("operadores"))
(define reales '("reales"))
(define especiales '("especiales"))
(define comentarios '("comentarios"))
(define reservadas '("reservadas"))
(define indexReservadas '("[alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)]"))
(define empty '("NADA"))

;; Extrae los caracteres del documento y las almacena en una lista. InputFile->characterList
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

#|Función que obteiene una lista de caracteres (loc) y dos listas vacías (aux, result), recorre toda la lista de caracteres almacenando los valores en el auxiliar,
y cuando se encuentra con un espacio vacío (#\tab, #\space, #\newline) convierte la lista de caracteres que ha extraído en un string que se almacena en resultados|#
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

(define string-list
  (lambda (filename)
    (reverse
     (char->string (file->list-of-chars filename) '() '()))))

;; Se crean los regex match que contendran las expresiones regulares y filtrará los tokens
(define matches
  (lambda (strList result)
    (cond
      [(empty? strList)
       result]
      
      ;; Palabras reservadas
      [(regexp-match #rx"[alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)]"
       (inicio_html(string-append "<div id=\"PReservada\">" (car strList) "</div>")))]
      
      ;; Variables
      [(regexp-match #rx"[a-zA-Z][a-zA-Z_0-9]*" 
       (inicio_html(string-append "<div id=\"Variables\">" (car strList) "</div>")))]
      
      ;; Operadores
      [(regexp-match #rx"[\\*|\\/|\\^|\\=|\\+|\\-]"
       (inicio_html(string-append "<div id=\"Operadores\">" (car strList) "</div>")))]
      
      ;; Números reales
      [(regexp-match #rx"-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?"
       (inicio_html(string-append "<div id=\"Reales\">" (car strList) "</div>")))]
      
      ;; Caracteres especiales
      [(regexp-match #rx"[\\(\\)\\#\\;\\.\\{\\}\\<\\>]"
       (inicio_html(string-append "<div id=\"Especiales\">" (car strList) "</div>")))]
      
      ;; Comentarios
      [(regexp-match #rx"//.*$"
       (inicio_html(string-append "<div id=\"Comentarios\">" (car strList) "</div>")))]
      
      [else
       (matches (cdr strList) result)])))

(define inicio_html
  (list
   "<!DOCTYPE html>\n"
   "<html lang=\"esp-mx\">\n"
   "<head>\n"
   "    <meta charset=\"UTF-8\">\n"
   "    <title>Resaltador de sintaxis</title>\n"
   "    <style>\n"
   "        body{color: beige;}\n"
   "        #PReservadas{color: blue;}\n"
   "        #Variables{color: blueviolet;}\n"
   "        #Operadores{color: aqua;}\n"
   "        #Reales{color: chartreuse;}\n"
   "        #Especiales{color: crimson;}\n"
   "        #Comentarios{color: gold;}\n"
   "    </style>\n"
   "</head>\n"
   "<body>\n"))

(define test
  (lambda (filename)
    (matches(string-list filename)'("reservadas") '("variables") '("operadores") '("reales")'("especiales")'("comentarios") '())))
;;