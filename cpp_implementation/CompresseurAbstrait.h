#ifndef COMPRESSEUR_ABSTRAIT_H
#define COMPRESSEUR_ABSTRAIT_H

#include <vector>

class CompresseurAbstrait {
public:
    virtual ~CompresseurAbstrait() = default;  

    virtual std::vector<std::vector<int>> compresserCanal(const std::vector<std::vector<int>>& canal) = 0;  // Méthode virtuelle pure
    virtual std::vector<std::vector<int>> decompresserCanal(const std::vector<std::vector<int>>& canal) = 0;

    void setMatriceQuantification(const std::vector<std::vector<int>>& Q);
    
protected:
    std::vector<std::vector<int>> matriceQuantification;
};

#endif

