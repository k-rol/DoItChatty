/*
 * TestChanger.h
 *
 *  Created on: Sep 12, 2014
 *      Author: cauellet
 */

#ifndef TESTCHANGER_H_
#define TESTCHANGER_H_
#include <QObject>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/controls/textarea.h>

using namespace bb::cascades;

class TestChanger: public QObject
{
    Q_OBJECT
public:
    TestChanger(QObject *parent = 0);
    void setQml(AbstractPane *root);
    Q_INVOKABLE void writeSome();
    virtual ~TestChanger();

private:
    AbstractPane *myRoot;
    TextArea *myTextArea;




};

#endif /* TESTCHANGER_H_ */
