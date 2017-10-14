;; .emacs

;;; uncomment this line to disable loading of "default.el" at startup
;; (setq inhibit-default-init t)

;; turn on font-lock mode
(when (fboundp 'global-font-lock-mode)
  (global-font-lock-mode t))

;; enable visual feedback on selections
;(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; always end a file with a newline
;(setq require-final-newline 'query)


;; c-mode

(load "~/.emacs-cpp.el")

; R for emacs

(require 'ess-site)

;;
;; Matlab
;;
;
;;;; Replace path below to be where your matlab.el file is.
;;(add-to-list 'load-path "/home/morii/admin/emacs_matlab/matlab-emacs")
;;(load-library "matlab-load")
;
;;; Enable CEDET feature support for MATLAB code. (Optional)
;;; (matlab-cedet-setup)
;
;(autoload 'matlab-mode "matlab" "Matlab Editing Mode" t)
;(add-to-list
; 'auto-mode-alist
; '("\\.m$" . matlab-mode))
;(setq matlab-indent-function t)
;(setq matlab-shell-command "matlab")


;; ------ memo ------------

; open again by utf8
;C-x RET c utf-8-unix RET M-x revert-buffer

; open again by euc
;C-x RET c euc-jp-unix RET M-x revert-buffer

