#include "Editor.BoltQtModels.ProjectHierarchyModel.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.Project.Project.h"
#include "Core.Screen.Screen.h"

#include "Core.Render.Layer.h"
#include "Core.Render.LayerEngine.h"

#include "Editor.BoltQtModels.TreeWrapperProject.h"


namespace  nQt {
namespace  nModels {


cProjectHierarchyModel::~cProjectHierarchyModel()
{
    delete  mRootItem;
}


 cProjectHierarchyModel::cProjectHierarchyModel( ::nProject::cProject* iProject, QObject* iParent ) :
    tSuperClass( iParent ),
    mProject( iProject )
{
     BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cProjectHierarchyModel::rowCount( const QModelIndex& iParent ) const
{
    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    return  parentItem->ChildrenCount();
}


int
cProjectHierarchyModel::columnCount( const QModelIndex& iParent ) const
{
    return  mRootItem->DataCount();
}


QVariant
cProjectHierarchyModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole != Qt::DisplayRole && iRole != Qt::EditRole )
        return  QVariant();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    return  item->DataAtColumn( iIndex.column() );
}


QVariant
cProjectHierarchyModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iOrientation == Qt::Horizontal && iRole == Qt::DisplayRole )
        return mRootItem->DataAtColumn( iSection );

    return  QVariant();
}


QModelIndex
cProjectHierarchyModel::index( int row, int column, const QModelIndex & iParent ) const
{
    if( iParent.isValid() && iParent.column() != 0 )
        return  QModelIndex();

    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    cTreeWrapperNode* child = parentItem->ChildAtRow( row );

    if( child )
        return  createIndex( row, column, child );

    return  QModelIndex();
}


QModelIndex
cProjectHierarchyModel::parent( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return QModelIndex();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parentItem = item->Parent();
    if( parentItem == mRootItem )
        return QModelIndex();

    return  createIndex( item->IndexInParent(), 0, parentItem );
}


Qt::ItemFlags
cProjectHierarchyModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

	auto node = ExtractTreeWrapper( iIndex  );
	if( node->Type() == "Entity" )
		return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDragEnabled;

	if( node->Type() == "Layer" )
		return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags( iIndex );
}


cTreeWrapperNode*
cProjectHierarchyModel::ExtractTreeWrapper( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return  mRootItem;

    cTreeWrapperNode* item = static_cast< cTreeWrapperNode* >( iIndex.internalPointer() );
    if( item )
        return  item;

    return  mRootItem;
}


void
cProjectHierarchyModel::BuildData()
{
    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Project Hierarchy Tree" );

    cTreeWrapperNodeHierarchyProject* projectNode = new cTreeWrapperNodeHierarchyProject( mRootItem, mProject );

    if( !mProject )
        return;

    for( int i = 0; i < mProject->ScreenCount(); ++i )
    {
        cTreeWrapperNode* screenRoot = new cTreeWrapperNode( projectNode );
        screenRoot->AppendData( "Screens" );

        ::nScreen::cScreen* screen = mProject->ScreenAtIndex( i );
        cTreeWrapperNodeHierarchyScreen* screenNode = new cTreeWrapperNodeHierarchyScreen( screenRoot, screen );

        ::nRender::cLayerEngine* layerEngine = screen->World()->LayerEngine();

        cTreeWrapperNode* layerRoot = new cTreeWrapperNode( screenNode );
        layerRoot->AppendData( "Layers" );
        for( int j = 0; j < layerEngine->LayerCount(); ++j )
        {
            ::nRender::cLayer* layer = layerEngine->LayerAtIndex( j );
            cTreeWrapperNodeHierarchyLayer* layerNode = new cTreeWrapperNodeHierarchyLayer( layerRoot, layer );

            for( int k = 0; k < layer->EntityCount(); ++k )
            {
                ::nECS::cEntity* entity = layer->EntityAtIndex( k );
                cTreeWrapperNodeHierarchyEntity* entityNode = new cTreeWrapperNodeHierarchyEntity( layerNode, entity );
            }
        }

        cTreeWrapperNode* systemRoot = new cTreeWrapperNode( screenNode );
        systemRoot->AppendData( "Systems" );
        ::nECS::cWorld* world = screen->World();
        for( int j = 0; j < world->SystemCount(); ++j )
        {
            ::nECS::cSystem* system = world->GetSystemAtIndex( j );
            cTreeWrapperNodeHierarchySystem* systemNode = new cTreeWrapperNodeHierarchySystem( systemRoot, system );
        }
    }
}


