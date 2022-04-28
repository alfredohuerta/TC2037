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
(define reservadas '("alignas" "alignof" "and" "and_eq" "asm" "atomic_cancel" "atomic_commit" "atomic_noexcept" "auto" "bitand" "bitor" "bool" "break" "case" "catch" "char" "char8_t""char16_t" "char32_t" "class" "compl" "concept" "const" "consteval" "constexpr" "constinit" "const_cast" "continue" "co_await" "co_return" "co_yield" "decltype" "default" "delete" "do" "double" "dynamic_cast" "else" "enum" "explicit" "export" "extern" "false" "float" "for" "friend" "goto" "if" "inline" "int" "long" "mutable" "namespace" "new" "noexcept" "not" "not_eq" "nullptr" "operator" "or" "or_eq" "private" "protected" "public" "reflexpr" "register" "reinterpret_cast" "requires" "return" "short" "signed" "sizeof" "static" "static_assert" "static_cast" "struct" "switch" "synchronized" "template" "this" "thread_local" "throw" "true" "try" "typedef" "typeid" "typename" "union" "unsigned" "using" "virtual" "void" "volatile" "wchar_t" "while" "xor" "xor_eq"))

;; Extrae los caracteres del documento y las almacena en una lista. InputFile->characterList
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

#|Función que obteiene una lista de caracteres (loc) y dos listas vacías (aux, result), recorre toda la lista de caracteres
almacenando los valores en el auxiliar, y cuando se encuentra con un espacio vacío (#\tab, #\space, #\newline)
convierte la lista de caracteres que ha extraído en un string que se almacena en resultados|#
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

;;PARA OBTENER LA LISTA ORDENADA (reverse (char->string (file->list-of-chars file) '() '()))
    

;; Se crean los regex match que contendran las expresiones regulares y filtrará los tokens
(define matches
  (lambda (element)
    (cond
      [(regexp-match #rx"[a-zA-Z][a-zA-Z_0-9]*" element)
       (cons element variables)]
      [(regexp-match #rx"[\\*|\\/|\\^|\\=|\\+|\\-]" element)
       (cons element operadores)]
      [(regexp-match #rx"-*[0-9]+\\.[0-9]+([E][-*][0-9]+)?|-*[0-9]+(\\.[0-9]+)?" element)
       (cons element reales)]
      [(regexp-match #rx"[\\(\\)]" element)
       (cons element especiales)]
      [(regexp-match #rx"//.*$" element)
       (cons element comentarios)]
      [else
       (cons element reservadas)])))

