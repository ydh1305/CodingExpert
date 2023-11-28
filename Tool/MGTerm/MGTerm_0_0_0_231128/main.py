# ///////////////////////////////////////////////////////////////
#
# BY: donghyun.yoon@lge.com
# PROJECT MADE WITH: Qt Designer and PySide6
# V: 1.0.0
#
# This project can be used freely for all uses, as long as they maintain the
# respective credits only in the Python scripts, any information in the visual
# interface (GUI) can be modified without any implication.
#
# There are limitations on Qt licenses if you want to use your products
# commercially, I recommend reading them on the official website:
# https://doc.qt.io/qtforpython/licenses.html
#
# ///////////////////////////////////////////////////////////////

import sys
import os
import platform

import serial
# IMPORT / GUI AND MODULES AND WIDGETS
# ///////////////////////////////////////////////////////////////
from modules import *
from widgets import *
os.environ["QT_FONT_DPI"] = "96" # FIX Problem for High DPI and Scale above 100%

# SET AS GLOBAL WIDGETS
# ///////////////////////////////////////////////////////////////
widgets = None

class SerialReaderThread(QThread):
    data_received = Signal(str)

    def __init__(self, port, baudrate):
        super().__init__()
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.buffer = b""

    def run(self):
        try:
            self.serial = serial.Serial(self.port, self.baudrate)
            while True:
                if self.serial.in_waiting > 0:
                    try:
                        self.buffer += self.serial.read(self.serial.in_waiting)
                        lines = self.buffer.split(b"\n")
                        self.buffer = lines[-1] # Incomplete line

                        for line in lines[:-1]:
                            data = line.decode('cp949').strip()
                            self.data_received.emit(data)
                        #data = self.serial.readline().decode('cp949').strip()
                        #self.data_received.emit(data)
                    except UnicodeDecodeError:
                        pass
        except serial.SerialException as e:
            print(f"Serial port error: {e}")
        finally:
            if self.serial and self.serial.is_open:
                self.serial.close()

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        # SET AS GLOBAL WIDGETS
        # ///////////////////////////////////////////////////////////////
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        global widgets
        widgets = self.ui

        # USE CUSTOM TITLE BAR | USE AS "False" FOR MAC OR LINUX
        # ///////////////////////////////////////////////////////////////
        Settings.ENABLE_CUSTOM_TITLE_BAR = True

        # APP NAME
        # ///////////////////////////////////////////////////////////////
        title = "MGTerm"
        description = "MGTerm"
        # APPLY TEXTS
        self.setWindowTitle(title)
        widgets.titleRightInfo.setText(description)

        # SET UI DEFINITIONS
        # ///////////////////////////////////////////////////////////////
        UIFunctions.uiDefinitions(self)

        # QTableWidget PARAMETERS
        # ///////////////////////////////////////////////////////////////
        # widgets.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        # BUTTONS CLICK
        # ///////////////////////////////////////////////////////////////

        # EXTRA LEFT BOX
        def openCloseLeftBox():
            UIFunctions.toggleLeftBox(self, True)
        # [andrew] removed
        # widgets.toggleLeftBox.clicked.connect(openCloseLeftBox)

        # EXTRA RIGHT BOX
        def openCloseRightBox():
            UIFunctions.toggleRightBox(self, True)
        widgets.settingsTopBtn.clicked.connect(openCloseRightBox)

        # EXTRA RIGHT BUTTON 
        widgets.btn_cmode.clicked.connect(self.buttonClick)
        widgets.btn_tmode.clicked.connect(self.buttonClick)
        widgets.btn_mmode.clicked.connect(self.buttonClick)
        widgets.btn_clear.clicked.connect(self.buttonClick)
        widgets.btn_filter_1.clicked.connect(self.buttonClick)

        # SHOW APP
        # ///////////////////////////////////////////////////////////////
        self.show()

        # SET CUSTOM THEME
        # ///////////////////////////////////////////////////////////////
        useCustomTheme = False
        themeFile = "themes\py_dracula_light.qss"

        # SET THEME AND HACKS
        if useCustomTheme:
            # LOAD AND APPLY STYLE
            UIFunctions.theme(self, themeFile, True)

            # SET HACKS
            AppFunctions.setThemeHack(self)

        # SET HOME PAGE AND SELECT MENU
        # ///////////////////////////////////////////////////////////////
        self.widgets = self.ui

        # widgets.version.setText("Build Info. {}.{}.{}".format(FM_VERSION_MAJOR, FM_VERSION_MINOR, FM_VERSION_PATCH))
        # Smart LCD
        self.serial_thread = SerialReaderThread("COM32", 921600)
        # LUPA on ITE
        #self.serial_thread = SerialReaderThread("COM57", 115200)
        self.serial_thread.data_received.connect(self.show_message)
        self.serial_thread.start()

        self.init_screen_mode()

    def init_screen_mode(self):
        if widgets.btn_cmode.isChecked() == True:
            widgets.stackedWidget.setCurrentWidget(widgets.widget1)
        elif widgets.btn_fmode.isChecked() == True:
            widgets.stackedWidget.setCurrentWidget(widgets.widget2)

    def show_message(self, message):

        curwidget = widgets.stackedWidget.currentWidget()

        if curwidget == widgets.widget1:
            widgets.message_viewer.appendPlainText(message)
        elif curwidget == widgets.widget2:
            widgets.message_viewer_2.appendPlainText(message)

            if "USB_STATE" in message:
                widgets.message_viewer_3.appendPlainText(message)
            
            if "role_sw_set role" in message:
                widgets.message_viewer_3.appendPlainText(message)

            if "New USB" in message:
                widgets.message_viewer_3.appendPlainText(message)
            
            if ", device number" in message:
                widgets.message_viewer_3.appendPlainText(message)
        elif curwidget == widgets.widget3:
            widgets.message_viewer_22.appendPlainText(message)

            if "USB_STATE" in message:
                widgets.message_viewer_23.appendPlainText(message)
        
            if "role_sw_set role" in message:
                widgets.message_viewer_23.appendPlainText(message)

            if "New USB" in message:
                widgets.message_viewer_23.appendPlainText(message)
        
            if ", device number" in message:
                widgets.message_viewer_23.appendPlainText(message)

            if "role_sw_set role" in message:
                widgets.message_viewer_24.appendPlainText(message)
		
    def show_setmessage(self, message):
        widgets.message_viewer.setPlainText(message)
	
    def event(self, event):
        if event.type() == QEvent.User:
            if isinstance(event, MessageEvent): 

                self.show_message(event.getMessage())
            elif isinstance(event, SetMessageEvent):
                self.show_setmessage(event.getMessage())
            return True
        return super().event(event)
    
    def eventFilter(self, obj, event):
        print(obj, widgets.message_viewer_2.size(), obj.size())
        print(obj.objectName(), event.type())

        if obj == widgets.message_viewer_2 and event.type() == QEvent.Resize:
            widgets.message_viewer_2.setFixedSize(widgets.message_viewer_2.size())
            return True
        elif obj == widgets.message_viewer_3 and event.type() == QEvent.Resize:
            widgets.message_viewer_3.setFixedSize(widgets.message_viewer_2.size())
            return True

        return super().eventFilter(obj, event)

    # BUTTONS CLICK
    # Post here your functions for clicked buttons
    # ///////////////////////////////////////////////////////////////
    def buttonClick(self):
        # GET BUTTON CLICKED
        btn = self.sender()
        btnName = btn.objectName()

        # SHOW HOME PAGE
        if btnName == "btn_cmode":
            widgets.stackedWidget.setCurrentWidget(widgets.widget1)
            #UIFunctions.resetStyle(self, btnName)
            #btn.setStyleSheet(UIFunctions.selectMenu(btn.styleSheet()))

        # SHOW WIDGETS PAGE
        if btnName == "btn_mmode":
            widgets.stackedWidget.setCurrentWidget(widgets.widget2)
            #UIFunctions.resetStyle(self, btnName)
            #btn.setStyleSheet(UIFunctions.selectMenu(btn.styleSheet()))

        if btnName == "btn_tmode":
            widgets.stackedWidget.setCurrentWidget(widgets.widget3)
            #UIFunctions.resetStyle(self, btnName)
            #btn.setStyleSheet(UIFunctions.selectMenu(btn.styleSheet()))

        # SHOW NEW PAGE
        if btnName == "btn_clear":
            widgets.message_viewer.clear()
            widgets.message_viewer_2.clear()
            widgets.message_viewer_3.clear()
            widgets.message_viewer_22.clear()
            widgets.message_viewer_23.clear()
            widgets.message_viewer_24.clear()

        if btnName == "btn_filter_1":
            #widgets.FilterBox_1.open()
            print("test")

        if btnName == "btn_save":
            print("Save BTN clicked!")

        # PRINT BTN NAME
        print(f'Button "{btnName}" pressed!')


    # RESIZE EVENTS
    # ///////////////////////////////////////////////////////////////
    def resizeEvent(self, event):
        # Update Size Grips
        UIFunctions.resize_grips(self)

    # MOUSE CLICK EVENTS
    # ///////////////////////////////////////////////////////////////
    def mousePressEvent(self, event):
        # SET DRAG POS WINDOW
        self.dragPos = event.globalPos()

        # PRINT MOUSE EVENTS
        if event.buttons() == Qt.LeftButton:
            print('Mouse click: LEFT CLICK')
        if event.buttons() == Qt.RightButton:
            print('Mouse click: RIGHT CLICK')

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon("icon.ico"))
    window = MainWindow()
    sys.exit(app.exec_())
