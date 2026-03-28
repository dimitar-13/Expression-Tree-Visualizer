#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <array>
#include "graphics/shader_class.h"
#include <glm/glm.hpp>
constexpr size_t kSingleQuadIndexCount = 6;
constexpr size_t kSingleQuadVertexCount = 4;
constexpr size_t kPrimitiveCount = 3;
constexpr size_t kPerPrimitiveQuadCount = 100;
constexpr size_t kTotalQuadCount = kPerPrimitiveQuadCount * kPrimitiveCount;

struct Vertex
{
    glm::vec2 local_position;
    glm::vec2 world_position;
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
    void PushCircle(glm::vec2 position);
    void PushLine(const glm::vec2& line_start,const glm::vec2& line_end);
    void FlushBatch() { this->m_CircleQuadVector.clear(); this->m_lineQuadVector.clear(); }
    Shader& GetCircleShader() { return *m_CircleShader; }
    Shader& GetLineShader() { return *m_LineShader; }

    ~BatchPipeline();
private:
    void DrawCircle();
    void DrawLine();
private:
    BatchGpuData m_GPU_Data{};
    std::unique_ptr<Shader> m_CircleShader;
    std::unique_ptr<Shader> m_LineShader;
    std::vector<std::array<Vertex, 4>> m_CircleQuadVector;
    std::vector<std::array<Vertex, 4>> m_lineQuadVector;

};