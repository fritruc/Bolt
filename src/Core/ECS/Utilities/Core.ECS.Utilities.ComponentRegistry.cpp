#include "Core.ECS.Utilities.ComponentRegistry.h"


#include "Core.Base.Utilities.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Component.FieldOfView.h"

#include <algorithm>


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentRegistry::~cComponentRegistry()
{
}


cComponentRegistry::cComponentRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cComponentRegistry*
cComponentRegistry::Instance()
{
    static cComponentRegistry* sgComponentsRegistry = 0;
    if( !sgComponentsRegistry )
        sgComponentsRegistry = new cComponentRegistry();

    return  sgComponentsRegistry;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cComponentRegistry::Initialize( const std::string& iProjectDir )
{
    // First : The defined components are registrered
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cColor() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cDirection() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cFieldOfView() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cPosition() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSize() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSpriteAnimated() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cUserInput() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSimplePhysic() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cBehaviourTree() );

    // Then we get all file based components
    mComponentDir = iProjectDir + "/Assets/Components/";
    std::wstring path( mComponentDir.begin(), mComponentDir.end() );

    std::vector< std::wstring > fileNames;
    ::nBase::ParseDirWindows( &fileNames, path );
    tinyxml2::XMLDocument doc;

    for( int i = 0; i < fileNames.size(); ++i )
    {
        std::wstring file = fileNames[ i ];
        std::string conversion( file.begin(), file.end() );

        tinyxml2::XMLError error = doc.LoadFile( conversion.c_str() );
        if( error )
            continue;

        cComponentGeneric* component = new cComponentGeneric( conversion );
        component->LoadXML( doc.FirstChildElement( "component" ) );

        mComponents[ component->Name() ].mComponent = component;
        mComponents[ component->Name() ].mFileName = file;
        doc.Clear();
    }


}


void
cComponentRegistry::Finalize()
{
    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
        delete  it->second.mComponent;

    mComponents.clear();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


void
cComponentRegistry::RegisterComponent( cComponent * iComponent )
{
    mComponents[ iComponent->Name() ].mComponent = iComponent;
    mComponents[ iComponent->Name() ].mFileName = L"";
}


void
cComponentRegistry::UnregisterComponent( cComponent * iComponent )
{
    mComponents.erase( iComponent->Name() );
    // delete or not ?
}


void
cComponentRegistry::UnregisterComponentByName( const std::string & iName )
{
    mComponents.erase( iName );
    // delete or not ?
}


cComponent*
cComponentRegistry::CreateComponentFromName( const std::string & iName )
{
    if( !IsComponentNameAValidComponentInRegistry( iName ) )
        return  0;

    if( mComponents[ iName ].mComponent != nullptr )
        return  mComponents[ iName ].mComponent->Clone();

    return  0;
}


bool
cComponentRegistry::IsComponentNameAValidComponentInRegistry( const std::string & iName ) const
{
    auto it = mComponents.find( iName );
    if( it != mComponents.end() )
        return  true;

    return  false;
}


int
cComponentRegistry::ComponentCount()
{
    return  int(mComponents.size());
}


cComponent*
cComponentRegistry::GetComponentAtIndex( int iIndex )
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mComponents.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second.mComponent;
}


cComponent*
cComponentRegistry::GetComponentByName( const std::string & iName )
{
    if( !IsComponentNameAValidComponentInRegistry( iName ) )
        return  0;

    return  mComponents[ iName ].mComponent;
}


cComponent*
cComponentRegistry::GetComponentAssociatedToFileName( const std::wstring & iFileName )
{
    for( auto ent : mComponents )
    {
        // Going 2 ifs to simplify the reading
        if( ent.second.mFileName == L"" )
            continue;

        if( ent.second.mFileName == iFileName || iFileName.find( ent.second.mFileName ) != std::string::npos )
            return  ent.second.mComponent;
    }

    return  0;
}


std::vector<std::string>
cComponentRegistry::GetComponentNamesSorted()
{
    std::vector<std::string> output;
    output.reserve( mComponents.size() );

    for( auto comp : mComponents )
    {
        if( comp.second.mComponent )
            output.push_back( comp.second.mComponent->Name() );
    }

    std::sort( output.begin(), output.end() );

    return  output;
}


std::wstring
cComponentRegistry::GetComponentFileNameByComponentName( const std::string & iName )
{
    if( !IsComponentNameAValidComponentInRegistry( iName ) )
        return  L"";

    return  mComponents[ iName ].mFileName;
}


void
cComponentRegistry::SetComponentFilenameUsingComponentName( const std::string & iEntityName, const std::wstring & iNewFilename )
{
    if( !IsComponentNameAValidComponentInRegistry( iEntityName ) )
        return;

    mComponents[ iEntityName ].mFileName = iNewFilename;
}


bool
cComponentRegistry::IsNameAvailable( const std::string & iID )
{
    for( auto comp : mComponents )
    {
        if( comp.second.mComponent->Name() == iID )
            return  true;
    }

    return  true;
}


} // namespace ECS

