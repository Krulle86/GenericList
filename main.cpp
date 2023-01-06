#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "registertypes.h"
#include "specialicedlist.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    REGISTER_GENERIC_TYPES(Models)

    QQmlApplicationEngine engine;

    SpecialicedList specialicedList(&app);
    engine.rootContext()->setContextProperty(QStringLiteral("specialicedList"), &specialicedList);

    const QUrl url(u"qrc:/ExampleGenericList/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
