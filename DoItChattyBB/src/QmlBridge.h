/*
 * QmlBridge.h
 *
 *  Created on: Aug 24, 2014
 *      Author: CaroL
 */

#ifndef QMLBRIDGE_H_
#define QMLBRIDGE_H_
#include <QObject>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;


class QmlBridge: public QObject
{
    Q_OBJECT
public:
    QmlBridge(QObject *parent = 0);
    void setQml(AbstractPane *root);
    void updateText(QString readContent);
    void systemMessages(QString textToSend);
    void setButtonEnabilities(QString set);
    AbstractPane *myRoot;
    virtual ~QmlBridge();

private:

};

#endif /* QMLBRIDGE_H_ */
