/********************************************************************************
** Form generated from reading UI file 'w_levelScheme.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_LEVELSCHEME_H
#define UI_W_LEVELSCHEME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LevelScheme
{
public:
    QAction *actionss;
    QAction *actiondd;
    QAction *actiond;
    QAction *actionds;
    QAction *actionfaf;
    QAction *actioniso_1;
    QAction *actioniso_2;
    QAction *actioniso_3;
    QAction *action_savePic;
    QAction *actioniso1;
    QAction *actioniso2;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuother_isotopes;
    QMenu *menuedit_levels;
    QMenu *menu_savePic;

    void setupUi(QMainWindow *LevelScheme)
    {
        if (LevelScheme->objectName().isEmpty())
            LevelScheme->setObjectName("LevelScheme");
        LevelScheme->resize(579, 494);
        LevelScheme->setMinimumSize(QSize(400, 0));
        LevelScheme->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionss = new QAction(LevelScheme);
        actionss->setObjectName("actionss");
        actiondd = new QAction(LevelScheme);
        actiondd->setObjectName("actiondd");
        actiond = new QAction(LevelScheme);
        actiond->setObjectName("actiond");
        actionds = new QAction(LevelScheme);
        actionds->setObjectName("actionds");
        actionfaf = new QAction(LevelScheme);
        actionfaf->setObjectName("actionfaf");
        actioniso_1 = new QAction(LevelScheme);
        actioniso_1->setObjectName("actioniso_1");
        actioniso_2 = new QAction(LevelScheme);
        actioniso_2->setObjectName("actioniso_2");
        actioniso_3 = new QAction(LevelScheme);
        actioniso_3->setObjectName("actioniso_3");
        action_savePic = new QAction(LevelScheme);
        action_savePic->setObjectName("action_savePic");
        action_savePic->setMenuRole(QAction::NoRole);
        actioniso1 = new QAction(LevelScheme);
        actioniso1->setObjectName("actioniso1");
        actioniso1->setCheckable(true);
        actioniso2 = new QAction(LevelScheme);
        actioniso2->setObjectName("actioniso2");
        actioniso2->setCheckable(true);
        centralwidget = new QWidget(LevelScheme);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");

        horizontalLayout->addWidget(graphicsView);

        LevelScheme->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(LevelScheme);
        statusbar->setObjectName("statusbar");
        LevelScheme->setStatusBar(statusbar);
        toolBar = new QToolBar(LevelScheme);
        toolBar->setObjectName("toolBar");
        LevelScheme->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);
        menuBar = new QMenuBar(LevelScheme);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 579, 21));
        menuBar->setLayoutDirection(Qt::LeftToRight);
        menuother_isotopes = new QMenu(menuBar);
        menuother_isotopes->setObjectName("menuother_isotopes");
        menuother_isotopes->setLayoutDirection(Qt::LeftToRight);
        menuedit_levels = new QMenu(menuBar);
        menuedit_levels->setObjectName("menuedit_levels");
        menu_savePic = new QMenu(menuBar);
        menu_savePic->setObjectName("menu_savePic");
        LevelScheme->setMenuBar(menuBar);

        toolBar->addAction(action_savePic);
        menuBar->addAction(menuother_isotopes->menuAction());
        menuBar->addAction(menu_savePic->menuAction());
        menuBar->addAction(menuedit_levels->menuAction());
        menuother_isotopes->addAction(actioniso1);
        menuother_isotopes->addAction(actioniso2);

        retranslateUi(LevelScheme);

        QMetaObject::connectSlotsByName(LevelScheme);
    } // setupUi

    void retranslateUi(QMainWindow *LevelScheme)
    {
        LevelScheme->setWindowTitle(QCoreApplication::translate("LevelScheme", "LevelSchemeWindow", nullptr));
        actionss->setText(QCoreApplication::translate("LevelScheme", "ss", nullptr));
        actiondd->setText(QCoreApplication::translate("LevelScheme", "dd", nullptr));
        actiond->setText(QCoreApplication::translate("LevelScheme", "d", nullptr));
        actionds->setText(QCoreApplication::translate("LevelScheme", "ds", nullptr));
        actionfaf->setText(QCoreApplication::translate("LevelScheme", "faf", nullptr));
        actioniso_1->setText(QCoreApplication::translate("LevelScheme", "iso 1", nullptr));
        actioniso_2->setText(QCoreApplication::translate("LevelScheme", "iso 2", nullptr));
        actioniso_3->setText(QCoreApplication::translate("LevelScheme", "iso 3", nullptr));
        action_savePic->setText(QCoreApplication::translate("LevelScheme", "Save Picture", nullptr));
        actioniso1->setText(QCoreApplication::translate("LevelScheme", "iso1", nullptr));
        actioniso2->setText(QCoreApplication::translate("LevelScheme", "iso2", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("LevelScheme", "toolBar", nullptr));
        menuother_isotopes->setTitle(QCoreApplication::translate("LevelScheme", "other isotopes", nullptr));
        menuedit_levels->setTitle(QCoreApplication::translate("LevelScheme", "edit levels", nullptr));
        menu_savePic->setTitle(QCoreApplication::translate("LevelScheme", "save picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LevelScheme: public Ui_LevelScheme {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_LEVELSCHEME_H
