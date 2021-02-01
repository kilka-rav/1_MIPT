(define (data tree) (car tree))		;	
(define (L tree) (cadr tree))
(define (R tree) (caddr tree))	; OK
(define (leaf x) (list x '() '()))
(define (insert-tree t x)
  (cond
    ((null? t) (leaf x))
    ((= (data t) x) t)
    ((< (data t) x) (list (data t) (L t) (insert-tree (R t) x)))
    ((> (data t) x) (list (data t) (insert-tree (L t) x) (R t)))))
(define (insert-tree-tree lst t)       ;вставка в дерево поддерево
  (cond
    ((null? lst) t)
    ((< (data lst) (data t)) (list (data lst) (L lst) (insert-tree-tree (R lst) t)))
    ((> (data lst) (data t)) (list (data lst) (insert-tree-tree (L lst) t) (R lst)))))

(define (search t x)
  (cond
    ((null? t) #f)
    ((< (data t) x) (search (R t) x))
    ((> (data t) x) (search (L t) x))
    (else #t)))
(define (delete-tree t x)  ;проверка на удаление верхушки
  (cond 
    ((search t x) (del t x t))
    (else t)))
(define (del t x lst) ; рекурсивно ищем вершину
  (cond
    ((= (data t) x) (delete-full lst x t)) ;находим поддерево с нужным ключом
    ((< (data t) x) (del (R t) x lst))
    ((> (data t) x) (del (L t) x lst))))
(define (delete-full lst x t)
  (cond
    ((and (null? (L t)) (null? (R t))) (delete-leaf lst t))
    (else (cond
	((null? (L t)) (insert-tree-tree (delete-leaf lst t) (R t)))
	((null? (R t)) (insert-tree-tree (delete-leaf lst t) (L t)))
	(else (delete-two lst t))))))
  
(define (delete-two lst t)
  (list (minimum (R lst)) (L lst) (delete-leaf (R lst) (minimum (R lst)))))
(define (minimum lst)
  (cond
    ((null? (L lst)) (data lst))
    (else (minimum (L lst)))))
(define (delete-leaf lst x) ;удаляем листья
  (cond
    ((null? lst) '())
    ((equal? x (data lst)) (cons '() (cdr lst)))
    (else (cons (data lst) (delete-leaf (cdr lst) x)))))



;test
(define tree (list 10 (list 5 (list 3 '() '()) '()) (list 22 '() '())))
(display "tree\n")
(display tree)
(newline)
(display "tree after insert\n")
(display (insert-tree tree 20))                 
(newline)
(display "search 5 and 231321")
(newline)
(display (search tree 10))
(display " ")
(display (search tree 231321))
(newline)                                     
(display "delete\n")
(display "tree\n")
(display tree)
(newline)
(display "delete 5 tree\n")
(display (delete-tree tree 5))
(newline)
(display "delete main-root tree\n")
(display (delete-tree tree 10))
(newline)
