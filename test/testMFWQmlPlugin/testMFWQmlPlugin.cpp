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

    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile(f.dir().absolutePath() + "/test.qml"));
    view->show();

    return app.exec();
}