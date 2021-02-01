(define-syntax my-map
	(syntax-rules (for in)
((_ expr for x in a)
(map (lambda (x) expr) a))))

;test
(define lst (list 1 2 3 4 5))
(display lst)
(newline)
(display (my-map (* x x) for x in lst))
(newline)
(define-syntax my-cond
  (syntax-rules (else)
		((_ (else cond1 ...))
		 (begin cond1 ...))
		((_ (cond1 cond2 ...))
		 (if cond1 (begin cond2 ...)))
		((_ (cond1 cond2 ...) right ...)
		 (if cond1 (begin cond2 ...) (my-cond right ...)))))
    
;test
(define (check a b)
  (my-cond 
    ((> a b) (display "a > b"))
    ((< a b) (display "a < b"))
    (else (display "a = b"))))
(check 4 3)
(newline)

