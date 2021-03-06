#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <unordered_map>
#include <functional>


namespace nRender { class cLayer; }
namespace nRender { class cLayerEngine; }
namespace nMapping { class cEntityGrid; }

namespace nECS {


class cEntity;
class cSystem;


class cWorld
{
public:
    // Contruction/Destruction
    ~cWorld();
    cWorld();

public:
    // Update/Draw
    void  Draw( sf::RenderTarget* iRenderTarget );
    void  Update( unsigned int iDeltaTime );

public:
    // Config
    void  SetUseLayerEngine( bool iValue );

public:
    // Layers
    ::nRender::cLayerEngine* LayerEngine();
    void  AddLayer( const sf::Vector2f& iViewSize, float iDistance );
    void  PutEntityInLayer( cEntity* iEntity, int iLayerIndex );

	void  LayersEnumerator( std::function< void( ::nRender::cLayer* ) > iFunction );

public:
    // Entity
    void  AddEntity( cEntity* iEntity );
    void  UpdateWorldWithEntity( cEntity* iEntity );
    void  DestroyEntity( cEntity* iEntity );
    void  DestroyEntityByID( const  std::string& iID );
    cEntity*  GetEntityByID( const  std::string& iID );
    cEntity*  GetEntityAtIndex( int iIndex );
    void  DestroyAllEntities();
    void  PurgeEntities();

	void  EntityEnumerator( std::function< void( cEntity* ) > iEnumeratorFunction );

    bool IsIDUnique( const std::string& iID ) const;

public:
    // Systems
    void        AddSystem( cSystem* iSystem );
    void        ConnectSystemToEvents( cSystem* iSystem );
    cSystem*    GetSystemAtIndex( int iIndex );

public:
    // Access
    int EntityCount() const;
    int SystemCount() const;

private:
    // Private
    void  RemoveEntity( cEntity* iEntity );

public:
    // EntityMap
    void						SetEntityMapDimensions( int iWidth, int iHeight, int iCellSize );
    ::nMapping::cEntityGrid*	EntityMap();
	void						EntityMapEnumerator( std::function< void( ::nMapping::cEntityGrid* iEntityGrid ) > iFunction );

public:
    // Events
    void  Resized( const sf::Event& iEvent );                ///< The window was resized (data in event.size)
    void  KeyPressed( const sf::Event& iEvent );             ///< A key was pressed (data in event.key)
    void  KeyReleased( const sf::Event& iEvent );            ///< A key was released (data in event.key)
    void  MouseWheelMoved( const sf::Event& iEvent );        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    void  MouseWheelScrolled( const sf::Event& iEvent );     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    void  MouseButtonPressed( const sf::Event& iEvent );     ///< A mouse button was pressed (data in event.mouseButton)
    void  MouseButtonReleased( const sf::Event& iEvent );    ///< A mouse button was released (data in event.mouseButton)
    void  MouseMoved( const sf::Event& iEvent );             ///< The mouse cursor moved (data in event.mouseMove)
    void  MouseEntered( const sf::Event& iEvent );           ///< The mouse cursor entered the area of the window (no data)
    void  MouseLeft( const sf::Event& iEvent );              ///< The mouse cursor left the area of the window (no data)
    void  JoystickButtonPressed( const sf::Event& iEvent );  ///< A joystick button was pressed (data in event.joystickButton)
    void  JoystickButtonReleased( const sf::Event& iEvent ); ///< A joystick button was released (data in event.joystickButton)
    void  JoystickMoved( const sf::Event& iEvent );          ///< The joystick moved along an axis (data in event.joystickMove)
    void  JoystickConnected( const sf::Event& iEvent );      ///< A joystick was connected (data in event.joystickConnect)
    void  JoystickDisconnected( const sf::Event& iEvent );   ///< A joystick was disconnected (data in event.joystickConnect)
    void  TouchBegan( const sf::Event& iEvent );             ///< A touch event began (data in event.touch)
    void  TouchMoved( const sf::Event& iEvent );             ///< A touch moved (data in event.touch)
    void  TouchEnded( const sf::Event& iEvent );             ///< A touch event ended (data in event.touch)
    void  SensorChanged( const sf::Event& iEvent );          ///< A sensor value changed (data in event.sensor)

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::unordered_map< std::string, cEntity* > mEntity;
    std::vector< cEntity* > mEntitiesToDestroy;

    std::vector< cSystem* > mSystems;
    std::vector< cSystem* > mEventRelatedSystems;

    ::nMapping::cEntityGrid*    mEntityMap;

public: // TEMP until main camera thing
    ::nRender::cLayerEngine*    mLayerEngine;
    bool                        mUseLayerEngine;
};


} // namespace nECS


