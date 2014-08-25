/*
 * QmlBridge.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: CaroL
 */

#include <src/QmlBridge.h>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/controls/button.h>

using namespace bb::cascades;

QmlBridge::QmlBridge(QObject *parent) : QObject(parent)
{

    // TODO Auto-generated constructor stub

}

void QmlBridge::setQml(AbstractPane *root)
{
    myRoot = root;
    Button *myButton = myRoot->findChild<Button*>("myButton");
    myButton->setText("Fuck yeah");
}

void QmlBridge::updateText(QString readContent)
{

}

void QmlBridge::systemMessages(QString textToSend)
{

}

void QmlBridge::setButtonEnabilities(QString set)
{

}

QmlBridge::~QmlBridge()
{
    // TODO Auto-generated destructor stub
}

