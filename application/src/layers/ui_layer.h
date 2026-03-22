#pragma once
#include "layer.h"
#include "graphics_layer.h"
#include <string>
#include <memory>

class UILayer : public Layer
{
public:
    UILayer() = default;
    void Update() override;
    void Draw() override;
    void Initialize() override;
private:
    std::string m_expressionString;
    std::shared_ptr<GraphicsLayer> m_graphicsLayer;
private:
    static size_t kExpressionStringLength;
};