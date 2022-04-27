#lang racket
(require 2htdp/batch-io)
(require racket/trace)

(define Input "testInput.txt")
(define Output "testOutput.txt")

;; Extrae las palabras del documento y las almacena en una lista vacía.
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-words filename)))))
(trace file->list-of-chars)

;; 