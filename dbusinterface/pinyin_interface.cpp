/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -N -p pinyin_interface.h:pinyin_interface.cpp -c PinyinInterface pinyin.xml
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "pinyin_interface.h"

/*
 * Implementation of interface class PinyinInterface
 */

PinyinInterface::PinyinInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

PinyinInterface::~PinyinInterface()
{
}
