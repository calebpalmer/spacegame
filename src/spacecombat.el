(require 'compile)

(defun proj-clean ()
  (interactive)
  (set (make-local-variable 'compile-command) "make clean; make extract")
  (call-interactively 'compile)
)

(defun proj-compile ()
  (interactive)
  (set (make-local-variable 'compile-command) "make -k")  
  (call-interactively 'compile)
)

(global-set-key [f12] 'proj-compile)
(global-set-key [f11] 'proj-clean)
