(setq auto-mode-alist
        (append '(("\\.C$"  . c++-mode)
        ("\\.cc$" . c++-mode)
        ("\\.cpp$". c++-mode)
        ("\\.cu$". c++-mode)
        ("\\.hh$" . c++-mode)
        ("\\.c$"  . c-mode)
        ("\\.h$"  . c++-mode))
                auto-mode-alist))


(add-hook 'c-mode-common-hook
          '(lambda ()
	     (c-set-style "cc-mode")
	     ;; (c-set-style "GNU")
             ;; (c-set-style "k&r")
             ;; (c-set-style "bsd")
             ;; (c-set-style "stroustrup")
             ;; (c-set-style "whitesmith")
             ;; (c-set-style "ellemtel")
	     ;; (c-set-style "linux")
             (progn
	       ;; (c-toggle-hungry-state 1)
	       (setq c-basic-offset 4 indent-tabs-mode nil))

             (require 'vc-hooks)
             (setq completion-mode t)
             ;; make: options are not asked.
             (setq compilation-read-command nil)
             ;; make: all buffers are saved automatically.
             (setq compilation-ask-about-save nil)
             (define-key c-mode-base-map "\C-m" 'newline-and-indent)
             (define-key c-mode-base-map "\C-h" 'delete-backward-char)
             (define-key c-mode-base-map "\C-ci" 'c-indent-line-or-region)
             (define-key c-mode-base-map [f1] 'manual-entry)
             (define-key c-mode-base-map [f4] 'next-error)
             (define-key c-mode-base-map "\C-ce" 'next-error)
             (define-key c-mode-base-map [(shift f4)] 'previous-error)
             (define-key c-mode-base-map [f7] 'compile)
             (define-key c-mode-base-map "\C-cc" 'compile)
             (define-key c-mode-base-map [(shift f7)]
                '(lambda ()
                   (interactive)
                   ;;(require 'compile)
                   ;;(save-some-buffers (not compilation-ask-about-save) nil)
                   (compile-internal "make clean all" "No more errors")))
             ))
