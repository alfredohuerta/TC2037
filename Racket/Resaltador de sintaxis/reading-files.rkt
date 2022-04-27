#lang racket
(require 2htdp/batch-io)
(require racket/trace)

;;https://docs.racket-lang.org/teachpack/2htdpbatch-io.html#%28def._%28%28lib._2htdp%2Fbatch-io..rkt%29._write-file%29%29
;;https://docs.racket-lang.org/reference/characters.html

(define input-file "testInput.txt")

(define output-file "testOutput.txt")

(define (flatten lists)
   (foldr append empty lists))

;;(string-downcase str)
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

;;(define input-characters (file->list-of-chars input-file))
(define list-of-chars->file
  (lambda (lst filename)
    (write-file filename (list->string lst))))

(define copy-and-upcase
  (lambda (input-file output-file)
    (list-of-chars->file
     (map char-upcase (file->list-of-chars input-file))
     output-file)))

;; (map char-upcase (file->list-of-chars input-file))