#include "Core.ECS.Core.World.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.LayerEngine.h"

namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cWorld::~cWorld()
{
    DestroyAllEntities();

    for( int i = 0; i < mSystems.size(); ++i )
    {
        delete  mSystems[ i ];
    }
}


cWorld::cWorld() :
    mLayerEngine( 0 ),
    mUseLayerEngine( false )
{
    if( !mEntityMap )
        mEntityMap = new ::nMapping::cPhysicEntityGrid( 100, 100, 32 );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cWorld::Draw( sf::RenderTarget* iRenderTarget )
{
    if( mUseLayerEngine )
    {
        mLayerEngine->Draw( iRenderTarget );
    }
    else
    {
        for( int i = 0; i < mSystems.size(); ++i )
        {
            mSystems[ i ]->Draw( iRenderTarget );
        }
    }
}


void
cWorld::Update( unsigned int iDeltaTime )
{
    PurgeEntities();
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->Update( iDeltaTime );
    }
}


void
cWorld::SetUseLayerEngine( bool iValue )
{
    mUseLayerEngine = iValue;
    if( !mLayerEngine )
        mLayerEngine = new ::nRender::cLayerEngine();
}


void
cWorld::AddLayer()
{
    mLayerEngine->AddLayer();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cWorld::AddEntity( cEntity* iEntity )
{
    mEntity[ iEntity->ID() ] = iEntity;
    UpdateWorldWithEntity( iEntity );
    iEntity->SetWorld( this );
    iEntity->SetLoaded();
}


void
cWorld::PutEntityInLayer( cEntity * iEntity, int iLayerIndex )
{
    mLayerEngine->AddEntityInLayer( iEntity, iLayerIndex );
}


void
cWorld::UpdateWorldWithEntity( cEntity* iEntity )
{
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->IncomingEntity( iEntity );
    }
}


void
cWorld::DestroyEntity( cEntity * iEntity )
{
    mEntitiesToDestroy.push_back( iEntity );
}


void
cWorld::DestroyEntityByID( const  std::string& iID )
{
    mEntitiesToDestroy.push_back( mEntity[ iID ] );
    mEntity.erase( iID );
}


cEntity*
cWorld::GetEntityByID( const  std::string& iID )
{
    return  mEntity[ iID ];
}


cEntity*
cWorld::GetEntityAtIndex( int iIndex )
{
    auto it = mEntity.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;
    return  it->second;
}


void
cWorld::DestroyAllEntities()
{
    for( auto it : mEntity )
    {
        it.second->Destroy();
    }
    PurgeEntities();
}


void cWorld::PurgeEntities()
{
    while( mEntitiesToDestroy.size() > 0 )
    {
        cEntity* ent = mEntitiesToDestroy.back();
        RemoveEntity( ent );
        delete  ent;
        mEntitiesToDestroy.pop_back();
    }
}


bool
cWorld::IsIDUnique( const std::string & iID ) const
{
    for( auto it : mEntity )
    {
        if( it.second->ID() == iID )
            return  false;
    }

    return  true;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Systems
// -------------------------------------------------------------------------------------


void
cWorld::AddSystem( cSystem * iSystem )
{
    mSystems.push_back( iSystem );
    iSystem->mWorld = this;
    iSystem->Initialize();
    for( auto it = mEntity.begin(); it != mEntity.end(); ++it )
    {
        iSystem->IncomingEntity( it->second );
    }
}


void
cWorld::ConnectSystemToEvents( cSystem * iSystem )
{
    mEventRelatedSystems.push_back( iSystem );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


size_t
cWorld::EntityCount() const
{
    return  mEntity.size();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Private
// -------------------------------------------------------------------------------------


void
cWorld::RemoveEntity( cEntity* iEntity )
{
    mEntity.erase( iEntity->ID() );
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- EntityMap
// -------------------------------------------------------------------------------------


void
cWorld::SetEntityMapDimensions( int iWidth, int iHeight, int iCellSize )
{
    mEntityMap->SetGridDimensions( iWidth, iHeight, iCellSize );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cWorld::Resized( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->Resized( iEvent );
    }
}


void
cWorld::KeyPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->KeyPressed( iEvent );
    }
}


void
cWorld::KeyReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->KeyReleased( iEvent );
    }
}


void
cWorld::MouseWheelMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseWheelMoved( iEvent );
    }
}


void
cWorld::MouseWheelScrolled( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseWheelScrolled( iEvent );
    }
}


void
cWorld::MouseButtonPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseButtonPressed( iEvent );
    }
}


void
cWorld::MouseButtonReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseButtonReleased( iEvent );
    }
}


void
cWorld::MouseMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseMoved( iEvent );
    }
}


void
cWorld::MouseEntered( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseEntered( iEvent );
    }
}


void
cWorld::MouseLeft( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseLeft( iEvent );
    }
}


void
cWorld::JoystickButtonPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickButtonPressed( iEvent );
    }
}


void
cWorld::JoystickButtonReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickButtonReleased( iEvent );
    }
}


void
cWorld::JoystickMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickMoved( iEvent );
    }
}


void
cWorld::JoystickConnected( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickConnected( iEvent );
    }
}


void
cWorld::JoystickDisconnected( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickDisconnected( iEvent );
    }
}


void
cWorld::TouchBegan( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchBegan( iEvent );
    }
}


void
cWorld::TouchMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchMoved( iEvent );
    }
}


void
cWorld::TouchEnded( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchEnded( iEvent );
    }
}


void
cWorld::SensorChanged( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->SensorChanged( iEvent );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cWorld::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tinyxml2::XMLElement* entityMap = iDocument->NewElement( "entityMap" );
    entityMap->SetAttribute( "width", mEntityMap->Width() );
    entityMap->SetAttribute( "height", mEntityMap->Height() );
    entityMap->SetAttribute( "cellsize", mEntityMap->CellSize() );
    iNode->LinkEndChild( entityMap );

    tinyxml2::XMLElement* entities = iDocument->NewElement( "entities" );

    for( auto it = mEntity.begin(); it != mEntity.end(); ++it )
    {
        tinyxml2::XMLElement* entity = iDocument->NewElement( "entity" );
        it->second->SaveXML( entity, iDocument );
        entities->LinkEndChild( entity );
    }

    iNode->LinkEndChild( entities );
}


void
cWorld::LoadXML( tinyxml2::XMLElement* iNode )
{
    DestroyAllEntities();
    tinyxml2::XMLElement* entityMap = iNode->FirstChildElement( "entityMap" );
    int eMapWidth = entityMap->IntAttribute( "width" );
    int eMapHeight = entityMap->IntAttribute( "height" );
    int eMapCellSize = entityMap->IntAttribute( "cellsize" );

    // Loading means we want a fresh entity map and a fresh world, so if they already exist, we diss them for brand new ones
    if( mEntityMap )
        delete  mEntityMap;
    mEntityMap = new ::nMapping::cPhysicEntityGrid( eMapWidth, eMapHeight, eMapCellSize );


    tinyxml2::XMLElement* entities = iNode->FirstChildElement( "entities" );

    for( tinyxml2::XMLElement* entity = entities->FirstChildElement( "entity" ); entity; entity = entity->NextSiblingElement() )
    {
        cEntity* loadedEntity = new cEntity();
        loadedEntity->LoadXML( entity );
        AddEntity( loadedEntity );
    }
}


} // namespace nECS

