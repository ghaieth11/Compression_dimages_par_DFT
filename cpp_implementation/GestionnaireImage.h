#ifndef GESTIONNAIREIMAGE_H
#define GESTIONNAIREIMAGE_H

#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

class GestionnaireImage {
private:
    std::string cheminImage;
    int hauteurTronquee;
    int largeurTronquee;
    int hauteur;
    int largeur;

public:
    GestionnaireImage(const std::string& cheminImage);
    
    void chargerImage();
    void sauvegarderImage(const std::string& cheminSortie, const cv::Mat& imageFinale);
    
    std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> extraireCouleurs();
    
    cv::Mat recomposerImage(const std::vector<std::vector<int>>& r, const std::vector<std::vector<int>>& g, const std::vector<std::vector<int>>& b);
};

#endif

