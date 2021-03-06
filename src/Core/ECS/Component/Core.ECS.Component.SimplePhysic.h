#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>


namespace nECS {


class cSimplePhysic :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    enum eType
    {
        kStatic = 0,
        kDynamic
    };

public:
    virtual  ~cSimplePhysic();
    cSimplePhysic();
    cSimplePhysic( double iW, double iH, eType iType );
    cSimplePhysic( const cSimplePhysic& iSimplePhysic );

private:
    void BuildComponent( double iCenterX, double iCenterY, double iSizeW, double iSizeH, eType iType );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    double  CenterX();
    double  CenterY();
    sf::Vector2f CenterAsVector2f();
    void SetCenter( const sf::Vector2f& iCenter );

    double  SizeW();
    double  SizeH();
    sf::Vector2f SizeAsVector2f();
    void SetSize( const sf::Vector2f& iSize );

    sf::FloatRect RelativeHitBox();

    sf::FloatRect GetAbsoluteHitBoxUsingCenterPosition( const sf::Vector2f& iCenterPosition );
    void  InvalidCache();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f        mVelocity;
    eType               mType;

	// Cached stuff
    sf::FloatRect           mCachedHitBox;
    bool                    mIsCacheValid;
	sf::Vector2f			mCachedHitBoxCenter;
};


} // namespace nECS

