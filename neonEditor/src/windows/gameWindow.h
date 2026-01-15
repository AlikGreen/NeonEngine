#pragma once
#include "device.h"
#include "editorWindow.h"
#include "core/components/transformComponent.h"
#include "graphics/image.h"
#include "graphics/components/camera.h"

namespace Neon::Editor
{
class GameWindow final : public EditorWindow
{
public:
    void startup() override;
    void update()  override;
    void render()  override;
private:
    void renderBillboards(const Transform& camTransform, Camera& camera) const;

    Rc<RHI::Device> m_device;
    Rc<RHI::Pipeline> m_pipeline;

    Rc<RHI::Buffer> m_uniformBuffer;

    Rc<RHI::Sampler> m_gizmoSampler;
    Rc<RHI::TextureView> m_lightTextureView{};
};
}
