#ifndef COMPRESSEURDCT_H
#define COMPRESSEURDCT_H

#include "CompresseurAbstrait.h"
#include <vector>

class CompresseurDCT : public CompresseurAbstrait {
public:
    std::vector<std::vector<int>> compresserCanal(const std::vector<std::vector<int>>& canal) override;
    std::vector<std::vector<int>> decompresserCanal(const std::vector<std::vector<int>>& canal) override;
};

#endif

