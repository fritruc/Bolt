#include "Editor.BoltQtWidgets.Editors.PrototypeEditor.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.BoltQtModels.EntityModel.h"
#include "Editor.BoltQtModels.EntityListModel.h"
#include "Editor.Application.EditorApplication.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>


cPrototypeEditor::~cPrototypeEditor()
{
}


cPrototypeEditor::cPrototypeEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mEntity( 0 )
{
    ui.setupUi( this );
}


void
cPrototypeEditor::SetAllPrototypeListModel( QAbstractItemModel * iModel )
{
    ui.listViewAllPrototypes->setModel( iModel );
}


void
cPrototypeEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    mEntity = ::nECS::cEntityParser::Instance()->GetPrototypeByName( name );

    ui.listViewAllPrototypes->setCurrentIndex( iIndex );
    ui.treeViewPrototype->selectedEntitiesChanged( mEntity, new ::nQt::nModels::cEntityModel( mEntity ) );
}


void
cPrototypeEditor::PrototypeNameChanged( QString iOldName, QString iNewName )
{
    auto parser = ::nECS::cEntityParser::Instance();
    auto filename = parser->GetEntityFileNameByEntityName( iOldName.toStdString() );
    parser->UnregisterEntityByName( iOldName.toStdString() );
    parser->RegisterEntity( mEntity );
    parser->SetEntityFilenameUsingEntityName( mEntity->ID(), filename );

    ForceUpdateModel();
}


void
cPrototypeEditor::SavePrototype()
{
    if( mEntity )
    {
        std::string entityName = mEntity->ID();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( entityName == "" )
        {
            msg.setText( "Prototype name is empty" );
            msg.exec();
            return;
        }

        std::wstring filename = ::nECS::cEntityParser::Instance()->GetEntityFileNameByEntityName( entityName );
        std::string newFileName;

        if( filename == L"" )
        {
            QString pathAndFile( "./Resources/Core/Entities/" );
            pathAndFile += entityName.c_str();

            QFileDialog fileAsking( this, tr( "Save your entity" ), pathAndFile, tr( "Entity (*.entity)" ) );
            fileAsking.setDefaultSuffix( "entity" );

            if( fileAsking.exec() )
                newFileName = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            std::wstring filenameAsWString( newFileName.begin(), newFileName.end() );
            ::nECS::cEntityParser::Instance()->SetEntityFilenameUsingEntityName( entityName, filenameAsWString );
        }
        else
        {
            // Removing the old file
            std::string originalAsString = std::string( filename.begin(), filename.end() );

            if( remove( originalAsString.c_str() ) != 0 )
                perror( "Delete failed\n" );
            else
                printf( "Delete success\n" );

            newFileName = originalAsString;
        }

        // Creating the new file
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

        mEntity->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFileName.c_str() );
        if( error )
            return;

        // Model changed, we don't care where, we update everything
        ForceUpdateModel();
    }
}


void
cPrototypeEditor::SavePrototypeAs()
{
    QString pathAndFile( "./Resources/Core/Entities/" );
    pathAndFile += mEntity->ID().c_str();

    QFileDialog fileAsking( this, tr( "Save your entity" ), pathAndFile, tr( "Entity (*.entity)" ) );
    fileAsking.setDefaultSuffix( "entity" );

    std::string fullFilePath;
    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    // To get file name, and not the full path
    QFileInfo fileInfo( fullFilePath.c_str() );

    auto parser = ::nECS::cEntityParser::Instance();
    std::wstring  entityCurrentFileName = parser->GetEntityFileNameByEntityName( mEntity->ID() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "entity" );
    std::wstring filenameAsWString( fullFilePath.begin(), fullFilePath.end() );

    if( entityCurrentFileName != L"" )
    {
        ::nECS::cEntity*  entityAssociatedToRequiredFilename = parser->GetPrototypeAssociatedToFileName( filenameAsWString );

        if( entityAssociatedToRequiredFilename )
        {
            parser->UnregisterEntityByName( entityAssociatedToRequiredFilename->ID() );
        }

        ::nECS::cEntity* clone = mEntity->Clone();
        std::string newEntName = fileInfo.baseName().toStdString();
        int i = 2;
        while( parser->IsEntityNameAValidEntityInRegistry( newEntName ) )
        {
            newEntName = fileInfo.baseName().toStdString() + std::to_string( i );
            ++i;
        }
        clone->SetID( newEntName );

        parser->RegisterEntity( clone );
        clone->SaveXML( elm, &doc );
        ::nECS::cEntityParser::Instance()->SetEntityFilenameUsingEntityName( clone->ID(), filenameAsWString );
    }
    else
    {
        mEntity->SaveXML( elm, &doc );
        ::nECS::cEntityParser::Instance()->SetEntityFilenameUsingEntityName( mEntity->ID(), filenameAsWString );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.c_str() );
    if( error )
        return;

    // Model changed, we don't care where, we update everything
    ForceUpdateModel();
}


void
cPrototypeEditor::AddNewPrototype()
{
    auto modelList = dynamic_cast< ::nQt::nModels::cEntityListModel* >( ui.listViewAllPrototypes->model() );
    if( modelList )
        PrototypeEditionAsked( modelList->AddNewPrototype() );
}


void
cPrototypeEditor::RemovePrototype()
{
    // Removing the file
    auto model = dynamic_cast< ::nQt::nModels::cEntityListModel* >( ui.listViewAllPrototypes->model() );
    if( !model )
        return;

    model->RemovePrototype( ui.listViewAllPrototypes->currentIndex() );
    PrototypeEditionAsked( ui.listViewAllPrototypes->currentIndex() );
}


void
cPrototypeEditor::ProjectLoaded( ::nProject::cProject* iProject )
{
    ForceUpdateModel();
}


void
cPrototypeEditor::ForceUpdateModel()
{
    auto model = ui.listViewAllPrototypes->model();
    model->dataChanged( model->index( 0, 0 ), model->index( ::nECS::cEntityParser::Instance()->EntityCount(), 0 ) );
}


