#pragma once

#include <QtCore/QAbstractListModel>

namespace  nECS { class cEntityParser; }
namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nModels {

class  cEntityListModel :
    public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QAbstractListModel tSuperClass;

public:
    cEntityListModel( QObject* iParent = 0 );

public:
    // Interface overrides
    virtual  int rowCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;
    virtual  QVariant headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const override;

    QModelIndex  AddNewPrototype();
    void RemovePrototype( QModelIndex& iIndex );
    QModelIndex  GetPrototypeIndex( ::nECS::cEntity* iPrototype );


private:
    ::nECS::cEntityParser* mParserInstance;
};

} //nQt
} //nModels
