/********************************************************************************
** Form generated from reading UI file 'ProjectEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTEDITOR_H
#define UI_PROJECTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.ProjectHierarchyViewer.h"

QT_BEGIN_NAMESPACE

class Ui_ProjectEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QLabel *labelPropertiesTitle;
    QFormLayout *formLayout;
    QLabel *labelResWidth;
    QSpinBox *spinBoxResWidth;
    QLabel *labelResHeight;
    QSpinBox *spinBoxResHeight;
    QLabel *labelFramerate;
    QSpinBox *spinBoxFramerate;
    QLineEdit *lineEditProjectName;
    QLabel *labelProjectName;
    QWidget *tab_2;
    cProjectHierarchyViewer *widget;

    void setupUi(QWidget *ProjectEditor)
    {
        if (ProjectEditor->objectName().isEmpty())
            ProjectEditor->setObjectName(QStringLiteral("ProjectEditor"));
        ProjectEditor->resize(542, 529);
        horizontalLayout = new QHBoxLayout(ProjectEditor);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(ProjectEditor);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelPropertiesTitle = new QLabel(tab);
        labelPropertiesTitle->setObjectName(QStringLiteral("labelPropertiesTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelPropertiesTitle->sizePolicy().hasHeightForWidth());
        labelPropertiesTitle->setSizePolicy(sizePolicy);
        labelPropertiesTitle->setMinimumSize(QSize(0, 0));
        labelPropertiesTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPropertiesTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelResWidth = new QLabel(tab);
        labelResWidth->setObjectName(QStringLiteral("labelResWidth"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelResWidth);

        spinBoxResWidth = new QSpinBox(tab);
        spinBoxResWidth->setObjectName(QStringLiteral("spinBoxResWidth"));
        spinBoxResWidth->setMaximum(9999);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxResWidth);

        labelResHeight = new QLabel(tab);
        labelResHeight->setObjectName(QStringLiteral("labelResHeight"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelResHeight);

        spinBoxResHeight = new QSpinBox(tab);
        spinBoxResHeight->setObjectName(QStringLiteral("spinBoxResHeight"));
        spinBoxResHeight->setMaximum(9999);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxResHeight);

        labelFramerate = new QLabel(tab);
        labelFramerate->setObjectName(QStringLiteral("labelFramerate"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelFramerate);

        spinBoxFramerate = new QSpinBox(tab);
        spinBoxFramerate->setObjectName(QStringLiteral("spinBoxFramerate"));
        spinBoxFramerate->setMaximum(999);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinBoxFramerate);

        lineEditProjectName = new QLineEdit(tab);
        lineEditProjectName->setObjectName(QStringLiteral("lineEditProjectName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditProjectName);

        labelProjectName = new QLabel(tab);
        labelProjectName->setObjectName(QStringLiteral("labelProjectName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelProjectName);


        verticalLayout->addLayout(formLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        widget = new cProjectHierarchyViewer(ProjectEditor);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(ProjectEditor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProjectEditor);
    } // setupUi

    void retranslateUi(QWidget *ProjectEditor)
    {
        ProjectEditor->setWindowTitle(QApplication::translate("ProjectEditor", "Form", nullptr));
        labelPropertiesTitle->setText(QApplication::translate("ProjectEditor", "Project Properties", nullptr));
        labelResWidth->setText(QApplication::translate("ProjectEditor", "Window width :", nullptr));
        labelResHeight->setText(QApplication::translate("ProjectEditor", "Window height :", nullptr));
        labelFramerate->setText(QApplication::translate("ProjectEditor", "Framerate Limit :", nullptr));
        labelProjectName->setText(QApplication::translate("ProjectEditor", "Project name :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ProjectEditor", "Properties", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ProjectEditor", "Screens", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectEditor: public Ui_ProjectEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTEDITOR_H
