
# Themen

1.  [Installationsmöglichkeiten](#org8226795)
2.  [Notizen](#org4cce564)


<a id="org8226795"></a>

# Installationsmöglichkeiten

Installation ohne Docker mit folgenden Befehl:
```console
    ~$ apt update && apt -y upgrade 
    ~$ apt  install gcc g++ gcc-multilib gdb emacs git
    ~$ git clone https://gitlab.com/toobi7007/ss22
    ~$ cd ss22
```
Installation mit Docker:
```console
    ~$ git clone https://gitlab.com/toobi7007/ss22
    ~$ cd ss22
    ~$ docker build -t ss22 .
```
Terminal + Entwicklungsumgebung starten im Container:
```console
    ~$ docker images
    ~$ docker run -it ss22:latest
    ~$ cd ss22 && nvim Makefile
```
Docker in Emacs effektiv verwenden:
```elisp
    ;; Vorbereiten des Packagemanagers
    (require 'package) 
    (setq package-archives '(("melpa" . "https://melpa.org/packages/")
    			 ("elpa" . "https://elpa.gnu.org/packages/")))
    
    (package-initialize)
    
    (unless (package-installed-p 'use-package)
      (package-install 'use-package))
    
    (require 'use-package)
    
    ;; Nutzen des Docker Packages
    (use-package docker
      :bind ("C-c d" . docker))
    
    ;; Je nach dem ob man Evil nutzt, sollte man die Shortcuts auf Emacs stellen
    (use-package evil
      :config
      (evil-mode t)
      (dolist (state '(docker-container-mode docker-volume-mode
    		   docker-image-mode docker-network-mode))
        (evil-set-initial-state state 'emacs)))
```
Nun kann man unter Emacs mit `C-c d` oder `M-x docker` mit dem Interface arbeiten. 
Mit `?` kann man sich die Shortcuts in den jeweiligen Buffern anschauen.


<a id="org4cce564"></a>

# Notizen

1.  Praktikum ([Code 1](Praktikas/Pr1/hello1.c), [Code 2](Praktikas/Pr1/kreis.c), [Aufgabe](https://www.staff.hs-mittweida.de/~tb/intranet/SysProg/Praktikum/prakt1.html))
2.  Praktikum ([Teil 1](Praktikas/Pr2/Teilaufgabe_1.c), [Teil 2](Praktikas/Pr2/Teilaufgabe_2.c), [Teil 3](Praktikas/Pr2/Teilaufgabe_3.c), [Teil 4](Praktikas/Pr2/Teilaufgabe_4.c), [Aufgabe](https://www.staff.hs-mittweida.de/~tb/intranet/SysProg/Praktikum/prakt2.html))
3.  Praktikum ([Code Kreis](Praktikas/Pr3/kreis.c), [Code Flaeche Header](Praktikas/Pr3/flaeche.h), [Code Flaeche](Praktikas/Pr3/flaeche.c), [Aufgabe](https://www.staff.hs-mittweida.de/~tb/intranet/SysProg/Praktikum/prakt3.html))
4.  Praktikum ([Teil 1](Praktikas/Pr4/Teilaufgabe_1.c), [Teil 2](Praktikas/Pr4/Teilaufgabe_2.c), [Teil 3](Praktikas/Pr4/Teilaufgabe_3.c), [Aufgabe](https://www.staff.hs-mittweida.de/~tb/intranet/SysProg/Praktikum/prakt4.html))

