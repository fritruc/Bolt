#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

#include "Math/Edge.h"

class cSightSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSightSystem();
    cSightSystem();


    // Overrides
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;

private:
    std::vector< cEntity* >         mPointsOfInterest;

    sf::FloatRect                   mFOVBBox;
    std::vector< sf::VertexArray >  mTriangles;
    std::vector< sf::VertexArray >  mResultingSubTriangles;
    sf::VertexArray                 mInterestingHitPoints;
    sf::Transform                   mTransformationAngleSort; // This places watcher in a y,x referential, that allows to sort using angle easily

    // The watcher referential is like this :

    //        /
    //       /
    //      /
    //     /
    //    /
    //   /
    //   \
    //    \
    //     \
    //      \
    //       \
    //        \

    // This ref allows distance sorting : X axis
    //            right to left sorting : angles

    // Angles doesn't even require adjustements, as in this config, they will be sortable as is ( bissectrice being the Y axis, being the angle 0.0 )
    // It means any angle to the "left" of the watcher's bissectrice will be positive, and to the "right" negative.
    // Also, the smaller the angle, the more it is on the right ( -PI/2 is more on the right than 0.0, itself more than PI  etc)

    std::vector< sf::VertexArray >  mDEBUGClips;
    std::vector< sf::VertexArray >  mDEBUGEntities;
    std::vector< cEdgeF >           mDEBUGRays;
    sf::VertexArray                 mDEBUGHitPoints;

};
