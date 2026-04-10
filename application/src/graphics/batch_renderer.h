#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <array>
#include "graphics/shader_class.h"
#include <glm/glm.hpp>
#include "graphics/font_resource_texture.h"

constexpr size_t kSingleQuadIndexCount = 6;
constexpr size_t kSingleQuadVertexCount = 4;
constexpr size_t kPrimitiveCount = 3;
constexpr size_t kPerPrimitiveQuadCount = 100;
constexpr size_t kTotalQuadCount = kPerPrimitiveQuadCount * kPrimitiveCount;

struct Vertex
{
    glm::vec2 local_position;
    glm::vec2 world_position;
    glm::vec2 texture_coordinates;
};

struct BatchGpuData
{
    GLuint vertex_buffer_handle{};
    GLuint vertex_attribute_array_handle{};
    GLuint index_buffer_handle{};
};

class BatchPipeline
{
public:
    static constexpr size_t kBatchVertexArraySize = kSingleQuadVertexCount * kTotalQuadCount;
    static constexpr size_t kBatchIndexArraySize = kSingleQuadIndexCount * kTotalQuadCount;

    BatchPipeline();
    void Draw();
    void PushCircle(const glm::vec2& position,const glm::vec2& scale = glm::vec2(20.f));
    void PushLine(const glm::vec2& line_start,const glm::vec2& line_end);
    void PushCharacter(const glm::vec2& char_position, char character,const glm::vec2& scale = glm::vec2(20.f));
    void FlushBatch() { this->m_CircleQuadVector.clear(); this->m_lineQuadVector.clear(); this->m_fontQuadVector.clear(); }
    Shader& GetCircleShader() { return *m_CircleShader; }
    Shader& GetLineShader() { return *m_LineShader; }

    void SetProjectionMatrix(const glm::mat4& projection_matrix) { m_ProjectionMatrix = projection_matrix; }
    ~BatchPipeline();
private:
    void ApplyProject(std::array<Vertex, 4>& quad);
    void DrawCircle();
    void DrawLine();
    void DrawFont();
private:
    BatchGpuData m_GPU_Data{};
    std::unique_ptr<Shader> m_CircleShader;
    std::unique_ptr<Shader> m_LineShader;
    std::unique_ptr<Shader> m_FontShader;

    std::vector<std::array<Vertex, 4>> m_CircleQuadVector;
    std::vector<std::array<Vertex, 4>> m_lineQuadVector;
    std::vector<std::array<Vertex, 4>> m_fontQuadVector;

    FontResource m_FontResource;

    glm::mat4 m_ProjectionMatrix;
};