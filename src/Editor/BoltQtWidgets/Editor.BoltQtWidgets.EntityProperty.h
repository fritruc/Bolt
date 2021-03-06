#pragma once

#include "ui_EntityPropertyWidget.h"

#include <QModelIndex>
#include <QStyledItemDelegate>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }
namespace  nQt { namespace  nModels { class cEntityModel; } }

class  cEntityPropertyDelegate;

class cEntityProperty :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cEntityProperty();
    cEntityProperty( QWidget *parent = Q_NULLPTR );

public:
    QString GetEntityName();

signals:
    void  EntityNameChanged( QString iOldName, QString iNewName );

public slots :
    void selectedEntitiesChanged( ::nECS::cEntity* iEntity, ::nQt::nModels::cEntityModel* iModel );
    void addEmptyComponent();
    void removeComponent();
    void EntityIDChanged();

private:
    Ui::EntityProperty ui;
    cEntityPropertyDelegate* mComboDelegate;

    ::nQt::nModels::cEntityModel* mModel;
    ::nECS::cEntity* mEntity;
    std::string  mEntityName;
};


// ==================================================================
// ==================================================================
// ==================================================================


class  cEntityPropertyDelegate :
    public  QStyledItemDelegate
{
public:
    typedef QStyledItemDelegate tSuperClass;

public:
    cEntityPropertyDelegate( QWidget* iParent = 0 );

public:
    // Overrides
    QWidget* createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
    void    setEditorData( QWidget *editor, const QModelIndex &index ) const override;
    void    setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const override;

public:
    void SetEntity( ::nECS::cEntity* iEntity );

private:
    ::nECS::cEntity* mEntity;
};




