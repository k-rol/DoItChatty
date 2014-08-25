

import bb.cascades 1.2

Page {
      titleBar: TitleBar {
          title: "DoIt Chatty"
        branded: TriBool.True
    }
    Container {
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight

            }
            rightPadding: 10.0
            
            TextField {
                id: nickTextBox
                text: "Carol"
                preferredWidth: 340.0

            }
            Button {
                text: "Chg Nick"
                onClicked: {
                    QmlBridge.on_changeNickButton_clicked(nickTextBox.text)
                }
                rightMargin: 20.0
                preferredWidth: 100

            }
            Button {
                text: "Connect"
                onClicked: {
                    QmlBridge.on_connectButton_clicked(nickTextBox.text);
                }
                objectName: "connectButton"
                preferredWidth: 100
            }

        }
        Container {
            TextArea {
                id: chatTextBox
                scrollMode: TextAreaScrollMode.Stiff
                objectName: "chatTextBox"
                //editable: false
                text: "No text received..."
                onTextChanged: {
                    //create some phone notification
                }
                preferredHeight: 450.0

            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                rightPadding: 10.0
                TextField {
                    id: sendTextBox
                    hintText: "Chat here"
                }
                Button {
                    text: "Send"
                    preferredWidth: 150
                    onClicked: {
                        QmlBridge.on_sendTextButton_clicked(sendTextBox.text)
                    }
                    leftMargin: 20.0
                    focusPolicy: FocusPolicy.KeyAndTouch

                }
            }

        }
        
    }
}
