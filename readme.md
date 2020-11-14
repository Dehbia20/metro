# Projet de simumation d'une station de métro

Ce projet est réalisé par :<br/>

- Djebarri Dehbia

Le projet est réalisé avec le language C et la bibliothèque SDL.<br/>
Les concepts suivants seront abordés :

- les structures
- les tableaux
- l'allocation dynamique de mémoire

## stucture du projet

<pre>project
├── .vscode/
│   ├── *settings*.json
├── build
│   ├── metro.exe
│   └── *.dll
└── debug
│   ├── *.dll
│   ├── *.exe
└── sdk
│   ├── **
└── src
│   ├── *.c
└── build.sh
└── makefile
└── readme.md</pre>

- Le dossier `.vscode` contient la configuration nécessaire pour build et debug le projet sous vscode
- Le dossier `build` contient l'executable construit avec les libraires tierces (exemple la SDL 2)
- Le dossier `debug` contient les sources compilées servant au debug sous vscode
  - **Important** Ce dossier n'est utile que pour le développement
- Le dossier `sdk` contient les librairie tierces (dll, header, link...)
- Le dossier `src`contient les sources du projet
- Le fichier `build.sh`permet de construire un executable (le contenu du dossier build)
- Le fichier `makefile` décrit comment les sources sont assemblées
