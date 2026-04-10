#include "font_resource_texture.h"
#include "stb_image.h"
#include <iostream>

FontResource::FontResource()
{
    stbi_set_flip_vertically_on_load_thread(true);

    glGenTextures(1, &m_TextureHandle);

    glBindTexture(GL_TEXTURE_2D, m_TextureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("D:/c++/Expression Tree Visualizer/vendor/resources/bitmap_img/charmap-cellphone_black.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    this->SetupCharacterMap();
}

FontResource::~FontResource()
{
    glDeleteTextures(1, &m_TextureHandle);
}

FontTextureCoordinates FontResource::GetCoordinates(char character)
{
    return m_characterTextureCoordinatesMap[character];
}

void FontResource::SetupCharacterMap()
{
    constexpr glm::vec2 kSingleCharSize = { 5.0f, 7.0f };
    constexpr glm::vec2 kTextureSize = { 128.0f, 64.0f };

    float currentY = kTextureSize.y - kSingleCharSize.y - 1.0f;
    float currentX = 1.0f;

    for (char i = ' '; i <= '~'; i++)
    {
        FontTextureCoordinates character_coords;

        character_coords.start = glm::vec2(currentX, currentY) / kTextureSize;

        character_coords.end = glm::vec2(currentX + kSingleCharSize.x,
            currentY + kSingleCharSize.y) / kTextureSize;

        m_characterTextureCoordinatesMap[i] = character_coords;

        currentX += kSingleCharSize.x + 2.0f;

        if (currentX + kSingleCharSize.x > kTextureSize.x)
        {
            currentX = 1.0f;

            currentY -= (kSingleCharSize.y + 2.0f);
        }
    }
}
