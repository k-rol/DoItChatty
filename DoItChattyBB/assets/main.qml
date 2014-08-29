import bb.cascades 1.2
import my.timer 1.0
import bb.platform 1.2
import bb.device 1.2

Page {
    attachedObjects: [
        QTimer {
            id: timer
            interval: 500
            onTimeout :{
                scrolldown()
                timer.stop()
            }
        },
        Settings {
            id: settings
        },
        Notification {
            id: notify
        }
    ]
    Menu.definition: MenuDefinition {
            settingsAction: SettingsActionItem {
                onTriggered: {
                    settings.open()
                    }
                }
            actions: ActionItem {
                onTriggered: {
                    testpage.open()
                }
            }
        }
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
                text: "Petula"
                preferredWidth: 340.0
                objectName: "nickTextBox"

            }
            Button {
                text: "Chg Nick"
                onClicked: {
                    QmlBridge.on_changeNickButton_clicked(nickTextBox.text)
                }
                rightMargin: 20.0
                preferredWidth: 100
                objectName: "nickButton"

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
        
            ScrollView {
                id: myScrollView
                scrollRole: ScrollRole.Main
                objectName: "myScrollView"
                TextArea {
                    id: chatTextBox
                    scrollMode: TextAreaScrollMode.Stiff
                    objectName: "chatTextBox"
                    editable: false
                    text: ""
                    inputMode: TextAreaInputMode.Chat
                    onTextChanged: {
                        //notify.notify()
                        //led.flash()
                        //chatTextBox.editor.cursorPosition = chatTextBox.editor.cursorPosition.valueOf() + 1000
                        scrolldown()
                    }
                    minHeight: 475.0
                    textFormat: TextFormat.Plain

                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                rightPadding: 10.0
                TextField {
                    id: sendTextBox
                    hintText: "Chat here"
                    inputMode: TextFieldInputMode.Chat
                    input.submitKey: SubmitKey.Send
                    objectName: "sendTextBox"
                    input {
                        onSubmitted: {
                            QmlBridge.on_sendTextButton_clicked(sendTextBox.text)
                            sendTextBox.text = ""
                            sendTextBox.requestFocus()
                        }
                    }
                    onFocusedChanged: {
                        if (sendTextBox.focused)
                        {
                            scrolldown()
                            timer.start()
                        }
                    }
                    onTextChanged: {

                    }
                    clearButtonVisible: false

                }
                Button {
                    text: "Send"
                    preferredWidth: 150
                    onClicked: {
                        QmlBridge.on_sendTextButton_clicked(sendTextBox.text)
                        sendTextBox.text = ""
                        sendTextBox.requestFocus()
                    }
                    leftMargin: 20.0
                    focusPolicy: FocusPolicy.KeyAndTouch
                    objectName: "sendButton"

                }

            }

        }
        
    }
    function scrolldown() 
    {
        myScrollView.scrollToPoint(0, 100000, ScrollAnimation.None)   
    }
    onCreationCompleted: {
        Application.fullscreen.connect(onfullscreen)
    }
    
    function onfullscreen()
    {
        notify.clearEffectsForAll()
        notify.deleteAllFromInbox()
    }
}

