/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *Action;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *img_source;
    QProgressBar *Barra1;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *in_folder;
    QLineEdit *out_folder;
    QPushButton *cpm_btn;
    QPushButton *meshlab_btn;
    QComboBox *itemize;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(616, 392);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 0, 121, 31));
        QFont font;
        font.setFamily(QStringLiteral("URW Chancery L"));
        font.setPointSize(18);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        Action = new QLabel(centralWidget);
        Action->setObjectName(QStringLiteral("Action"));
        Action->setGeometry(QRect(13, 310, 591, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("URW Chancery L"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        Action->setFont(font1);
        Action->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 251, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        img_source = new QLabel(layoutWidget);
        img_source->setObjectName(QStringLiteral("img_source"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(img_source->sizePolicy().hasHeightForWidth());
        img_source->setSizePolicy(sizePolicy);
        img_source->setScaledContents(true);

        verticalLayout->addWidget(img_source);

        Barra1 = new QProgressBar(layoutWidget);
        Barra1->setObjectName(QStringLiteral("Barra1"));
        Barra1->setValue(0);

        verticalLayout->addWidget(Barra1);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(320, 30, 265, 87));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu Mono"));
        font2.setPointSize(11);
        font2.setItalic(true);
        label_2->setFont(font2);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        in_folder = new QLineEdit(layoutWidget1);
        in_folder->setObjectName(QStringLiteral("in_folder"));

        verticalLayout_3->addWidget(in_folder);

        out_folder = new QLineEdit(layoutWidget1);
        out_folder->setObjectName(QStringLiteral("out_folder"));

        verticalLayout_3->addWidget(out_folder);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        cpm_btn = new QPushButton(layoutWidget1);
        cpm_btn->setObjectName(QStringLiteral("cpm_btn"));

        verticalLayout_4->addWidget(cpm_btn);

        meshlab_btn = new QPushButton(centralWidget);
        meshlab_btn->setObjectName(QStringLiteral("meshlab_btn"));
        meshlab_btn->setGeometry(QRect(340, 230, 211, 61));
        QFont font3;
        font3.setFamily(QStringLiteral("URW Palladio L"));
        font3.setPointSize(15);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        meshlab_btn->setFont(font3);
        itemize = new QComboBox(centralWidget);
        itemize->addItem(QString());
        itemize->addItem(QString());
        itemize->setObjectName(QStringLiteral("itemize"));
        itemize->setGeometry(QRect(340, 190, 211, 31));
        QFont font4;
        font4.setFamily(QStringLiteral("URW Bookman L"));
        font4.setPointSize(11);
        font4.setItalic(true);
        itemize->setFont(font4);
        itemize->setLayoutDirection(Qt::LeftToRight);
        itemize->setIconSize(QSize(16, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Esc\303\241ner 2018", nullptr));
        label->setText(QApplication::translate("MainWindow", "Esc\303\241ner 3D", nullptr));
        Action->setText(QApplication::translate("MainWindow", "== Step ==", nullptr));
        img_source->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Carpeta de Entrada:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Carpeta de Salida:", nullptr));
        cpm_btn->setText(QApplication::translate("MainWindow", "Compilar", nullptr));
        meshlab_btn->setText(QApplication::translate("MainWindow", "Abrir Mesh", nullptr));
        itemize->setItemText(0, QApplication::translate("MainWindow", "         Nube de Puntos", nullptr));
        itemize->setItemText(1, QApplication::translate("MainWindow", "                Textura", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
