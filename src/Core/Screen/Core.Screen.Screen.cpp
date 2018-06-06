#include "Core.Screen.Screen.h"

#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.System.h"
#include "Core.ECS.Utilities.SystemRegistry.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.LayerEngine.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------

namespace nScreen {


cScreen::~cScreen()
{
}


cScreen::cScreen() :
    mName( "Unnamed" ),
    mWorld( 0 ),
    mLayerEngine( 0 ),
    mUseLayerEngine( false )
{
}


cScreen::cScreen( const std::string & iName ) :
    mName( iName ),
    mWorld( 0 ),
    mLayerEngine( 0 ),
    mUseLayerEngine( false )
{
}


void
cScreen::Initialize()
{
    if( !mWorld )
        mWorld = new ::nECS::cWorld();
}


void
cScreen::Finalize()
{
    if( mWorld )
        delete  mWorld;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Draw / Update
// -------------------------------------------------------------------------------------


void
cScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    if( mUseLayerEngine )
        mLayerEngine->Draw( iRenderTarget );
    else
        mWorld->Draw( iRenderTarget );
}


void
cScreen::Update( unsigned int iDeltaTime )
{
    mWorld->Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Layers
// -------------------------------------------------------------------------------------


void
cScreen::PutEntityInLayer( ::nECS::cEntity * iEntity, int iLayerIndex )
{
    mLayerEngine->AddEntityInLayer( iEntity, iLayerIndex );
}


void
cScreen::SetUseLayerEngine( bool iValue )
{
    mUseLayerEngine = iValue;
    if( !mLayerEngine )
        mLayerEngine = new ::nRender::cLayerEngine();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cScreen::Resized( const sf::Event& iEvent )
{
    mWorld->Resized( iEvent );
}

void
cScreen::TextEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreen::KeyPressed( const sf::Event& iEvent )
{
    mWorld->KeyPressed( iEvent );
}


void
cScreen::KeyReleased( const sf::Event& iEvent )
{
    mWorld->KeyReleased( iEvent );
}


void
cScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    mWorld->MouseWheelMoved( iEvent );
}


void
cScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    mWorld->MouseWheelScrolled( iEvent );
}


void
cScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    mWorld->MouseButtonPressed( iEvent );
}


void
cScreen::MouseButtonReleased( const sf::Event& iEvent )
{
    mWorld->MouseButtonReleased( iEvent );
}


void
cScreen::MouseMoved( const sf::Event& iEvent )
{
    mWorld->MouseMoved( iEvent );
}


void
cScreen::MouseEntered( const sf::Event& iEvent )
{
    mWorld->MouseEntered( iEvent );
}


void
cScreen::MouseLeft( const sf::Event& iEvent )
{
    mWorld->MouseLeft( iEvent );
}


void
cScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    mWorld->JoystickButtonPressed( iEvent );
}


void
cScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    mWorld->JoystickButtonReleased( iEvent );
}


void
cScreen::JoystickMoved( const sf::Event& iEvent )
{
    mWorld->JoystickMoved( iEvent );
}


void
cScreen::JoystickConnected( const sf::Event& iEvent )
{
    mWorld->JoystickConnected( iEvent );
}


void
cScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    mWorld->JoystickDisconnected( iEvent );
}


void
cScreen::TouchBegan( const sf::Event& iEvent )
{
    mWorld->TouchBegan( iEvent );
}


void
cScreen::TouchMoved( const sf::Event& iEvent )
{
    mWorld->TouchMoved( iEvent );
}


void
cScreen::TouchEnded( const sf::Event& iEvent )
{
    mWorld->TouchEnded( iEvent );
}


void
cScreen::SensorChanged( const sf::Event& iEvent )
{
    mWorld->SensorChanged( iEvent );
}


void
cScreen::SaveXML()
{
}


void
cScreen::LoadXML( const std::string& iFilePath )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFilePath.c_str() );
    if( !error )
        printf( "Cool\n" );
    else
        printf( "Error : %s\n", doc.ErrorIDToName( error ) );

    tinyxml2::XMLElement* root = doc.FirstChildElement( "screen" );

    tinyxml2::XMLElement* world = root->FirstChildElement( "world" );
    if( mWorld )
        delete  mWorld;

    mWorld = new ::nECS::cWorld();
    mWorld->LoadXML( world );

    tinyxml2::XMLElement* systems = root->FirstChildElement( "systems" );
    for( tinyxml2::XMLElement* system = systems->FirstChildElement( "system" ); system; system = system->NextSiblingElement() )
    {
        ::nECS::cSystem* sys = ::nECS::cSystemRegistry::Instance()->GetSystemByName( system->Attribute( "name" ) );
        if( sys )
        {
            mWorld->AddSystem( sys );
            if( system->BoolAttribute( "eventconnected" ) )
                mWorld->ConnectSystemToEvents( sys );
        }
    }
}


} // namespace nScreen

