#pragma once

class Layer
{
public:
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Draw() {};
    virtual void OnScreenResize(int newWidth, int newHeight) {};
};