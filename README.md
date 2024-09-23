# Projet de Compression d'Image par DCT

Ce projet implémente un algorithme de **compression d'image** basé sur la **Transformée Discrète en Cosinus (DCT)**, similaire à la compression JPEG. Vous trouverez dans ce dépôt trois répertoires :

## Répertoires

1. **`python_implementation/`** : Contient l'implémentation complète en Python de l'algorithme de compression d'image utilisant la DCT. Ce répertoire inclut tous les scripts nécessaires pour décomposer l'image en blocs de 8x8, appliquer la DCT, effectuer la quantification, ainsi que la recomposition de l'image après compression.

2. **`cpp_implementation/`** : Contient l'implémentation en **C++** de l'algorithme. Cette version est optimisée pour de meilleures performances en termes de vitesse d'exécution et est utile pour des traitements d'image de grande taille.

3. **`rapport/`** : Ce répertoire contient un rapport détaillé expliquant le fonctionnement de l'algorithme, les étapes de la compression par DCT, les tests effectués et les résultats obtenus. Le rapport décrit également les différences de performance entre les implémentations Python et C++.

## Contenu des Scripts Python

- **Décomposition d'image en blocs de 8x8** : La matrice de l'image est découpée en sous-matrices de taille 8x8, facilitant l'application de la DCT.
- **Compression via DCT** : La Transformée Discrète en Cosinus est appliquée à chaque bloc, suivie d'une quantification pour réduire la précision des coefficients et ainsi compresser l'image.
- **Décompression** : L'algorithme permet de reconstruire une approximation de l'image originale après la compression.
- **Calcul du taux de compression** : Un calcul du taux de compression basé sur le nombre de coefficients annulés après la quantification est effectué.
- **Évaluation de la perte** : L'erreur de compression est mesurée pour évaluer la qualité de l'image après compression.

## Instructions d'Utilisation

1. Clonez ce dépôt :
   ```bash
   git clone https://github.com/ghaieth11/Compression_dimages_par_DFT.git
2. Exécution de l'implémentation en Python :
   ```bash
   cd python_implementation
   python main.py
3. Pour l'implémentation C++, veuillez vous rendre dans le répertoire **`cpp_implementation/`** et suivre les instructions de compilation fournies dans un fichier README spécifique.

## Auteur

Ce projet a été réalisé par **ALOUI Ghaieth**, étudiant en **Mathématiques Appliquées et Modélisation** à **POLYTECH Nice Sophia** – **Université Côte d'Azur**, dans le cadre d'un projet académique du **semestre S5**.

Les algorithmes et le code implémentés dans ce projet sont inspirés des techniques de compression d'image utilisées dans le standard **JPEG**.


