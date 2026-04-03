Binome: Davy Araujo && Gabriel Corsi


# Projet TP - Cours de Programmation Système

Ce projet contient une collection d'exercices pratiques (TP) en C++ pour le cours de programmation système.

## Structure du Projet

```
.
├── TP1/          # Exercices TP1 - Classe Chrono et timespec
├── TP2/          # Exercices TP2 - Timer et Calibrator
├── TP3/          # Exercices TP3 et TP4 - Threading et Synchronisation
├── Makefile      # Fichier de compilation
└── README.md     # Ce fichier
```

## Compilation

Pour compiler un exercice spécifique, utilisez la commande `make` suivi du nom de l'exercice:

### TP1 - Classe Chrono et Timespec
```bash
make tp1

### TP2

make tp2a

make tp2b

make tp2c

make tp2de
```
Exécutables: `bin/tp2a`, `bin/tp2b`, `bin/tp2c`, `bin/tp2de`

### TP3 - Threading et Synchronisation

# Exercice TD3-c
make tp3c

# Exercice TD3-d
make tp3d

# Exercice TD3-e
make tp3e

# Exercice TD4
make tp4
```

Exécutables: `bin/tp3c`, `bin/tp3d`, `bin/tp3e`, `bin/tp4`

## Exécution

Une fois compilés, les exécutables se trouvent dans le répertoire `bin/`.

### Exemple

```bash
# Compiler TP1
make tp1

# Exécuter TP1
./bin/tp1

# Compiler et exécuter TP2a
make tp2a
./bin/tp2a

# Compiler et exécuter TP3d
make tp3d
./bin/tp3d
```

## Nettoyage

Pour supprimer tous les fichiers compilés:

make clean
### Recompilation Complète

```
make clean && make tp1 && make tp2a && make tp2b && make tp2c && make tp2de && make tp3c && make tp3d && make tp3e && make tp4
```


## Raspberry step by step

```
git clone git@github.com:davyaraujo/Temp-Reel.git
```

```
cd Temp-Reel
```

```
make clean && make tp1 && make tp2a && make tp2b && make tp2c && make tp2de && make tp3c && make tp3d && make tp3e && make tp4
```

```
rsync -avz bin/ root@192.168.50.xx:
```

```
ssh root@192.168.50.xx
```