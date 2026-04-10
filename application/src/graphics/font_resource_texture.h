#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <glm/glm.hpp>

struct FontTextureCoordinates
{
    glm::vec2 start;
    glm::vec2 end;
};

class FontResource
{
public:
    FontResource();
    ~FontResource();

    void BindTexture() const { glBindTexture(GL_TEXTURE_2D, m_TextureHandle); }
    FontTextureCoordinates GetCoordinates(char character);
private:
    void SetupCharacterMap();
private:
    GLuint m_TextureHandle;
    std::unordered_map<char, FontTextureCoordinates> m_characterTextureCoordinatesMap;
};