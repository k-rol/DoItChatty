import bb.cascades 1.2

Sheet {
    Page {
        titleBar: TitleBar {
            title: "Settings"
            acceptAction: ActionItem {
                title: "Close"
                onTriggered: {
                    close()
                }
            }
        }
        Container {
            topPadding: 20.0

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Container {
                    
                }
                Label {
                    text: "Username"
                    
                }
                Container {
                    leftMargin: 200.0

                }
                TextField {
                    text: "some saved username"
                    preferredWidth: 320.0
                 
                }


            }

            Divider {}
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Container {
                    leftMargin: 200.0
                
                }
                Label {
                    text: "IP Address"
                }
                Container {
                    leftMargin: 200.0
                
                }
                TextField {
                    text: "54.191.14.76"
                    preferredWidth: 320.0

                }
                
            }
            Divider {}
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Container {
                    leftMargin: 200.0
                
                }
                Label {
                    text: "Port"
                }
                Container {
                    leftMargin: 300.0
                
                }
                TextField {
                    text: "443"
                    maximumLength: 5
                    preferredWidth: 320.0
                    validator: Validator {
                        
                    }

                }
            }
            Divider {}

        }
    }
}