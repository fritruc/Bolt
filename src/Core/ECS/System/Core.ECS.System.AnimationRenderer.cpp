 #include "Core.ECS.System.AnimationRenderer.h"


#include "Core.ECS.Core.Entity.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cAnimationRenderer::~cAnimationRenderer()
{
}


cAnimationRenderer::cAnimationRenderer() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::Initialize()
{
}


void
cAnimationRenderer::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::Draw( sf::RenderTarget* iRenderTarget )
{
    sf::RectangleShape rect;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position       = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size       = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );

        // Because sprite's origin is set to be the very center of the image, we need to
        // reposition it so it matches top left format given by position
        sf::Vector2f spritePos( float(position->X()), float(position->Y()) );
        spriteanimated->mSprite.setPosition( spritePos );
        spriteanimated->mSprite.setOrigin( 0,0 );
        spriteanimated->mSprite.setScale( float(size->W()) / spriteanimated->mCurrentSpriteRect.width, float(size->H()) / spriteanimated->mCurrentSpriteRect.height );
        iRenderTarget->draw( spriteanimated->mSprite );
    }
}


void
cAnimationRenderer::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );

        if( spriteanimated->Paused ())
            continue;

        if( spriteanimated->mClock.getElapsedTime().asSeconds() > 1 / spriteanimated->Framerate() )
        {
            spriteanimated->NextFrame();
            spriteanimated->mClock.restart();
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::IncomingEntity( cEntity * iEntity )
{
    auto spriteanimated = iEntity->GetComponentByName( "spriteanimated" );
    auto position = iEntity->GetComponentByName( "position" );
    auto size = iEntity->GetComponentByName( "size" );

    if( spriteanimated && position && size )
        AcceptEntity( iEntity );
}


} // namespace nECS

