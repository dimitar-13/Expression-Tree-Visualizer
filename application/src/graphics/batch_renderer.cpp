#include "batch_renderer.h"
#include <assert.h>
#include <algorithm>

BatchPipeline::BatchPipeline()
{
    glGenVertexArrays(1, &this->m_GPU_Data.vertex_attribute_array_handle);
    glGenBuffers(1, &this->m_GPU_Data.vertex_buffer_handle);
    glGenBuffers(1, &this->m_GPU_Data.index_buffer_handle);

    glBindVertexArray(this->m_GPU_Data.vertex_attribute_array_handle);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_GPU_Data.vertex_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, kBatchVertexArraySize * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    std::array<GLuint, kBatchIndexArraySize> index_array{};
    GLuint index_buffer_index = 0;
    size_t i = 0;
    size_t quad_counter = 0;

    while (quad_counter < kTotalQuadCount)
    {
        index_array[i] = index_buffer_index;
        index_array[i + 1] = index_buffer_index + 1;
        index_array[i + 2] = index_buffer_index + 2;

        index_array[i + 3] = index_buffer_index + 2;
        index_array[i + 4] = index_buffer_index + 3;
        index_array[i + 5] = index_buffer_index;

        quad_counter++;
        index_buffer_index += 4;
        i += 6;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_GPU_Data.index_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_array), index_array.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, local_position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, world_position));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->m_QuadVector.reserve(kTotalQuadCount);
    this->m_BatchShader = std::make_unique<Shader>("D:/c++/Expression Tree Visualizer/application/shaders/test_shader.glsl");
}
void BatchPipeline::Draw()
{
    if (this->m_QuadVector.empty()) return;

    this->m_BatchShader->UserProgram();

    size_t vertex_count = this->m_QuadVector.size() * 4;

    glBindVertexArray(this->m_GPU_Data.vertex_attribute_array_handle);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_GPU_Data.vertex_buffer_handle);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), this->m_QuadVector.data());

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_QuadVector.size() * kSingleQuadIndexCount), GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchPipeline::PushCircle(Position2D position)
{

    std::array<Vertex, 4> vertex_data = {
        Vertex{ Position2D{-0.1f, -0.1f},Position2D{ -0.1f, -0.1f},},
        Vertex{ Position2D{0.1f, -0.1f  },Position2D{ 0.1f, -0.1f }},
        Vertex{Position2D{0.1f, 0.1f}, Position2D{ 0.1f, 0.1f}},
        Vertex{Position2D{-0.1f, 0.1f},Position2D{ -0.1f, 0.1f},}
    };

    for (auto& vertex : vertex_data)
    {
        vertex.world_position += position;
    }

    if (this->m_QuadVector.size() >= kTotalQuadCount)
    {
        assert(false);
        return;
    }
    this->m_QuadVector.emplace_back(vertex_data);
}

BatchPipeline::~BatchPipeline()
{
    glDeleteBuffers(1, &this->m_GPU_Data.vertex_buffer_handle);
    glDeleteBuffers(1, &this->m_GPU_Data.index_buffer_handle);
    glDeleteVertexArrays(1, &this->m_GPU_Data.vertex_attribute_array_handle);
}
