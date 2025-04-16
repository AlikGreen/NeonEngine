# 0 "C:/Users/alikg/CLionProjects/neonEngine/sandboxApp/gameSystem.cpp"
# 1 "C:\\Users\\alikg\\CLionProjects\\neonEngine\\sandboxApp\\cmake-build-debug//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/alikg/CLionProjects/neonEngine/sandboxApp/gameSystem.cpp"
# 1 "C:/Users/alikg/CLionProjects/neonEngine/sandboxApp/gameSystem.h" 1
       
# 1 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/core/system.h" 1
       
# 1 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/core/event.h" 1
       

namespace Neon
{
    class Event
    {
    public:
        virtual ~Event() = default;

        void cancel()
        {
            canceled = true;
        }

        [[nodiscard]] bool isCanceled() const
        {
            return canceled;
        }
    private:
        bool canceled = false;
    };
}
# 3 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/core/system.h" 2

namespace Neon
{
    class System
    {
    public:
        virtual ~System() = default;

        virtual void startup() { }
        virtual void shutdown() { }

        virtual void preRender() { }
        virtual void postRender() { }
        virtual void render() { }

        virtual void preUpdate() { }
        virtual void postUpdate() { }
        virtual void update() { }

        virtual void event(Event* event) { }
    };
}
# 3 "C:/Users/alikg/CLionProjects/neonEngine/sandboxApp/gameSystem.h" 2


class GameSystem final : public Neon::System
{

};
# 2 "C:/Users/alikg/CLionProjects/neonEngine/sandboxApp/gameSystem.cpp" 2
