#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <array>
#include "graphics/shader_class.h"
#include "structs/Position2D.h"

constexpr size_t kSingleQuadIndexCount = 6;
constexpr size_t kSingleQuadVertexCount = 4;
constexpr size_t kTotalQuadCount = 100;

struct Vertex
{
    Position2D local_position{};
    Position2D world_position{};
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
    void PushCircle(Position2D position);
    void FlushBatch() { this->m_QuadVector.clear(); }
    ~BatchPipeline();

    std::vector<std::array<Vertex, 4>> m_QuadVector;

private:
    BatchGpuData m_GPU_Data{};
     std::unique_ptr<Shader> m_BatchShader;
};