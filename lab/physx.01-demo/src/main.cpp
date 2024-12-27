#include <PxPhysicsAPI.h>

using namespace physx;

class PhysicsDemo {
public:
    void init() {
        // Create a physics foundation
        mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallback);
        
        // Create a physics instance
        mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale());

        // Create a scene
        PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0, -9.81f, 0);
        mScene = mPhysics->createScene(sceneDesc);

        // Create material
        PxMaterial* material = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

        // Create a stack of boxes
        createStack(material);
    }

    void createStack(PxMaterial* material) {
        for (int i = 0; i < 10; ++i) {
            PxTransform transform(PxVec3(0, i * 1.0f, 0));
            PxRigidDynamic* box = mPhysics->createRigidDynamic(transform);
            PxShape* shape = PxRigidActorExt::createExclusiveShape(*box, PxBoxGeometry(0.5f, 0.5f, 0.5f), *material);
            box->setMass(1.0f);
            mScene->addActor(*box);
        }
    }

    void simulate() {
        // Simulate the scene
        mScene->simulate(1.0f / 60.0f);
        mScene->fetchResults(true);
    }

    void cleanup() {
        mScene->release();
        mPhysics->release();
        mFoundation->release();
    }

private:
    PxFoundation* mFoundation;
    PxPhysics* mPhysics;
    PxScene* mScene;
    PxDefaultAllocator mAllocator;
    PxDefaultErrorCallback mErrorCallback;
};

int main() {
    PhysicsDemo demo;
    demo.init();

    for (int i = 0; i < 60; ++i) {
        demo.simulate();
    }

    demo.cleanup();
    return 0;
}

