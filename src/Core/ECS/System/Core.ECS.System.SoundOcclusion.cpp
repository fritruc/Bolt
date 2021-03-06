 #include "Core.ECS.System.SoundOcclusion.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.OcclusionFactor.h"

#include "Core.Render.Layer.h"

#include "Core.Math.Edge.h"
#include "Core.Math.Utils.h"



namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSoundOcclusion::~cSoundOcclusion()
{
}


cSoundOcclusion::cSoundOcclusion() :
    tSuperClass( "SoundOcclusion" ),
    mListener( 0 )
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSoundOcclusion::Draw( sf::RenderTarget* iRenderTarget )
{
}


void
cSoundOcclusion::Update( unsigned int iDeltaTime )
{
    ::nMapping::cEntityGrid* entityMap = 0;
    bool applyOcclusion = false;

    for( int i = 0; i < mSoundEmitters.size(); ++i )
    {
        cEntity* entity = mSoundEmitters[ i ];

        if( entity == mListener )
            continue;

		auto layer = entity->Layer();
		if( layer )
			entityMap = layer->EntityGrid();
		else
			entityMap = mWorld->EntityMap();

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto sound = dynamic_cast< cSound* >( entity->GetComponentByName( "sound" ) );

        double finalOcclusion = 1.0F;

        std::set< cEntity* >  entitiesInBetween;
        entityMap->GetEntitiesFollowingLineFromEntityToEntity( &entitiesInBetween, mListener, entity,::nMath::cEdgeF::MakePointPoint( position->AsVector2F(), mListenerPosition->AsVector2F() ) );
        for( auto ent : entitiesInBetween )
        {
            auto occlusionfactor = dynamic_cast< cOcclusionFactor* >( ent->GetComponentByName( "occlusionfactor" ) );
            if( occlusionfactor )
            {
                finalOcclusion *= occlusionfactor->OcclusionFactor();
                applyOcclusion = !false;
            }
        }

        //if( applyOcclusion )
            sound->SetSoundOcclusionFactor( finalOcclusion );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSoundOcclusion::IncomingEntity( cEntity * iEntity )
{
    auto position           = dynamic_cast< cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto simplephysic       = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    auto occlusionfactor    = dynamic_cast< cOcclusionFactor* >( iEntity->GetComponentByName( "occlusionfactor" ) );
    auto sound              = dynamic_cast< cSound* >( iEntity->GetComponentByName( "sound" ) );

    if( position && simplephysic && ( occlusionfactor || sound ) )
    {
        AcceptEntity( iEntity );

        if( occlusionfactor )
            mSoundOccluser.push_back( iEntity );
        else if( sound )
            mSoundEmitters.push_back( iEntity );
        else
            printf( "On est pas bon la\n" );
    }

    if( position && simplephysic && iEntity->HasTag( "listener" ) )
    {
        mListener = iEntity;
        mListenerPosition = dynamic_cast< cPosition* >( mListener->GetComponentByName( "position" ) );
    }
}


} // namespace nECS

