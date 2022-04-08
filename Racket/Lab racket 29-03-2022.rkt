;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |Lab racket 29-03-2022|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; sum: number number -> number (BTW esto es un comentario)
(define sum
  (lambda (a b)
    (+ a b)))

;; sum of squares: number number -> number
(define sum-of-squares
  (lambda (a b)
    (sum (* a a) (* b b))))

;; area of a disk: number -> number
(define area-of-a-disk
  (lambda (radio)
    (* 3.14151692 radio radio)))

;; area of a ring: number number -> number
(define area-of-a-ring
  (lambda (outer inner)
    (-(area-of-a-disk outer)
    (area-of-a-disk inner))))

;; wage: number number -> number
(define wage
  (lambda (payment hours)
    (* paument hours)))

;; tax: number number -> number
(define tax
  (lambda (wage rate)
    (* wage rate)))
