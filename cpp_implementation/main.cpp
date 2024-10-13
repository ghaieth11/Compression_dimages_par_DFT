#include <iostream>
#include "GestionnaireImage.h"
#include "ProcesseurImage.h"
#include "CompresseurDCT.h"
#include "AutreMethodeCompression.h"
#include "CompresseurFactory.h"
#include <opencv2/opencv.hpp>

int main() {    
    try {
        // 1. Charger l'image avec GestionnaireImage
        std::string cheminImage = "/home/user/Bureau/ProjetC++/CR7.jpg";  // Remplacez par le chemin réel
        GestionnaireImage gestionnaire(cheminImage);
        gestionnaire.chargerImage();

        // 2. Extraire les canaux de couleurs
        auto [Rouge, Vert, Bleu] = gestionnaire.extraireCouleurs();

        // Vérifier si les canaux Rouge, Vert, Bleu ne sont pas vides avant de continuer
        if (Rouge.empty() || Vert.empty() || Bleu.empty()) {
            std::cerr << "Erreur : les canaux de couleurs sont vides après l'extraction." << std::endl;
            return -1;  // Quitter le programme si les canaux sont vides
        }

        // 3. Créer un compresseur DCT simplifié via la factory
        CompresseurAbstrait* compresseurDCTSimple = CompresseurFactory::getCompresseur("DCT");

        // 4. Créer un autre compresseur avec la DCT complète
        CompresseurAbstrait* compresseurDCTComplet = CompresseurFactory::getCompresseur("Autre");

        // 5. Créer les processeurs d'image pour DCT simplifiée et DCT complète
        ProcesseurImage processeurDCTSimple(compresseurDCTSimple);
        ProcesseurImage processeurDCTComplet(compresseurDCTComplet);

        // 6. Appliquer la compression avec DCT simplifiée
        processeurDCTSimple.setCanaux(Rouge, Vert, Bleu);
        processeurDCTSimple.appliquerCompression(1);

        // 7. Appliquer la compression avec DCT complète
        processeurDCTComplet.setCanaux(Rouge, Vert, Bleu);
        processeurDCTComplet.appliquerCompression(1);

        // 8. Appliquer la décompression avec DCT simplifiée
        std::vector<std::vector<int>> rougeDecompresseSimple = compresseurDCTSimple->decompresserCanal(Rouge);
        std::vector<std::vector<int>> vertDecompresseSimple = compresseurDCTSimple->decompresserCanal(Vert);
        std::vector<std::vector<int>> bleuDecompresseSimple = compresseurDCTSimple->decompresserCanal(Bleu);

        // 9. Appliquer la décompression avec DCT complète
        std::vector<std::vector<int>> rougeDecompresseComplet = compresseurDCTComplet->decompresserCanal(Rouge);
        std::vector<std::vector<int>> vertDecompresseComplet = compresseurDCTComplet->decompresserCanal(Vert);
        std::vector<std::vector<int>> bleuDecompresseComplet = compresseurDCTComplet->decompresserCanal(Bleu);

        // 10. Vérifier si la décompression a renvoyé des matrices valides pour les deux méthodes
        if (rougeDecompresseSimple.empty() || vertDecompresseSimple.empty() || bleuDecompresseSimple.empty()) {
            std::cerr << "Erreur : décompression DCT simplifiée échouée, matrices vides." << std::endl;
            return -1;
        }
        if (rougeDecompresseComplet.empty() || vertDecompresseComplet.empty() || bleuDecompresseComplet.empty()) {
            std::cerr << "Erreur : décompression DCT complète échouée, matrices vides." << std::endl;
            return -1;
        }

        // 11. Recomposer les deux images (simplifiée et complète)
        cv::Mat imageRecomposeeSimple = gestionnaire.recomposerImage(rougeDecompresseSimple, vertDecompresseSimple, bleuDecompresseSimple);
        cv::Mat imageRecomposeeComplet = gestionnaire.recomposerImage(rougeDecompresseComplet, vertDecompresseComplet, bleuDecompresseComplet);

        // 12. Charger l'image originale pour l'afficher
        cv::Mat imageOriginale = cv::imread(cheminImage);
        if (imageOriginale.empty()) {
            std::cerr << "Erreur : impossible de charger l'image originale." << std::endl;
            return -1;
        }

        // 13. Sauvegarder les deux images décompressées
        gestionnaire.sauvegarderImage("/home/user/Bureau/Projet C++/image_decompressee_simple.png", imageRecomposeeSimple);
        gestionnaire.sauvegarderImage("/home/user/Bureau/Projet C++/image_decompressee_complet.png", imageRecomposeeComplet);

        // 14. Afficher les trois images avec des titres différents
        cv::imshow("Image Originale", imageOriginale);  // Afficher l'image originale
        cv::imshow("Image Décompressée - DCT Simplifiée", imageRecomposeeSimple);  // Afficher l'image décompressée avec DCT simplifiée
        cv::imshow("Image Décompressée - DCT Complète", imageRecomposeeComplet);   // Afficher l'image décompressée avec DCT complète

        // 15. Attendre une touche pour fermer
        cv::waitKey(0);  // Attendre que l'utilisateur appuie sur une touche pour fermer les fenêtres

        // 16. Fermer toutes les fenêtres créées
        cv::destroyAllWindows();

        // Libérer la mémoire allouée
        delete compresseurDCTSimple;
        delete compresseurDCTComplet;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
