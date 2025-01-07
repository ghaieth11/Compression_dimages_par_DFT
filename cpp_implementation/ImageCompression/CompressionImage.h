#ifndef COMPRESSIONIMAGE_H
#define COMPRESSIONIMAGE_H

#include "CompresseurAbstrait.h"
#include <opencv2/opencv.hpp>
#include <tuple>
#include <vector>

class CompressionImage : public CompresseurAbstrait {
public:
    CompressionImage();
    ~CompressionImage();

    // Implémentation des méthodes abstraites
    cv::Mat Compression(const cv::Mat& M, const cv::Mat& Pass, int f) override;
    cv::Mat Decompression(const cv::Mat& Mcomp, const cv::Mat& Pass) override;
    cv::Mat Recomposition(const cv::Mat& R, const cv::Mat& V, const cv::Mat& B) override;
    cv::Mat CalculerPass() override;
    std::tuple<cv::Mat, cv::Mat, cv::Mat> ExtractionCouleurs(const cv::Mat& image) override;

private:
    std::vector<std::vector<int>> Q;  // Matrice de quantification
};

#endif // COMPRESSIONIMAGE_H

