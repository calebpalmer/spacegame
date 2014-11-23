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

(defun myproj-launch ()
  (interactive)
  (shell-command "sh ./spacecombat.sh")
)

(defun myproj-debug ()
  (interactive)
  ;; (set (make-local-variable 'gdb-command-name) "gdb -i=mi spacecombat -d ../../github/capengine")
  (setenv "LD_LIBRARY_PATH" ".")
  (defvar gud-gdb-command-name "")
  ;;(setq gud-gdb-command-name "gdb -i=mi --ex \"dir ../capengine\" spacecombat")
  (setq gud-gdb-command-name "gdb -i=mi  spacecombat")
  (call-interactively 'gdb)
)

(global-set-key [f12] 'myproj-compile)
(global-set-key [f11] 'myproj-clean)
(global-set-key [f10] 'myproj-debug)
(global-set-key (kbd "C-c C-l t") 'myproj-tags)
(global-set-key (kbd "C-c C-l l") 'myproj-launch)

(global-set-key (kbd "M-.") 'gtags-find-tag)
