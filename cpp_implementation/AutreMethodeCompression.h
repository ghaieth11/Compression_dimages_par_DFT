#ifndef AUTREMETHODECOMPRESSION_H
#define AUTREMETHODECOMPRESSION_H

#include "CompresseurAbstrait.h"
#include <vector>

class AutreMethodeCompression : public CompresseurAbstrait {
public:
    AutreMethodeCompression();
    
    virtual std::vector<std::vector<int>> compresserCanal(const std::vector<std::vector<int>>& canal) override;
    virtual std::vector<std::vector<int>> decompresserCanal(const std::vector<std::vector<int>>& canal) override;
};

#endif

