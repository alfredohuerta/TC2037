;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Actividad 2.1 Programación funcional, parte 1|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f () #f)))
;; Erick Alfredo García Huerta - A01708119
(define my-list-pos-neg '(-1 -2 -3 -4 -5 1 2 3 4 5 10))
(define my-list-w-symbols '("a" "b" "c" "d" "e"))
(define my-list-wt-symbols '("a" "b" "c" "d" "e" 6))
(define empty-list '())
(define listA '(1 2 3 4))
(define listB '(5 6 7 8))
(define listP '((a b) (1 2) (c d) (3 4)))

;; 1. La función toma como entrada una temperatura f en grados Fahrenheit y la convierte a su equivalente en grados Celsius
(define fahrenheit-to-celsius
  (lambda (F)
    (/ (* (- F 32) 5) 9)))

;; 2. La funcíon sign recibe como entrada un valor entero n. Devuelve -1 si n es negativo, 1 si n es positivo mayor que cero, o 0 si n es cero.
(define sign
  (lambda (n)
    (cond
      [(> n 0) 1]
      [(< n 0) -1]
      [else 0])))

;; 3.  La función roots devuelve la ra ́ız que resuelve una ecuaci ́on cuadr ́atica a partir de sus tres coeficiente, a, b y c, que se reciben como entrada.
(define roots
  (lambda (a b c)
     (/ (+ (* -1 b) (sqrt (- (expt b 2) (* 4 a c)))) (* 2 a))))

;; 4.  La función bmi recibe dos entrada: weight y height. Debe devolver un s ́ımbolo que represente la descripci ́on del BMI correspondiente calculado a partir de sus entradas.
(define bmi
  (lambda (w h)
   (cond
     [(> (/ w (expt h 2)) 40) "obese3"]
     [(> (/ w (expt h 2)) 30) "obese2"]
     [(> (/ w (expt h 2)) 25) "obese1"]
     [(> (/ w (expt h 2)) 20) "normal"]
     [else "underweight"])))

;; 5. La funcíon factorial toma un entero positivo n como su entrada y devuelve el factorial correspondiente
(define factorial
  (lambda (n)
    (cond
      [(= n 0) 1]
      [else (* n (factorial (- n 1)))])))

;; 6. La funcíon pow toma dos entradas como entrada: un n ́umero a y un entero positivo b. Devuelve el resultado de calcular a elevado a la potencia b.
(define pow
  (lambda (a b)
    (expt a b)))

;; 7. La funcíon add-list devuelve la suma de los n ́umeros contenidos en la lista que recibe como entrada, o 0 si est ́a vac ́ıa.
(define add-list
  (lambda (lst)
    (cond
      [(null? lst) '0]
      [(list? (car lst)) (+ (add-list (car lst))
                            (add-list (cdr lst)))]
      [else (+ (car lst)
               (add-list (cdr lst)))])))

;; 8. La funci ́on de list-of-symbols? toma una lista lst como entrada. Devuelve verdadero si todos los elementos (posiblemente cero) contenidos en lst son s ́ımbolos, o falso en caso contrario.
(define list-of-symbols?
  (lambda (lst)
      (cond
        [(equal? lst '()) #t]
        [(andmap string? lst) #t]
        [else #f])))

;; 9. La funci ́on positives toma una lista de n ́umeros lst como entrada y devuelve una nueva lista que solo contiene los n ́umeros positivos de lst.
(define positives
  (lambda (lst)
      (filter positive? lst)))

;; 10.La funci ́on fib toma un entero positivo n como entrada y devuelve el elemento correspondiente de la secuencia de Fibonacci
(define fib
  (lambda (n)
    (cond
      [(> n 1) (+ (fib (- n 1)) (fib (- n 2)))]
      [else n])))

;; 11.La funci ́on dot-product toma dos entradas: las listas a y b. Devuelve el resultado de realizar el producto punto de a por b. El producto punto es una operaci ́on algebraica que toma dos secuencias de n ́umeros de igual longitud y devuelve un solo n ́umero que se obtiene multiplicando los elementos en la misma posici ́on y luego sumando esos productos.
(define dot-product
  (lambda (lst1 lst2)
    (+ (dot-product (+ (* (car lst1) (car lst2)) (* (cdr lst1) (cdr lst2))) lst1 lst2))))

;; 12. La funci ́on invert-pairs toma como entrada una lista cuyo contenido son listas de dos elementos. Devuelve una nueva lista con cada pareja invertida.
(define invert-pairs
  (lambda (list)
    (cond
      [(null? list) '()]
      [else (invert-pairs (reverse list))])))
      
;; 13.


;; 14.


;; 15.