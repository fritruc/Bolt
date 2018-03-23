﻿#pragma once

#include "Volumetric/Static1664/VUtils.h"

namespace  nVolumetric
{

void
GenFace( eNF_Index iFace, int iIndex, std::vector< sf::Vector3f >& iData, int iX, int iY, int iZ )
{
    float x = float( iX );
    float y = float( iY );
    float z = float( iZ );

    switch( iFace )
    {
    case kIndexTop:
        GenTopFace( iData, iIndex, x, y, z );
        break;
    case kIndexBot:
        GenBotFace( iData, iIndex, x, y, z );
        break;
    case kIndexFront:
        GenFrontFace( iData, iIndex, x, y, z );
        break;
    case kIndexBack:
        GenBackFace( iData, iIndex, x, y, z );
        break;
    case kIndexLeft:
        GenLeftFace( iData, iIndex, x, y, z );
        break;
    case kIndexRight:
        GenRightFace( iData, iIndex, x, y, z );
        break;
    }
}


void
GenTopFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


void
GenBotFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


void
GenFrontFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


void
GenBackFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


void
GenLeftFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


void
GenRightFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f, iY, iZ );
    iData[ iIndex++ ]   = sf::Vector3f( iX, iY, iZ + 1.f );
}


} // namespace  nVolumetric
