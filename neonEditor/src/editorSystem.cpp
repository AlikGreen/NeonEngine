#include "editorSystem.h"


#include "audio/components/audioSource.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/image.h"
#include "graphics/imGuiSystem.h"
#include "graphics/events/dropFileEvent.h"
#include "neonEngine/neonEngine.h"
#include "windows/assetsWindow.h"
#include "windows/propertiesWindow.h"
#include "windows/sceneGraphWindow.h"

namespace Neon::Editor
{
    void EditorSystem::startup()
    {
        auto& scene = Engine::getSceneManager().getCurrentScene();

        AssetManager& assetManager = Engine::getAssetManager();
        auto model = assetManager.import<Prefab>("models/monkey.glb");

        ECS::Entity modelEntity = scene.import(model.get());
        modelEntity.get<Tag>().name = "Imported model";
        modelEntity.get<Transform>().setScale(glm::vec3(1.0f));


        auto skyboxData =  assetManager.loadUnmanaged<TextureData>("textures/skybox.hdr");
        const Rc<RHI::Texture> skyboxTexture = assetManager.addAsset(Image(*skyboxData.release()), "Skybox Image")->texture;
        const auto skyboxTexViewDesc = RHI::TextureViewDescription(skyboxTexture);
        const Rc<RHI::TextureView> skyboxTextureView = Engine::getSystem<GraphicsSystem>()->getDevice()->createTextureView(skyboxTexViewDesc);

        MaterialShader skyboxMaterial = MaterialShader::createEquirectangularSkybox();
        skyboxMaterial.setTexture("skyboxTexture", skyboxTextureView);
        const AssetRef<MaterialShader> skyboxMaterialAsset = assetManager.addAsset<MaterialShader>(skyboxMaterial);

        // Player/Camera entity
        ECS::Entity cameraEntity = scene.createEntity("Main Camera");
        auto& camera = cameraEntity.emplace<Camera>();
        camera.skyboxMaterial = skyboxMaterialAsset;
        camera.renderTarget = Engine::getSystem<GraphicsSystem>()->createRenderTarget(800, 600);
        auto& camTransform = cameraEntity.get<Transform>();
        camTransform.setPosition({0, 0, 0});

        // Light entity
        ECS::Entity lightEntity = scene.createEntity("Light");
        auto& lightTransform = lightEntity.get<Transform>();
        lightTransform.setPosition({8, 10, 8});

        lightEntity.emplace<PointLight>();
        auto& pointLight = lightEntity.get<PointLight>();
        pointLight.power = 10.0f;
        pointLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

        // const AssetRef<AudioClip> music = assetManager.loadAsset<AudioClip>("music.mp3");
        // ECS::Entity speakerEntity = scene.createEntity("Speaker");
        // auto& audioSource = speakerEntity.emplace<AudioSource>();
        // audioSource.clip = music;
        // audioSource.loop = true;
        // audioSource.play();

        registerComponent<MeshRenderer>("Mesh Renderer");
        registerComponent<PointLight>("Point Light");
        registerComponent<Camera>("Camera");


        auto* imGuiSystem = Engine::getSystem<ImGuiSystem>();

        imGuiSystem->shouldDrawDockSpace = true;
        imGuiSystem->shouldDrawConsole = true;
        imGuiSystem->shouldDrawStats = true;

        imGuiSystem->addRenderCallback([this]()
        {
            viewportWindow.render();
            sceneGraphWindow.render();
            assetsWindow.render();
            propertiesWindow.render();
            editorViewport.render();
        });

        auto data = assetManager.serialize();
        assetManager.deserialize(data);
    }

    void EditorSystem::update()
    {

    }

    void EditorSystem::event(Event* event)
    {
        if(const auto* windowEvent = dynamic_cast<DropFileEvent*>(event))
        {
            assetsWindow.dropFile(windowEvent->getPath());
        }
    }

    std::vector<ComponentInfo> EditorSystem::getComponents()
    {
        return registeredComponents;
    }
}
