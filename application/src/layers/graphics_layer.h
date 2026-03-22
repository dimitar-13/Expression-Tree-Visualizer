#pragma once
#include "layer.h"

class GraphicsLayer : public Layer
{
public:
    void Initialize() override;
    void Update()override;
    void Draw()override;

    void TestMethod();
};