/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2

Page {
    Container {
        Label {
            // Localized text with the dynamic translation and locale updates support
            text: qsTr("Hello World") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: SystemDefaults.TextStyles.BigText
        }
        ListView {

        }
        /*
        TextArea {
            id: textBox
            objectName: "textbox"
            
            preferredHeight: 500.0
            text: "<html><span style='text-decoration:underline'>Cascades</span>is <span style='font-size:xx-large;font-style:italic;color:green'>awesome!</span><br></html>"
            textFormat: TextFormat.Html

        }*/
        
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight

            }

            Button {
                text: "add"
                onClicked: {
                    TestChanger.writeSome()
                }
            
            }
            ToggleButton {
                /*
                onCheckedChanged: {
                    if (checked)
                    {
                        textBox.textFormat.Html
                    }
                    else {
                        textBox.textFormat.Plain
                    }
                }*/
            
            }
        }

    }
}