bool
cProjectHierarchyModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    if( role != Qt::EditRole )
        return false;

    cTreeWrapperNode *item = ExtractTreeWrapper( index );

    bool result = item->SetData( index.column(), value );
    if( result )
        emit dataChanged( index, index );

    return result;
}


bool
cProjectHierarchyModel::setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
    if( role != Qt::EditRole || orientation != Qt::Horizontal )
        return false;

    bool result = mRootItem->SetData( section, value );

    if( result )
        emit headerDataChanged( orientation, section, section );

    return result;
}


bool
cProjectHierarchyModel::insertColumns( int position, int columns, const QModelIndex & parent )
{
    bool success;

    beginInsertColumns( parent, position, position + columns - 1 );
    success = mRootItem->AppendColumns( position, columns );
    endInsertColumns();

    return success;
}


bool
cProjectHierarchyModel::removeColumns( int iIndex, int iCount, const QModelIndex & parent )
{
    bool success;

    beginRemoveColumns( parent, iIndex, iIndex + iCount - 1 );
    success = mRootItem->RemoveColumns( iIndex, iCount );
    endRemoveColumns();

    if( mRootItem->DataCount() == 0 )
        removeRows( 0, rowCount() );

    return success;
}


bool
cProjectHierarchyModel::insertRows( int iIndex, int iCount, const QModelIndex & parent )
{
    return false;
}


bool
cProjectHierarchyModel::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    cTreeWrapperNode *parentItem = ExtractTreeWrapper( iParent );
    bool success = true;

    beginRemoveRows( iParent, iIndex, iIndex + iCount - 1 );
    success = parentItem->RemoveChildrenAtIndex( iIndex, iCount );
    endRemoveRows();

    return success;
}


bool
cProjectHierarchyModel::moveRows( const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild )
{
	return false;
}


bool
cProjectHierarchyModel::RemoveComponent( QModelIndex & iIndex )
{
    //TODO
    //cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    //cTreeWrapperNode* parent = item->Parent();

    //if( parent && parent->Type() == "BaseNode" )
    //{
    //    beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

    //    if( item->DataAtColumn( 0 ) != "New Component" )
    //        mEntity->RemoveComponentAtIndex( iIndex.row() );

    //    parent->RemoveChildrenAtIndex( iIndex.row(), 1 );

    //    endRemoveRows();

    //    return  true;
    //}

    return  false;
}


QMimeData*
cProjectHierarchyModel::mimeData( const QModelIndexList & indexes ) const
{
	if( indexes.size() == 0 )
		return  0;

	QMimeData* mimeData = new QMimeData();
	QByteArray encodedData;

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach( const QModelIndex &index, indexes)
	{
		if( index.isValid() )
		{
			auto node = dynamic_cast< cTreeWrapperNodeHierarchyEntity* >( ExtractTreeWrapper( index ) );
			if( node )
			{
				QVariant pointerLong = (long long)(node);
				stream << pointerLong;
			}
		}
	}

	mimeData->setData("application/oui", encodedData);

	return mimeData;
}


bool
cProjectHierarchyModel::canDropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent ) const
{
	return  true;
}


bool
cProjectHierarchyModel::dropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
	auto		node		= ExtractTreeWrapper( parent );
	QByteArray	encodedData = data->data("application/oui");
	QDataStream stream( &encodedData, QIODevice::ReadOnly );

	auto parentNode = ExtractTreeWrapper( parent );

	if( parentNode->Type() == "Layer" )
	{
		auto  parentNodeAsLayer = dynamic_cast< cTreeWrapperNodeHierarchyLayer* >( parentNode );
		auto theLayer = parentNodeAsLayer->Layer();

		while ( !stream.atEnd() )
		{
			QVariant data;
			stream >> data;
			auto entityNode = (cTreeWrapperNodeHierarchyEntity*)( data.toLongLong() );

			// First remove from old layer
			auto originLayer = dynamic_cast< cTreeWrapperNodeHierarchyLayer* >( entityNode->Parent() )->Layer();
			originLayer->RemoveEntity( entityNode->Entity() );

			// Then add into the new one
			int index = theLayer->AddEntity( entityNode->Entity() );

			// Update the tree : we don't have to do the remove, it's done automatically
			auto newNode = new cTreeWrapperNodeHierarchyEntity( entityNode->Entity() );
			parentNode->InsertChild( newNode, index );
		}
	}

	return  true;
}


Qt::DropActions
cProjectHierarchyModel::supportedDropActions() const
{
	return  Qt::MoveAction;
}

} //nQt
} //nModels
