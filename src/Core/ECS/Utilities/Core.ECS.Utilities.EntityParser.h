#pragma once


#include <string>
#include <vector>
#include <unordered_map>


namespace nECS {


class cEntity;
class cWorld;


class cEntityParser
{
public:
    struct sPairEntityFile
    {
        sPairEntityFile() : mEntity( 0 ), mFileName( L""){}

        cEntity* mEntity;
        std::wstring mFileName;
    };


public:
    // Contruction/Destruction
    ~cEntityParser();
    cEntityParser();

public:
    // Instance
    static  cEntityParser* Instance();

public:
    // Initialize/Finalize
    void  Initialize( const std::string& iProjectDir );
    void  Finalize();

public:
    void  ReparseAll();

private:
    void  ParseFolder();

public:
    // Functions
    cEntity* CreateEntityFromFile( const std::string& iFile, cWorld* iWorld );
    cEntity* CreateEntityFromPrototypeMap( const std::string& iEntityName );

    void RegisterEntity( cEntity* iEntity );
    void UnregisterEntityByName( const std::string& iName );

    bool  IsEntityNameAValidEntityInRegistry( const std::string& iName ) const;


public:
    // Accessors--EDITOR mainly
    const std::string&  GetEntityNameAtIndex( int iIndex ) const;
    std::vector< std::string > GetEntityNamesSorted();

    const std::wstring& GetEntityFileNameAtIndex( int iIndex ) const;
    std::wstring        GetEntityFileNameByEntityName( const std::string& iName );
    void SetEntityFilenameUsingEntityName( const std::string& iEntityName, const std::wstring& iNewFilename );

    cEntity*            GetPrototypeByName( const std::string& iName );
    cEntity*            GetPrototypeAssociatedToFileName( const std::wstring& iFileName );

    unsigned int        EntityCount() const;
    bool                IsIDAvailable( const std::string& iID );

private:
    std::string                                        mEntitiesDir;
    std::unordered_map< std::string, sPairEntityFile > mEntities;

};


} // namespace ECS

