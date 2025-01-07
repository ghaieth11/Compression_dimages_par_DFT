#ifndef COMPRESSEURABSTRAIT_H
#define COMPRESSEURABSTRAIT_H

#include <opencv2/opencv.hpp>
#include <string>

class CompresseurAbstrait {
public:
    virtual ~CompresseurAbstrait() = default; // Destructeur virtuel qui va garantir la destruction des objets dérivées en appelant les destructeurs spécifiques aux sous-classes

    // Méthodes virtuelles pures
    virtual cv::Mat Compression(const cv::Mat& M, const cv::Mat& Pass, int f) = 0;
    virtual cv::Mat Decompression(const cv::Mat& Mcomp, const cv::Mat& Pass) = 0;
    virtual cv::Mat Recomposition(const cv::Mat& R, const cv::Mat& V, const cv::Mat& B) = 0;
    virtual cv::Mat CalculerPass() = 0;
    virtual std::tuple<cv::Mat, cv::Mat, cv::Mat> ExtractionCouleurs(const cv::Mat& image) = 0;
};

#endif // COMPRESSEURABSTRAIT_H

/*Ce fichier nous permet de déterminer une classe abstraite pour la classe de c
compression d'image.

On inclut la biblothèque OpenCV qui est utilisé pour la manipulation des images en C++
Les images vont etre presenté par des objets de type cv::Mat qui est une strucure de données pour contenir des matrices
=> Utilisé pour stocker les pixels d'une image 


 virtual cv::Mat Compression(const cv::Mat& M, const cv::Mat& Pass, int f) = 0;

 Cette méthode va implémenter la compression d'image. Elle prend en paramètre une matrice M qui représente
 la matrice à compresser, Pass va être la matrice de passage qui va être utilisé dans la compression.
 f: paramètre de filtrage qui va influer sur le niveau de compression


virtual cv::Mat Decompression(const cv::Mat& Mcomp, const cv::Mat& Pass) = 0;

Cette méthode doit implémenter la décompression de l'image, elle prend en paramètre : 

Mcomp: La matrice représentant l'image compressée
Pass: La matrice de passage utilisé pour reconstruire l'image décompressée 

La méthode retourne une matrice cv::Mat représentant l'image decompressée.





virtual cv::Mat Recomposition(const cv::Mat& R, const cv::Mat& V, const cv::Mat& B) = 0;

Cette méthode doit reconstituer l'image à partir de ses composantes couleur rouge(R), verte(V) et bleue(B)

R,V,B sont des matrices représentant les canaux de couleurs de l'image 

La méthode retourne une matrice cv::Mat représentant l'image recomposée 



virtual cv::Mat CalculerPass() = 0;

Cette méthode doit calculer la matrice de passage utilisée dans les différents processus de compression et décompression








virtual std::tuple<cv::Mat, cv::Mat, cv::Mat> ExtractionCouleurs(const cv::Mat& image) = 0;

Cette méthode doit extraire les trois composantes de couleur (rouge,vert,bleu) d'une image
Elle prend en parametre :

Image: La matrice représentant l'image en entrée 
Et retourne un std::tuple contenant trois matrices cv::Mat représentant les caneaux rouge, vert 
et bleu de l'image.







*/ 