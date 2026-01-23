module test_system;
import system;
import scene_management;
import input;
import log;

class TestSystem : System
{
    public override void update()
    {
        Scene scene = SceneManager.getCurrentScene();
        auto view = scene.view!(Transform, Camera)();

        if (Input.isKeyHeld(KeyCode.w))
        {
            foreach (entity, transform, camera; view)
            {
                transform.position.z += 0.01f;
                Log.info("[%s] Position: (%s)", entity, transform.position);
            }
        }
    }
}
