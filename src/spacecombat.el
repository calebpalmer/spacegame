(require 'compile)

(defun myproj-clean ()
  (interactive)
  (set (make-local-variable 'compile-command) "make clean; make extract")
  (call-interactively 'compile)
)

(defun myproj-compile ()
  (interactive)
  (set (make-local-variable 'compile-command) "make -k")  
  (call-interactively 'compile)
)

(defun myproj-tags ()
  (interactive)
  (shell-command "make tags")
)

(global-set-key [f12] 'myproj-compile)
(global-set-key [f11] 'myproj-clean)
(global-set-key (kbd "C-c C-b t") 'myproj-tags)
