#include "Core.Render.LayerEngine.h"

#include "Core.Render.Layer.h"


namespace nRender
{


cLayerEngine::~cLayerEngine()
{
}


cLayerEngine::cLayerEngine()
{
}


void
cLayerEngine::Draw( sf::RenderTarget * iRenderTarget )
{
    for( auto& layer : mLayers )
        layer.Draw( iRenderTarget );
}


void
cLayerEngine::AddLayer( const sf::Vector2f& iViewSize )
{
    cLayer newLayer( iViewSize );
    newLayer.Name( "Layer " + std::to_string( mLayers.size() ) );
    mLayers.push_back( newLayer );
}


void
cLayerEngine::AddLayerAtIndex( const sf::Vector2f& iViewSize, int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    mLayers.insert( it, cLayer( iViewSize ) );
}


void
cLayerEngine::SetLayersCenter( const sf::Vector2f & iLayerCenter )
{
    for( auto& layer : mLayers )
        layer.SetViewCenter( iLayerCenter );
}


void
cLayerEngine::LayerDistanceAtIndex( float iDistance, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).ZLayer( iDistance );
}


void
cLayerEngine::AddShaderToLayer( ::nShaders::cShader2D* iShader, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).AddShader( iShader );
}


int
cLayerEngine::LayerCount() const
{
    return  int(mLayers.size());
}


cLayer&
cLayerEngine::LayerAtIndex( int iLayerIndex )
{
    if( iLayerIndex < 0 || iLayerIndex > mLayers.size() )
        return  mLayers.back(); // Completely wrong, we really need to change layers to pointer in the list !!

    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    return  *it;
}


void
cLayerEngine::AddEntityInLayer( ::nECS::cEntity * iEntity, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).AddEntity( iEntity );
}


void
cLayerEngine::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument * iDocument )
{
    for( auto& layer : mLayers )
    {
        // LAYERS
        tinyxml2::XMLElement* layerNode = iDocument->NewElement( "layer" );
        layer.SaveXML( layerNode, iDocument );
        iNode->LinkEndChild( layerNode );
    }
}


void
cLayerEngine::LoadXML( tinyxml2::XMLElement * iNode )
{
    // Nothing because already done in an unsymmetrical manner by the world
}


}

