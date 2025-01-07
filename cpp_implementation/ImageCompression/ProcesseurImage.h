#ifndef PROCESSEURIMAGE_H
#define PROCESSEURIMAGE_H

#include <opencv2/opencv.hpp>
#include <chrono>  // Pour la mesure du temps d'exécution
#include <string>
#include <iostream>


// Fonction pour appliquer un filtrage à un bloc 8x8
cv::Mat Filtrage(const cv::Mat& M, int f);

// Fonction pour appliquer le filtrage complet à une image
cv::Mat FiltrageComplet(const cv::Mat& M, int f);

// Fonction pour calculer le taux de compression
double TauxCompression(const cv::Mat& Rouge, const cv::Mat& Vert, const cv::Mat& Bleu, int f);

// Fonction pour calculer l'erreur de compression
double ErreurCompression(const cv::Mat& original, const cv::Mat& decompresse);

// Implémentation de la fonction template pour mesurer le temps d'exécution
template <typename Func>
void mesurerTempsExecution(const std::string& message, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();  // Exécuter la fonction passée en argument
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duree = end - start;
    std::cout << message << " : " << duree.count() << " secondes." << std::endl;
}

#endif // PROCESSEURIMAGE_H


/**
Fonction template pour mesurer le temps d'exécution d'une fonction.

 Template <typename Func> : Accepte n'importe quel type de fonction, méthode de classes, objets...
 Le template nous permet de mesurer le temps d'exécution de n'importe quelle tâche quelque soit son type ou la signature de la fonction.
 Sans template il aurait fallut surcharger la fonction à chaque fois
Paramètres 
    message : Un message pour identifier la tâche mesurée.
   Func&& func : La fonction à exécuter.   (func&&) pour accepter les objets existant comme les objets temporaires 

 auto start = std::chrono::high_resolution_clock::now()` : Capture le temps de départ.

 func() : Exécute la fonction passée en argument.

 auto end = std::chrono::high_resolution_clock::now()` : Capture le temps de fin.

std::chrono::duration<double> duree = end - start : Calcule la durée écoulée en secondes.

std::cout << message << " : " << duree.count() << " secondes." : Affiche le message et la durée.

*/

