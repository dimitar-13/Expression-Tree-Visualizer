#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <array>
#include "graphics/shader_class.h"
#include <glm/glm.hpp>
constexpr size_t kSingleQuadIndexCount = 6;
constexpr size_t kSingleQuadVertexCount = 4;
constexpr size_t kTotalQuadCount = 100;

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
    void FlushBatch() { this->m_QuadVector.clear(); }
    Shader& GetShader() { return *m_BatchShader; }
    ~BatchPipeline();

    std::vector<std::array<Vertex, 4>> m_QuadVector;

private:
    BatchGpuData m_GPU_Data{};
     std::unique_ptr<Shader> m_BatchShader;
};