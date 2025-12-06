#include "camera.h"


namespace Neon
{
    void Camera::setAspectRatio(const float ratio)
    {
        if(aspectRatio != ratio)
        {
            aspectRatio = ratio;
            projectionDirty = true;
        }
    }

    float Camera::getAspectRatio() const
    {
        return aspectRatio;
    }

    void Camera::setFov(const float fov)
    {
        if(this->fov != fov)
        {
            this->fov = fov;
            projectionDirty = true;
        }
    }

    float Camera::getFov() const
    {
        return fov;
    }

    void Camera::setNear(const float near)
    {
        if(nearClip != near)
        {
            nearClip = near;
            projectionDirty = true;
        }
    }

    float Camera::getNear() const
    {
        return nearClip;
    }

    void Camera::setFar(const float far)
    {
        if(farClip != far)
        {
            farClip = far;
            projectionDirty = true;
        }
    }

    float Camera::getFar() const
    {
        return farClip;
    }

    Frustum Camera::getFrustum(const glm::mat4 &view)
    {
        if(projectionDirty || view != this->viewMatrix)
        {
            this->viewMatrix = view;
            updateProjectionMatrix();
        }

        return frustum;
    }


    const glm::mat4 & Camera::getProjectionMatrix()
    {
        if (projectionDirty)
        {
            updateProjectionMatrix();
        }
        return projectionMatrix;
    }

    void Camera::updateProjectionMatrix()
    {
        projectionMatrix = glm::perspective(
            glm::radians(fov),
            aspectRatio,
            nearClip,
            farClip
        );

        frustum.update(projectionMatrix, viewMatrix);

        projectionDirty = false;
    }
}
