#pragma once

#include <QQmlApplicationEngine>
#include <QDebug>

#include "genericitemlist.h"
#include "genericlistmodel.h"

#define REGISTER_GENERIC_TYPES( PLUGIN_NAME )                                                                                                                   \
    qmlRegisterUncreatableType<GenericList::ItemList>(#PLUGIN_NAME, 1, 0, "GenericItemList", QStringLiteral("Only Interface. Cannot create in QML"));       \
    qmlRegisterType<GenericList::GenericModel>(#PLUGIN_NAME, 1, 0, "GenericModel");

