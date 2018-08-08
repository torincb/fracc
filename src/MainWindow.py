from typing import Optional
from PySide2.QtCore import Qt
from PySide2.QtWidgets import QDockWidget
from PySide2.QtWidgets import QMainWindow
from PySide2.QtWidgets import QMdiArea
from PySide2.QtWidgets import QMdiSubWindow
from PySide2.QtWidgets import QWidget
from ComputationWidget import ComputationWidget
from ui.MainWindowUI import Ui_MainWindow


class MainWindow(QMainWindow, Ui_MainWindow):
    """
    Main application window.
    """
    mdi: QMdiArea = None
    display_window: QMdiSubWindow = None
    compute_controls: QDockWidget = None

    def __init__(self, parent: Optional[QWidget] = None) -> None:
        """
        Initialize the main window.
        """
        super(MainWindow, self).__init__()
        self.setupUi(self)

        self.initialize_widgets()
        self.setCentralWidget(self.mdi)

        self.setWindowTitle("Fracc")
        self.setGeometry(50, 50, 1280, 720)

    def initialize_widgets(self) -> None:
        """
        Create widgets contained in the window.
        """
        self.mdi = QMdiArea(self)

        # Display window
        self.display_window = QMdiSubWindow(self.mdi)
        self.display_window.setWindowTitle("Display")
        self.display_window.setGeometry(0, 0, 400, 300)

        # Docked computation control widget
        self.compute_controls = ComputationWidget(parent=self)
        compute_dock = QDockWidget("Computation Controls", self)
        compute_dock.setFloating(False)
        compute_dock.setWidget(self.compute_controls)
        self.addDockWidget(Qt.LeftDockWidgetArea, compute_dock)
