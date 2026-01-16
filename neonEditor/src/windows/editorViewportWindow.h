#pragma once
#include "device.h"
#include "editorWindow.h"
#include "core/components/transformComponent.h"
#include "graphics/image.h"
#include "graphics/components/camera.h"

namespace Neon::Editor
{
class EditorViewportWindow final : public EditorWindow
{
public:
    void startup() override;
    void update()  override;
    void render()  override;
private:
    void updateFramebuffer(const Rc<RenderTarget>& renderTarget);
    void renderBillboards(ECS::Entity camEntity, const Transform& camTransform, Camera& camera);

    Box<MaterialShader> m_billboardMaterial{};
    Mesh m_screenMesh;

    Rc<RHI::Device> m_device;
    Rc<RHI::Buffer> m_matrixUniformBuffer;
    Rc<RHI::Framebuffer> m_framebuffer;

    Rc<RHI::Sampler> m_gizmoSampler;
    Rc<RHI::TextureView> m_lightTextureView{};

    bool m_wasFocused = false;
};
}
