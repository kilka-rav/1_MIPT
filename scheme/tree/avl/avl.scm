(define (data tree) (car tree))
(define (L tree) (cadr tree))
(define (R tree) (caddr tree))
(define (H tree)			
  (cond
    ((null? tree) 0)
    (else (cadddr tree))))
(define (make-avl data L R)
  (list data L R (+ 1 (max (H L) (H R)))))
(define (rotate-right t)	; балансировка поворотом направо		
  (cond
    ((null? t) t)
    (else (make-avl (data (R t)) (make-avl (data t) (L t) (L (R t))) (R (R t))))))
(define (rotate-left t)		; балансировка поворотом налево
  (cond
    ((null? t) t)
    (else (make-avl (data (L t)) (L (L t)) (make-avl (data t) (R (L t)) (R t))))))
(define (rotate-composition-lr t)
  (rotate-left (list (data t) (rotate-right (L t)) (R t))))
(define (rotate-composition-rl t)
  (rotate-right (list (data t) (L t) (rotate-left (R t)))))
(define (dbal t) (- (H (R t)) (H (L t)))) ; баланс узлов
(define (balance-avl t)
  (let ((main-dbal (dbal t)))
    (cond
      ((= main-dbal 2)
       (cond 
	 ((< (dbal (R t)) 0) (rotate-composition-rl t))
	 (else (rotate-right t))))
      ((= main-dbal -2)
       (cond 
	 ((> (dbal (L t)) 0) (rotate-composition-lr t))
	 (else (rotate-left t))))
    (else t))))
(define (search t x)
  (cond
    ((null? t) #f)
    ((= (data t) x) #t)
    ((< (data t) x) (search (R t) x))
    ((> (data t) x) (search (L t) x))))
(define (insert t x)   ; для вставки дублей используем (data (L t)) <= (data t) < (data (R t))
    (cond 
      ((null? t) (list x '() '() 0))
      ((> (data t) x)
	(let* ((new-LT (insert (L t) x)) (new-tree (make-avl (data t) new-LT (R t)))) ;используем позднее связывание
	(balance-avl new-tree)))
      ((<= (data t) x)
       (let* ((new-RT (insert (R t) x)) (new-tree (make-avl (data t) (L t) new-RT)))
	 (balance-avl new-tree)))))



;test 
(define tree (list 12 (list 5 '() (list 7 '() (list 9 '() '() 0) 1) 2) (list 13 '() '() 0) 3))
(display "tree\n")
(display tree)
(newline)
(display "after insert in AVL-tree 9\n")
(display (insert tree 12))
(newline)
(display "tree\n")
(display tree)
(newline)
(display "search 13 15\n")
(display (search tree 13))
(display " ")
(display (search tree 15))
(newline)

