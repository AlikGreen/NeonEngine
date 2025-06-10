#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

namespace Neon
{
struct Transform
{
public:
    const glm::vec3& getPosition() const { return position; }

    void setPosition(const glm::vec3& pos)
    {
        position = pos;
        dirty = true;
    }

    const glm::vec3& getRotation() const { return rotation; }
    void setRotation(const glm::vec3& rot)
    {
        rotation = rot;
        dirty = true;
    }

    void rotate(const glm::vec3& rot)
    {
        rotation += rot;
        dirty = true;
    }

    const glm::vec3& getScale() const { return scale; }

    void setScale(const glm::vec3& scl)
    {
        scale = scl;
        dirty = true;
    }

    const glm::mat4& getMatrix() const
    {
        if (dirty)
        {
            updateMatrix();
        }
        return cachedMatrix;
    }

    glm::vec3 forward() const
    {
        return xyz((cachedRotationMatrix * glm::vec4(0, 0, 1, 0)));
    }

    glm::vec3 backward() const
    {
        return -forward();
    }

    glm::vec3 up() const
    {
        return xyz((cachedRotationMatrix * glm::vec4(0, 1, 0, 0)));
    }

    glm::vec3 down() const
    {
        return -up();
    }

    glm::vec3 right() const
    {
        return xyz((cachedRotationMatrix * glm::vec4(1, 0, 0, 0)));
    }

    glm::vec3 left() const
    {
        return -right();
    }

    void translate(const glm::vec3 translation)
    {
        position += translation;
        dirty = true;
    }
private:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{1.0f};

    mutable bool dirty = true;
    mutable glm::mat4 cachedMatrix{1.0f};
    mutable glm::mat4 cachedRotationMatrix{1.0f};
    mutable glm::mat4 cachedTranslationMatrix{1.0f};
    mutable glm::mat4 cachedScaleMatrix{1.0f};

    void updateMatrix() const
    {
        cachedTranslationMatrix = glm::translate(glm::mat4(1.0f), position);

        const glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
        const glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));
        const glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1));
        cachedRotationMatrix = Rz * Ry * Rx;

        cachedScaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        cachedMatrix = cachedTranslationMatrix * cachedRotationMatrix * cachedScaleMatrix;
        dirty = false;
    }
};
}
