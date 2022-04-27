#lang racket
(require racket/trace)
;; Erick Alfredo García Huerta - A01708119
;; Constantes
(define empty-list '())
(define lista '(1 2 3 4 5))
(define lista1 '(a b c))
(define paquete '(a a a a b c c a a d e e e e))
(define nested-list '((a) b (c d) (e) ((f) (g h))))

;; 1. La funcíon insert toma dos entradas: un ńumero n y una lista lst que contiene ńumeros en orden ascendente. Devuelve una nueva lista con los mismos elementos de lst pero con n insertado en su lugar correspondiente.
(define insert
  (lambda (n lst)
    (cond
      [(empty? lst)
       (cons n '())]
      [(<= n (car lst))
       (cons n lst)]
      [else
       (cons (car lst) (insert n (cdr lst)))])))

;; 2. La funcíon insertion-sort toma una lista desordenada de ńumeros como entrada y devuelve una nueva lista con los mismos elementos pero en orden ascendente. Se debe usar la funcíon de insert definida en el ejercicio anterior para escribir insertion-sort. No se debe utilizar la funcíon sort o alguna similar predefinida.
;; dividir la función en varias
(define insert-helper
  (lambda (in-list out-list)
    (cond
      [(empty? in-list) out-list]
      [(and (> length (> (car in-list) (car (cdr in-list))) in-list) 1)
       (cons (car in-list) out-list) (insert-helper (cdr in-list) out-list)]
      [else
       (cons (car in-list) (insert-helper (cdr in-list) out-list)
             (insert-helper (car in-list) out-list))])))
(trace insert-helper)

;; 3. 
(define deep-reverse
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(list? (car lst))
       (cond
         [(empty? (cdr lst)) (append (deep-reverse (car lst)) '())]
         [else (cons (deep-reverse (cdr lst))
                     (deep-reverse (car lst)))])]
      [else (append (deep-reverse (cdr lst))
                  (cons (car lst) '()))])))

(trace deep-reverse)

;; 4. La función coprtess toma una lista lst como entrada. Devuelve una lista en la que los elementos repetidos consecutivos de lst se reemplazan por una sola instancia. El orden de los elementos no debe modificarse.
(define compress
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else
       (remove-duplicates lst)])))

;; 5. fn para la función
(define there-exists-one?
  (lambda (fn lst)
    (cond
      [(null? lst) #f]
      [(fn (car lst)) #t]
      [else (there-exists-one? fn (cdr lst))])))

;;6.
(define helper
  (lambda (cont lst)
    (if (empty? lst)
        cont
        (+ 1 (helper cont (cdr lst))))))

(define linear-search
  (lambda (val lst fn)
    (cond
      [(empty? lst) #f]
      [(and (equal? (car lst) val) fn) (helper 0 lst)]
      [else
       (linear-search val (cdr lst) fn)])))

;; 7.

(define args-swap
  (lambda (fn)
    (lambda (a b)
      (fn a b))))

;; 8.
