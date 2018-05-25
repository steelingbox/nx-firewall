//
// Created by alexis on 5/23/18.
//

#include <QQuickView>
#include <QtQml>
#include <QtWidgets/QApplication>
#include <QFileInfo>


int main(int argc, char **argv)
{
    QApplication app( argc, argv );

    QFileInfo f(__FILE__);

//    QQuickView *view = new QQuickView;
//    view->setSource(QUrl::fromLocalFile(f.dir().absolutePath() + "/test.qml"));
//    view->show();
//
//    QQuickView *view2 = new QQuickView;
//    view2->setSource(QUrl::fromLocalFile(f.dir().absolutePath() + "/test2.qml"));
//    view2->show();

    QQuickView *view3 = new QQuickView;
    view3->setSource(QUrl::fromLocalFile(f.dir().absolutePath() + "/test3.qml"));
    view3->show();

    return app.exec();
}