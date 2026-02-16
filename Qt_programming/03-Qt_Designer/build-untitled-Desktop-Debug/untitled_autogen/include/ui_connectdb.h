/********************************************************************************
** Form generated from reading UI file 'connectdb.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDB_H
#define UI_CONNECTDB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectDB
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QSpinBox *spinBox;
    QDialogButtonBox *buttonBox;
    QMenuBar *menubar;

    void setupUi(QMainWindow *ConnectDB)
    {
        if (ConnectDB->objectName().isEmpty())
            ConnectDB->setObjectName("ConnectDB");
        ConnectDB->resize(300, 225);
        ConnectDB->setMinimumSize(QSize(300, 225));
        ConnectDB->setMaximumSize(QSize(300, 225));
        centralwidget = new QWidget(ConnectDB);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);

        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_4);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(0);
        spinBox->setMaximum(9999);
        spinBox->setValue(0);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);

        ConnectDB->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConnectDB);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 300, 20));
        ConnectDB->setMenuBar(menubar);

        retranslateUi(ConnectDB);

        QMetaObject::connectSlotsByName(ConnectDB);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectDB)
    {
        ConnectDB->setWindowTitle(QCoreApplication::translate("ConnectDB", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 \320\261\320\260\320\267\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label->setText(QCoreApplication::translate("ConnectDB", "\320\230\320\274\321\217 \321\205\320\276\321\201\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectDB", "\320\230\320\274\321\217 \320\261\320\260\320\267\321\213 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectDB", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_4->setText(QCoreApplication::translate("ConnectDB", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("ConnectDB", "\320\237\320\276\321\200\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectDB: public Ui_ConnectDB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDB_H
