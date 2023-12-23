#include "Inst.h"
#include "Generated/ClassRegistry.gen.h"
Actor* dynamicCastFromClass(Actor* actor)
{
    std::string classClassName = actor->className;
    if (classClassName == "TestActor") {
        Actor* test = new TestActor(*dynamic_cast<TestActor*>(actor));
        return test;
    }
    return actor;
}
