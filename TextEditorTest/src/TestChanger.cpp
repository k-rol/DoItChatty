/*
 * TestChanger.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: cauellet
 */

#include <src/TestChanger.h>

TestChanger::TestChanger(QObject *parent) : QObject(parent), myRoot(0), myTextArea(0)
{
    // TODO Auto-generated constructor stub

}

void TestChanger::setQml(AbstractPane *root)
{
    myRoot = root;
    myTextArea = myRoot->findChild<TextArea*>("textbox");
}

void TestChanger::writeSome()
{
    QString html = "<html><span style='text-decoration:underline'>Cascades</span>is <span style='font-size:xx-large;font-style:italic;color:green'>awesome!</span><br></html>";
    //myTextArea->editor()->insertPlainText(html);
    //myTextArea->setTextFormat(TextFormat::Html);
    //myTextArea->setText(html);
}
TestChanger::~TestChanger()
{
    // TODO Auto-generated destructor stub
}

