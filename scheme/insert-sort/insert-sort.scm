(define (insert x lst) ; рекурсивная вставка элемента
  (if (null? lst) (list x) ; если lst пустой
      (let ((y (car lst)) ; дробим lst
            (new-lst (cdr lst)))
        (if (<= x y) (list x lst)
            (cons y (insert x new-lst))))))
 
(define (insert-sort lst) 
  (if (null? lst) '()
      (insert (car lst) (insert-sort (cdr lst)))))
 

(define lst (list 9 8 7 6 5 4 3 2 1))
(display "BEFORE\n")
(display lst)
(newline)
(display "AFTER\n")
(display (insert-sort lst))
(newline)
