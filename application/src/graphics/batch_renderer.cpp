#include "batch_renderer.h"
#include <assert.h>
#include <algorithm>


static constexpr float kScaleFactor = 30.f;

static constexpr std::array<Vertex, 4> kDefaultVertexData = {
    Vertex{ glm::vec2{-1.f, -1.f},glm::vec2{ -1.f, -1.f},},
    Vertex{ glm::vec2{1.f, -1.f  },glm::vec2{ 1.f, -1.f }},
    Vertex{glm::vec2{1.f, 1.f}, glm::vec2{ 1.f, 1.f}},
    Vertex{glm::vec2{-1.f, 1.f},glm::vec2{ -1.f, 1.f},}
};

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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, local_position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, world_position));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->m_CircleQuadVector.reserve(kPerPrimitiveQuadCount);
    this->m_lineQuadVector.reserve(kPerPrimitiveQuadCount);
    this->m_CircleShader = std::make_unique<Shader>("D:/c++/Expression Tree Visualizer/application/shaders/circle_shader.glsl");
    this->m_LineShader = std::make_unique<Shader>("D:/c++/Expression Tree Visualizer/application/shaders/line_shader.glsl");
}
void BatchPipeline::Draw()
{
    this->DrawLine();
    this->DrawCircle();
}

void BatchPipeline::PushCircle(glm::vec2 position)
{
    std::array<Vertex, 4> vertex_data_copy = kDefaultVertexData;

    for (auto& vertex : vertex_data_copy)
    {
        vertex.world_position *= kScaleFactor;
        vertex.world_position += position;
    }

    if (this->m_CircleQuadVector.size() >= kPerPrimitiveQuadCount)
    {
        assert(false);
        return;
    }
    this->m_CircleQuadVector.emplace_back(vertex_data_copy);
}

void BatchPipeline::PushLine(const glm::vec2& line_start, const glm::vec2& line_end)
{
    std::array<Vertex, 4> vertex_data_copy = kDefaultVertexData;

    vertex_data_copy[0].world_position = line_start;
    vertex_data_copy[1].world_position = { line_end.x,line_start.y};
    vertex_data_copy[2].world_position = line_end;
    vertex_data_copy[3].world_position = { line_start.x,line_end.y };

    if (this->m_lineQuadVector.size() >= kPerPrimitiveQuadCount)
    {
        assert(false);
        return;
    }
    this->m_lineQuadVector.emplace_back(vertex_data_copy);

}

BatchPipeline::~BatchPipeline()
{
    glDeleteBuffers(1, &this->m_GPU_Data.vertex_buffer_handle);
    glDeleteBuffers(1, &this->m_GPU_Data.index_buffer_handle);
    glDeleteVertexArrays(1, &this->m_GPU_Data.vertex_attribute_array_handle);
}

void BatchPipeline::DrawCircle()
{
    size_t circle_count = this->m_CircleQuadVector.size();
    if (circle_count == 0)
    {
        return;
    }

    this->m_CircleShader->UserProgram();

    size_t vertex_count = circle_count * 4;

    glBindVertexArray(this->m_GPU_Data.vertex_attribute_array_handle);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_GPU_Data.vertex_buffer_handle);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), this->m_CircleQuadVector.data());

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(circle_count * kSingleQuadIndexCount), GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchPipeline::DrawLine()
{
    size_t line_count = this->m_lineQuadVector.size();
    if (line_count == 0)
    {
        return;
    }
    this->m_LineShader->UserProgram();

    size_t vertex_count = line_count * 4;

    glBindVertexArray(this->m_GPU_Data.vertex_attribute_array_handle);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_GPU_Data.vertex_buffer_handle);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), this->m_lineQuadVector.data());

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(line_count * kSingleQuadIndexCount), GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
