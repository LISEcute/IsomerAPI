/********************************************************************************
** Form generated from reading UI file 'w_IsomerAPI.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_ISOMERAPI_H
#define UI_W_ISOMERAPI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IsomerAPI
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLineEdit *le_entryCounts;
    QLabel *label_12;
    QLineEdit *le_maxGAMMA;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pb_applyFilters;
    QPushButton *pb_clearFilters;
    QPushButton *pb_levelScheme;
    QPushButton *pb_downloadCSV;
    QGroupBox *gb_tableFilters;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gb_filterHouse1;
    QLabel *label_3;
    QLineEdit *le_IGAM2;
    QLineEdit *le_T122;
    QLabel *label_5;
    QLineEdit *le_GE2;
    QLabel *label_7;
    QLabel *label_10;
    QLineEdit *le_FINE1;
    QLineEdit *le_GE1;
    QLabel *label_9;
    QLineEdit *le_FINE2;
    QLineEdit *le_IGAM1;
    QLabel *label_6;
    QLineEdit *le_T121;
    QLabel *label_8;
    QLabel *label_18;
    QGroupBox *gb_filterHouse2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cb_sourceFilter;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QLineEdit *le_numA;
    QLabel *label_4;
    QLineEdit *le_numA2;
    QLabel *label_13;
    QFrame *line_3;
    QLabel *label_17;
    QLabel *label_14;
    QLineEdit *le_numZ;
    QLineEdit *le_numZ1;
    QLineEdit *le_numZ2;
    QLabel *label_16;
    QLineEdit *le_numA1;
    QLabel *label_15;
    QFrame *line;
    QMenuBar *menubar;
    QMenu *menumy_menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IsomerAPI)
    {
        if (IsomerAPI->objectName().isEmpty())
            IsomerAPI->setObjectName("IsomerAPI");
        IsomerAPI->resize(863, 633);
        centralwidget = new QWidget(IsomerAPI);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(10);
        gridLayout_2->setObjectName("gridLayout_2");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setEnabled(true);
        tableView->setMouseTracking(true);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName("formLayout");
        formLayout->setVerticalSpacing(15);
        formLayout->setContentsMargins(-1, 20, -1, -1);
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        le_entryCounts = new QLineEdit(groupBox_2);
        le_entryCounts->setObjectName("le_entryCounts");
        le_entryCounts->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, le_entryCounts);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setTextFormat(Qt::RichText);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_12);

        le_maxGAMMA = new QLineEdit(groupBox_2);
        le_maxGAMMA->setObjectName("le_maxGAMMA");
        le_maxGAMMA->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, le_maxGAMMA);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(2, QFormLayout::LabelRole, verticalSpacer_2);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(20, -1, 20, -1);
        pb_applyFilters = new QPushButton(groupBox_3);
        pb_applyFilters->setObjectName("pb_applyFilters");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pb_applyFilters->sizePolicy().hasHeightForWidth());
        pb_applyFilters->setSizePolicy(sizePolicy);
        pb_applyFilters->setMaximumSize(QSize(16777215, 30));

        verticalLayout_7->addWidget(pb_applyFilters);

        pb_clearFilters = new QPushButton(groupBox_3);
        pb_clearFilters->setObjectName("pb_clearFilters");
        sizePolicy.setHeightForWidth(pb_clearFilters->sizePolicy().hasHeightForWidth());
        pb_clearFilters->setSizePolicy(sizePolicy);
        pb_clearFilters->setMaximumSize(QSize(16777215, 30));

        verticalLayout_7->addWidget(pb_clearFilters);

        pb_levelScheme = new QPushButton(groupBox_3);
        pb_levelScheme->setObjectName("pb_levelScheme");
        sizePolicy.setHeightForWidth(pb_levelScheme->sizePolicy().hasHeightForWidth());
        pb_levelScheme->setSizePolicy(sizePolicy);
        pb_levelScheme->setMaximumSize(QSize(16777215, 30));

        verticalLayout_7->addWidget(pb_levelScheme);

        pb_downloadCSV = new QPushButton(groupBox_3);
        pb_downloadCSV->setObjectName("pb_downloadCSV");
        sizePolicy.setHeightForWidth(pb_downloadCSV->sizePolicy().hasHeightForWidth());
        pb_downloadCSV->setSizePolicy(sizePolicy);
        pb_downloadCSV->setMaximumSize(QSize(16777215, 30));

        verticalLayout_7->addWidget(pb_downloadCSV);


        verticalLayout_2->addWidget(groupBox_3);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 2);

        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 2, 1);

        gb_tableFilters = new QGroupBox(centralwidget);
        gb_tableFilters->setObjectName("gb_tableFilters");
        horizontalLayout = new QHBoxLayout(gb_tableFilters);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(gb_tableFilters);
        groupBox->setObjectName("groupBox");
        gb_filterHouse1 = new QGridLayout(groupBox);
        gb_filterHouse1->setObjectName("gb_filterHouse1");
        gb_filterHouse1->setHorizontalSpacing(4);
        gb_filterHouse1->setContentsMargins(10, 9, 6, 6);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        gb_filterHouse1->addWidget(label_3, 0, 2, 1, 1);

        le_IGAM2 = new QLineEdit(groupBox);
        le_IGAM2->setObjectName("le_IGAM2");

        gb_filterHouse1->addWidget(le_IGAM2, 3, 3, 1, 1);

        le_T122 = new QLineEdit(groupBox);
        le_T122->setObjectName("le_T122");

        gb_filterHouse1->addWidget(le_T122, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setTextFormat(Qt::RichText);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gb_filterHouse1->addWidget(label_5, 1, 0, 1, 1);

        le_GE2 = new QLineEdit(groupBox);
        le_GE2->setObjectName("le_GE2");

        gb_filterHouse1->addWidget(le_GE2, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setTextFormat(Qt::RichText);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gb_filterHouse1->addWidget(label_7, 3, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setAlignment(Qt::AlignCenter);

        gb_filterHouse1->addWidget(label_10, 3, 2, 1, 1);

        le_FINE1 = new QLineEdit(groupBox);
        le_FINE1->setObjectName("le_FINE1");

        gb_filterHouse1->addWidget(le_FINE1, 2, 1, 1, 1);

        le_GE1 = new QLineEdit(groupBox);
        le_GE1->setObjectName("le_GE1");

        gb_filterHouse1->addWidget(le_GE1, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignCenter);

        gb_filterHouse1->addWidget(label_9, 2, 2, 1, 1);

        le_FINE2 = new QLineEdit(groupBox);
        le_FINE2->setObjectName("le_FINE2");

        gb_filterHouse1->addWidget(le_FINE2, 2, 3, 1, 1);

        le_IGAM1 = new QLineEdit(groupBox);
        le_IGAM1->setObjectName("le_IGAM1");

        gb_filterHouse1->addWidget(le_IGAM1, 3, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gb_filterHouse1->addWidget(label_6, 2, 0, 1, 1);

        le_T121 = new QLineEdit(groupBox);
        le_T121->setObjectName("le_T121");
        le_T121->setInputMethodHints(Qt::ImhNone);

        gb_filterHouse1->addWidget(le_T121, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignCenter);

        gb_filterHouse1->addWidget(label_8, 1, 2, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setTextFormat(Qt::RichText);
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gb_filterHouse1->addWidget(label_18, 0, 0, 1, 1);

        gb_filterHouse1->setColumnStretch(0, 3);
        gb_filterHouse1->setColumnStretch(1, 2);
        gb_filterHouse1->setColumnStretch(2, 1);
        gb_filterHouse1->setColumnStretch(3, 2);

        horizontalLayout->addWidget(groupBox);

        gb_filterHouse2 = new QGroupBox(gb_tableFilters);
        gb_filterHouse2->setObjectName("gb_filterHouse2");
        verticalLayout = new QVBoxLayout(gb_filterHouse2);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(gb_filterHouse2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        cb_sourceFilter = new QComboBox(gb_filterHouse2);
        cb_sourceFilter->setObjectName("cb_sourceFilter");
        cb_sourceFilter->setEditable(true);

        horizontalLayout_2->addWidget(cb_sourceFilter);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 4);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        line_2 = new QFrame(gb_filterHouse2);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        le_numA = new QLineEdit(gb_filterHouse2);
        le_numA->setObjectName("le_numA");
        le_numA->setEnabled(true);
        le_numA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numA, 1, 6, 1, 1);

        label_4 = new QLabel(gb_filterHouse2);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 2, 1, 3);

        le_numA2 = new QLineEdit(gb_filterHouse2);
        le_numA2->setObjectName("le_numA2");
        le_numA2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numA2, 1, 4, 1, 1);

        label_13 = new QLabel(gb_filterHouse2);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 1, 0, 1, 1);

        line_3 = new QFrame(gb_filterHouse2);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line_3, 0, 5, 3, 1);

        label_17 = new QLabel(gb_filterHouse2);
        label_17->setObjectName("label_17");
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_17, 0, 6, 1, 1);

        label_14 = new QLabel(gb_filterHouse2);
        label_14->setObjectName("label_14");
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_14, 1, 3, 1, 1);

        le_numZ = new QLineEdit(gb_filterHouse2);
        le_numZ->setObjectName("le_numZ");
        le_numZ->setInputMethodHints(Qt::ImhNone);
        le_numZ->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numZ, 2, 6, 1, 1);

        le_numZ1 = new QLineEdit(gb_filterHouse2);
        le_numZ1->setObjectName("le_numZ1");
        le_numZ1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numZ1, 2, 2, 1, 1);

        le_numZ2 = new QLineEdit(gb_filterHouse2);
        le_numZ2->setObjectName("le_numZ2");
        le_numZ2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numZ2, 2, 4, 1, 1);

        label_16 = new QLabel(gb_filterHouse2);
        label_16->setObjectName("label_16");
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_16, 2, 3, 1, 1);

        le_numA1 = new QLineEdit(gb_filterHouse2);
        le_numA1->setObjectName("le_numA1");
        le_numA1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(le_numA1, 1, 2, 1, 1);

        label_15 = new QLabel(gb_filterHouse2);
        label_15->setObjectName("label_15");
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 2, 0, 1, 1);

        line = new QFrame(gb_filterHouse2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line, 0, 1, 3, 1);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(2, 2);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 2);
        gridLayout->setColumnStretch(6, 3);

        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addWidget(gb_filterHouse2);


        gridLayout_2->addWidget(gb_tableFilters, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 2);
        gridLayout_2->setRowStretch(1, 1);
        IsomerAPI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IsomerAPI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 863, 21));
        menumy_menu = new QMenu(menubar);
        menumy_menu->setObjectName("menumy_menu");
        IsomerAPI->setMenuBar(menubar);
        statusbar = new QStatusBar(IsomerAPI);
        statusbar->setObjectName("statusbar");
        IsomerAPI->setStatusBar(statusbar);
        QWidget::setTabOrder(tableView, le_T121);
        QWidget::setTabOrder(le_T121, le_T122);
        QWidget::setTabOrder(le_T122, le_GE1);
        QWidget::setTabOrder(le_GE1, le_GE2);
        QWidget::setTabOrder(le_GE2, le_FINE1);
        QWidget::setTabOrder(le_FINE1, le_FINE2);
        QWidget::setTabOrder(le_FINE2, le_IGAM1);
        QWidget::setTabOrder(le_IGAM1, le_IGAM2);
        QWidget::setTabOrder(le_IGAM2, cb_sourceFilter);
        QWidget::setTabOrder(cb_sourceFilter, le_numA1);
        QWidget::setTabOrder(le_numA1, le_numA2);
        QWidget::setTabOrder(le_numA2, le_numZ1);
        QWidget::setTabOrder(le_numZ1, le_numZ2);
        QWidget::setTabOrder(le_numZ2, le_numA);
        QWidget::setTabOrder(le_numA, le_numZ);
        QWidget::setTabOrder(le_numZ, le_entryCounts);
        QWidget::setTabOrder(le_entryCounts, le_maxGAMMA);
        QWidget::setTabOrder(le_maxGAMMA, pb_applyFilters);
        QWidget::setTabOrder(pb_applyFilters, pb_clearFilters);
        QWidget::setTabOrder(pb_clearFilters, pb_levelScheme);
        QWidget::setTabOrder(pb_levelScheme, pb_downloadCSV);

        menubar->addAction(menumy_menu->menuAction());

        retranslateUi(IsomerAPI);

        QMetaObject::connectSlotsByName(IsomerAPI);
    } // setupUi

    void retranslateUi(QMainWindow *IsomerAPI)
    {
        IsomerAPI->setWindowTitle(QCoreApplication::translate("IsomerAPI", "IsomerAPI", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("IsomerAPI", "Summary statistics for filter", nullptr));
        label_11->setText(QCoreApplication::translate("IsomerAPI", "Isomer Count:", nullptr));
        label_12->setText(QCoreApplication::translate("IsomerAPI", "max &gamma;-Energy:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("IsomerAPI", "User operations", nullptr));
        pb_applyFilters->setText(QCoreApplication::translate("IsomerAPI", "Apply Filters", nullptr));
        pb_clearFilters->setText(QCoreApplication::translate("IsomerAPI", "Clear Filters", nullptr));
        pb_levelScheme->setText(QCoreApplication::translate("IsomerAPI", "Draw Level Scheme", nullptr));
        pb_downloadCSV->setText(QCoreApplication::translate("IsomerAPI", "Download CSV", nullptr));
        gb_tableFilters->setTitle(QString());
        label_3->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_5->setText(QCoreApplication::translate("IsomerAPI", "&gamma;-energy (KeV) :", nullptr));
        label_7->setText(QCoreApplication::translate("IsomerAPI", "I<sub>&gamma;</sub> transmission :", nullptr));
        label_10->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_9->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_6->setText(QCoreApplication::translate("IsomerAPI", "Final Levels :", nullptr));
        label_8->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_18->setText(QCoreApplication::translate("IsomerAPI", "T <sub>1/2</sub> :", nullptr));
        gb_filterHouse2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("IsomerAPI", "Source:", nullptr));
        cb_sourceFilter->setCurrentText(QString());
        label_4->setText(QCoreApplication::translate("IsomerAPI", "Range Search", nullptr));
        label_13->setText(QCoreApplication::translate("IsomerAPI", "Mass number (A<sub>IT</sub>) :", nullptr));
        label_17->setText(QCoreApplication::translate("IsomerAPI", "Exact Search", nullptr));
        label_14->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_16->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_15->setText(QCoreApplication::translate("IsomerAPI", "Proton number (Z<sub>IT</sub>) :", nullptr));
        menumy_menu->setTitle(QCoreApplication::translate("IsomerAPI", "my menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IsomerAPI: public Ui_IsomerAPI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_ISOMERAPI_H
