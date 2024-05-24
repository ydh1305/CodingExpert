# ///////////////////////////////////////////////////////////////
#
# BY: Andrew.Yoon
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

# IMPORT / GUI AND MODULES AND WIDGETS
# ///////////////////////////////////////////////////////////////
from modules import *
from widgets import *
os.environ["QT_FONT_DPI"] = "96" # FIX Problem for High DPI and Scale above 100%

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PySide6.QtWidgets import QApplication, QGraphicsView, QGraphicsScene, QGraphicsPixmapItem, QMainWindow
from PySide6.QtGui import QPixmap
from PySide6.QtCore import Qt
from io import BytesIO

# SET AS GLOBAL WIDGETS
# ///////////////////////////////////////////////////////////////
widgets = None

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        # SET AS GLOBAL WIDGETS
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        global widgets
        widgets = self.ui
        
        # andrew
        self.file_path = None

        # USE CUSTOM TITLE BAR | USE AS "False" FOR MAC OR LINUX
        Settings.ENABLE_CUSTOM_TITLE_BAR = True

        # APP NAME
        title = "LPMate - Modern GUI"
        description = "LPMate APP - Log Parser & visualization."

        # APPLY TEXTS
        self.setWindowTitle(title)
        widgets.titleRightInfo.setText(description)

        # TOGGLE MENU
        widgets.toggleButton.clicked.connect(lambda: UIFunctions.toggleMenu(self, True))

        # SET UI DEFINITIONS
        UIFunctions.uiDefinitions(self)

        # LEFT MENUS
        widgets.btn_home.clicked.connect(self.buttonClick)
        widgets.btn_new.clicked.connect(self.buttonClick)
        widgets.btn_copy.clicked.connect(self.buttonClick)
        widgets.btn_open.clicked.connect(self.buttonClick)

        # EXTRA LEFT BOX
        def openCloseLeftBox():
            UIFunctions.toggleLeftBox(self, True)

        # EXTRA RIGHT BOX
        def openCloseRightBox():
            UIFunctions.toggleRightBox(self, True)

        # SHOW APP
        self.show()

        # SET CUSTOM THEME
        useCustomTheme = False
        themeFile = "themes\py_dracula_light.qss"

        # SET THEME AND HACKS
        if useCustomTheme:
            # LOAD AND APPLY STYLE
            UIFunctions.theme(self, themeFile, True)

            # SET HACKS
            AppFunctions.setThemeHack(self)

        # SET HOME PAGE AND SELECT MENU
        widgets.stackedWidget.setCurrentWidget(widgets.home)
        widgets.btn_home.setStyleSheet(UIFunctions.selectMenu(widgets.btn_home.styleSheet()))

    def get_widget_size(self, widget):
        return widget.width(), widget.height()
    
    def copy_to_clipboard(self):
        # Create a QImage to render the scatterplot
        img = QImage(widgets.graphicsView.size(), QImage.Format_ARGB32)
        painter = QPainter(img)
        widgets.graphicsView.render(painter)
        painter.end()

        # Copy QImage to clipboard
        clipboard = QApplication.clipboard()
        clipboard.setImage(img)

    def draw_graph(self, file_path):
        if file_path is None:
            return  # If file_path is None, do not proceed further
        
        # Read data and create scatterplot
        print(file_path)
        df = pd.read_csv(file_path)

        # Extract the district information from '시군구' column
        df['구'] = df['시군구'].apply(lambda x: x.split()[1])
        df['동'] = df['시군구'].apply(lambda x: x.split()[2])

        # Filter data for the specific districts
        districts = ['강남구', '마포구', '서초구', '송파구']
        filtered_df = df[df['구'].isin(districts)]

        # Set up the plot
        plt.rc("font", family="Malgun Gothic")

        # scatterplot - white
        #sns.set(font="Malgun Gothic", rc={"axes.unicode_minus": False}, style='white')
        
        # lineplot - darkgrid
        sns.set(font="Malgun Gothic", rc={"axes.unicode_minus": False}, style='darkgrid')  # Set the style here

        # Adjust figure size based on widget size
        widget_width, widget_height = self.get_widget_size(widgets.graphicsView)
        figsize = (widget_width / 100, widget_height / 100)  # Convert to inches

        # Create line plots for each district
        fig, axes = plt.subplots(2, 2, figsize=figsize, sharey=True)
        axes = axes.flatten()

        for idx, district in enumerate(districts):
            district_df = filtered_df[filtered_df['구'] == district]
            #sns.scatterplot(data=district_df, x='동', y='거래금액(만원)', hue='구', ax=axes[idx])
            #sns.scatterplot(data=district_df, x='동', y='거래금액(만원)', ax=axes[idx], color='blue', alpha=0.5)
            sns.scatterplot(data=district_df, x='동', y='거래금액(만원)', hue='거래금액(만원)', ax=axes[idx], palette='coolwarm').legend(loc='upper left')

            #sns.histplot(data=district_df, x='동', y='거래금액(만원)', ax=axes[idx])
            
            #sns.lineplot(data=district_df, x='동', y='거래금액(만원)', ax=axes[idx], errorbar=None, marker='o')
            axes[idx].set_title(f"{district} 거래금액(만원) 추이")
            axes[idx].set_xlabel('동')
            axes[idx].set_ylabel('거래금액(만원)')

        # Adjust layout
        plt.tight_layout()

        # Convert the Matplotlib figure to QPixmap
        buf = BytesIO()
        fig.savefig(buf, format='png')
        buf.seek(0)
        qimage = QPixmap()
        qimage.loadFromData(buf.getvalue())

        # Display QPixmap in QGraphicsView
        scene = QGraphicsScene()
        pixmap_item = QGraphicsPixmapItem(qimage)
        scene.addItem(pixmap_item)
        widgets.graphicsView.setScene(scene)
        widgets.graphicsView.fitInView(pixmap_item, Qt.KeepAspectRatio)

        # Close the Matplotlib figure
        plt.close(fig)

    # BUTTONS CLICK
    def buttonClick(self):
        # GET BUTTON CLICKED
        btn = self.sender()
        btnName = btn.objectName()

        # SHOW HOME PAGE
        if btnName == "btn_home":
            widgets.stackedWidget.setCurrentWidget(widgets.home)
            UIFunctions.resetStyle(self, btnName)
            btn.setStyleSheet(UIFunctions.selectMenu(btn.styleSheet()))

        # SHOW NEW PAGE
        if btnName == "btn_new":
            widgets.stackedWidget.setCurrentWidget(widgets.new_page) # SET PAGE
            UIFunctions.resetStyle(self, btnName) # RESET ANOTHERS BUTTONS SELECTED
            btn.setStyleSheet(UIFunctions.selectMenu(btn.styleSheet())) # SELECT MENU

        if btnName == "btn_copy":
            self.copy_to_clipboard()

        if btnName == "btn_open":
            file_path, _ = QFileDialog.getOpenFileName(self, "Open CSV File", "", "CSV Files (*.csv);;All Files (*)")
            if file_path:
                try:
                    self.file_path = file_path
                    self.draw_graph(file_path)
                except Exception as e:
                    QMessageBox.critical(self, "Error", f"Failed to read file: {str(e)}")
            
        # PRINT BTN NAME
        print(f'Button "{btnName}" pressed!')


    # RESIZE EVENTS
    def resizeEvent(self, event):
        # Update Size Grips
        UIFunctions.resize_grips(self)

        # Redraw graph when resizing
        if widgets.stackedWidget.currentWidget() == widgets.new_page and self.file_path:
            self.draw_graph(self.file_path)

    # MOUSE CLICK EVENTS
    def mousePressEvent(self, event):
        # SET DRAG POS WINDOW
        self.dragPos = event.globalPos()

        # PRINT MOUSE EVENTS
        if event.buttons() == Qt.LeftButton:
            print('Mouse click: LEFT CLICK')
        if event.buttons() == Qt.RightButton:
            print('Mouse click: RIGHT CLICK')

    def event(self, event):
        return super().event(event)
    
    def eventFilter(self, obj, event):
        # print(obj.objectName(), event.type())
        return super().eventFilter(obj, event)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon("icon.ico"))
    window = MainWindow()
    sys.exit(app.exec_())
