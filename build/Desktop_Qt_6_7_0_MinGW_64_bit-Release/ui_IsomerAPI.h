/********************************************************************************
** Form generated from reading UI file 'IsomerAPI.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISOMERAPI_H
#define UI_ISOMERAPI_H

#include <QtCore/QVariant>
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IsomerAPI
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QGroupBox *gb_tableFilters;
    QHBoxLayout *horizontalLayout;
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
    QLabel *label;
    QLabel *label_8;
    QLineEdit *le_FINE2;
    QLineEdit *le_IGAM1;
    QLabel *label_6;
    QLineEdit *le_T121;
    QGroupBox *gb_filterHouse2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cb_sourceFilter;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *label_16;
    QLineEdit *le_numA2;
    QLineEdit *le_numZ2;
    QLineEdit *le_numZ1;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_14;
    QLineEdit *le_numA1;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *le_numA;
    QLineEdit *le_numZ;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLineEdit *le_entryCounts;
    QLabel *label_12;
    QLineEdit *le_maxGAMMA;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pb_applyFilters;
    QPushButton *pb_clearFilters;
    QPushButton *pb_levelScheme;
    QPushButton *pb_downloadCSV;

    void setupUi(QWidget *IsomerAPI)
    {
        if (IsomerAPI->objectName().isEmpty())
            IsomerAPI->setObjectName("IsomerAPI");
        IsomerAPI->resize(974, 641);
        horizontalLayout_3 = new QHBoxLayout(IsomerAPI);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tableView = new QTableView(IsomerAPI);
        tableView->setObjectName("tableView");
        tableView->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMouseTracking(true);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);

        gb_tableFilters = new QGroupBox(IsomerAPI);
        gb_tableFilters->setObjectName("gb_tableFilters");
        horizontalLayout = new QHBoxLayout(gb_tableFilters);
        horizontalLayout->setObjectName("horizontalLayout");
        gb_filterHouse1 = new QGridLayout();
        gb_filterHouse1->setObjectName("gb_filterHouse1");
        label_3 = new QLabel(gb_tableFilters);
        label_3->setObjectName("label_3");

        gb_filterHouse1->addWidget(label_3, 0, 2, 1, 1);

        le_IGAM2 = new QLineEdit(gb_tableFilters);
        le_IGAM2->setObjectName("le_IGAM2");

        gb_filterHouse1->addWidget(le_IGAM2, 3, 3, 1, 1);

        le_T122 = new QLineEdit(gb_tableFilters);
        le_T122->setObjectName("le_T122");

        gb_filterHouse1->addWidget(le_T122, 0, 3, 1, 1);

        label_5 = new QLabel(gb_tableFilters);
        label_5->setObjectName("label_5");

        gb_filterHouse1->addWidget(label_5, 1, 0, 1, 1);

        le_GE2 = new QLineEdit(gb_tableFilters);
        le_GE2->setObjectName("le_GE2");

        gb_filterHouse1->addWidget(le_GE2, 1, 3, 1, 1);

        label_7 = new QLabel(gb_tableFilters);
        label_7->setObjectName("label_7");
        label_7->setTextFormat(Qt::PlainText);

        gb_filterHouse1->addWidget(label_7, 3, 0, 1, 1);

        label_10 = new QLabel(gb_tableFilters);
        label_10->setObjectName("label_10");

        gb_filterHouse1->addWidget(label_10, 3, 2, 1, 1);

        le_FINE1 = new QLineEdit(gb_tableFilters);
        le_FINE1->setObjectName("le_FINE1");

        gb_filterHouse1->addWidget(le_FINE1, 2, 1, 1, 1);

        le_GE1 = new QLineEdit(gb_tableFilters);
        le_GE1->setObjectName("le_GE1");

        gb_filterHouse1->addWidget(le_GE1, 1, 1, 1, 1);

        label_9 = new QLabel(gb_tableFilters);
        label_9->setObjectName("label_9");

        gb_filterHouse1->addWidget(label_9, 2, 2, 1, 1);

        label = new QLabel(gb_tableFilters);
        label->setObjectName("label");

        gb_filterHouse1->addWidget(label, 0, 0, 1, 1);

        label_8 = new QLabel(gb_tableFilters);
        label_8->setObjectName("label_8");

        gb_filterHouse1->addWidget(label_8, 1, 2, 1, 1);

        le_FINE2 = new QLineEdit(gb_tableFilters);
        le_FINE2->setObjectName("le_FINE2");

        gb_filterHouse1->addWidget(le_FINE2, 2, 3, 1, 1);

        le_IGAM1 = new QLineEdit(gb_tableFilters);
        le_IGAM1->setObjectName("le_IGAM1");

        gb_filterHouse1->addWidget(le_IGAM1, 3, 1, 1, 1);

        label_6 = new QLabel(gb_tableFilters);
        label_6->setObjectName("label_6");

        gb_filterHouse1->addWidget(label_6, 2, 0, 1, 1);

        le_T121 = new QLineEdit(gb_tableFilters);
        le_T121->setObjectName("le_T121");
        le_T121->setInputMethodHints(Qt::ImhNone);

        gb_filterHouse1->addWidget(le_T121, 0, 1, 1, 1);

        gb_filterHouse1->setColumnStretch(0, 1);

        horizontalLayout->addLayout(gb_filterHouse1);

        gb_filterHouse2 = new QGroupBox(gb_tableFilters);
        gb_filterHouse2->setObjectName("gb_filterHouse2");
        verticalLayout_6 = new QVBoxLayout(gb_filterHouse2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(gb_filterHouse2);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        cb_sourceFilter = new QComboBox(gb_filterHouse2);
        cb_sourceFilter->setObjectName("cb_sourceFilter");
        cb_sourceFilter->setEditable(true);

        horizontalLayout_2->addWidget(cb_sourceFilter);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        verticalLayout_5->addItem(verticalSpacer);

        line_2 = new QFrame(gb_filterHouse2);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_5->addWidget(line_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_4 = new QLabel(gb_filterHouse2);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        label_17 = new QLabel(gb_filterHouse2);
        label_17->setObjectName("label_17");
        sizePolicy2.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_17, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(280, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        line = new QFrame(gb_filterHouse2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line, 1, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_16 = new QLabel(gb_filterHouse2);
        label_16->setObjectName("label_16");
        sizePolicy2.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(9);
        label_16->setFont(font);

        gridLayout_2->addWidget(label_16, 2, 2, 1, 1);

        le_numA2 = new QLineEdit(gb_filterHouse2);
        le_numA2->setObjectName("le_numA2");
        sizePolicy2.setHeightForWidth(le_numA2->sizePolicy().hasHeightForWidth());
        le_numA2->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(le_numA2, 0, 3, 1, 1);

        le_numZ2 = new QLineEdit(gb_filterHouse2);
        le_numZ2->setObjectName("le_numZ2");
        sizePolicy2.setHeightForWidth(le_numZ2->sizePolicy().hasHeightForWidth());
        le_numZ2->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(le_numZ2, 2, 3, 1, 1);

        le_numZ1 = new QLineEdit(gb_filterHouse2);
        le_numZ1->setObjectName("le_numZ1");
        sizePolicy2.setHeightForWidth(le_numZ1->sizePolicy().hasHeightForWidth());
        le_numZ1->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(le_numZ1, 2, 1, 1, 1);

        label_13 = new QLabel(gb_filterHouse2);
        label_13->setObjectName("label_13");
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_13, 0, 0, 1, 1);

        label_15 = new QLabel(gb_filterHouse2);
        label_15->setObjectName("label_15");
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);
        label_15->setFont(font);

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        label_14 = new QLabel(gb_filterHouse2);
        label_14->setObjectName("label_14");
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(label_14, 0, 2, 1, 1);

        le_numA1 = new QLineEdit(gb_filterHouse2);
        le_numA1->setObjectName("le_numA1");
        sizePolicy2.setHeightForWidth(le_numA1->sizePolicy().hasHeightForWidth());
        le_numA1->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(le_numA1, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 2);

        horizontalLayout_5->addLayout(gridLayout_2);

        line_3 = new QFrame(gb_filterHouse2);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_5->addWidget(line_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        le_numA = new QLineEdit(gb_filterHouse2);
        le_numA->setObjectName("le_numA");
        le_numA->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(le_numA->sizePolicy().hasHeightForWidth());
        le_numA->setSizePolicy(sizePolicy3);

        verticalLayout_4->addWidget(le_numA);

        le_numZ = new QLineEdit(gb_filterHouse2);
        le_numZ->setObjectName("le_numZ");
        sizePolicy3.setHeightForWidth(le_numZ->sizePolicy().hasHeightForWidth());
        le_numZ->setSizePolicy(sizePolicy3);
        le_numZ->setInputMethodHints(Qt::ImhNone);

        verticalLayout_4->addWidget(le_numZ);


        horizontalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalLayout_5->setStretch(0, 2);
        verticalLayout_5->setStretch(2, 1);

        verticalLayout_6->addLayout(verticalLayout_5);


        horizontalLayout->addWidget(gb_filterHouse2);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(gb_tableFilters);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox_2 = new QGroupBox(IsomerAPI);
        groupBox_2->setObjectName("groupBox_2");
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName("formLayout");
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        le_entryCounts = new QLineEdit(groupBox_2);
        le_entryCounts->setObjectName("le_entryCounts");
        le_entryCounts->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, le_entryCounts);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setTextFormat(Qt::PlainText);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_12);

        le_maxGAMMA = new QLineEdit(groupBox_2);
        le_maxGAMMA->setObjectName("le_maxGAMMA");
        le_maxGAMMA->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, le_maxGAMMA);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(IsomerAPI);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        pb_applyFilters = new QPushButton(groupBox_3);
        pb_applyFilters->setObjectName("pb_applyFilters");

        verticalLayout_7->addWidget(pb_applyFilters);

        pb_clearFilters = new QPushButton(groupBox_3);
        pb_clearFilters->setObjectName("pb_clearFilters");

        verticalLayout_7->addWidget(pb_clearFilters);

        pb_levelScheme = new QPushButton(groupBox_3);
        pb_levelScheme->setObjectName("pb_levelScheme");

        verticalLayout_7->addWidget(pb_levelScheme);

        pb_downloadCSV = new QPushButton(groupBox_3);
        pb_downloadCSV->setObjectName("pb_downloadCSV");

        verticalLayout_7->addWidget(pb_downloadCSV);


        verticalLayout_2->addWidget(groupBox_3);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 9);
        horizontalLayout_3->setStretch(1, 3);

        retranslateUi(IsomerAPI);

        QMetaObject::connectSlotsByName(IsomerAPI);
    } // setupUi

    void retranslateUi(QWidget *IsomerAPI)
    {
        IsomerAPI->setWindowTitle(QCoreApplication::translate("IsomerAPI", "IsomerAPI", nullptr));
        gb_tableFilters->setTitle(QString());
        label_3->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        le_IGAM2->setText(QString());
        label_5->setText(QCoreApplication::translate("IsomerAPI", "<html><head/><body><p>&gamma;-Energy (keV):</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("IsomerAPI", "I\316\263 Transmission:", nullptr));
        label_10->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        le_FINE1->setText(QString());
        label_9->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label->setText(QCoreApplication::translate("IsomerAPI", "T<sub> 1/2</sub> (&mu;):", nullptr));
        label_8->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_6->setText(QCoreApplication::translate("IsomerAPI", "Final Levels:", nullptr));
        gb_filterHouse2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("IsomerAPI", "<html><head/><body><p>Source:</p></body></html>", nullptr));
        cb_sourceFilter->setCurrentText(QString());
        label_4->setText(QCoreApplication::translate("IsomerAPI", "Range Search", nullptr));
        label_17->setText(QCoreApplication::translate("IsomerAPI", "Exact Search", nullptr));
        label_16->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        label_13->setText(QCoreApplication::translate("IsomerAPI", "Atomic Mass (A_IT):", nullptr));
        label_15->setText(QCoreApplication::translate("IsomerAPI", "Proton Number (Z_IT):", nullptr));
        label_14->setText(QCoreApplication::translate("IsomerAPI", "to", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("IsomerAPI", "summary statistics for filter", nullptr));
        label_11->setText(QCoreApplication::translate("IsomerAPI", "Isomer Count:", nullptr));
        label_12->setText(QCoreApplication::translate("IsomerAPI", "Max &gamma;-Energy:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("IsomerAPI", "user operations", nullptr));
        pb_applyFilters->setText(QCoreApplication::translate("IsomerAPI", "Apply Filters", nullptr));
        pb_clearFilters->setText(QCoreApplication::translate("IsomerAPI", "Clear Filters", nullptr));
        pb_levelScheme->setText(QCoreApplication::translate("IsomerAPI", "Draw Level Scheme", nullptr));
        pb_downloadCSV->setText(QCoreApplication::translate("IsomerAPI", "Download CSV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IsomerAPI: public Ui_IsomerAPI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISOMERAPI_H
