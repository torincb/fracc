from typing import Optional
from PySide2.QtWidgets import QWidget, QMainWindow, QMdiArea, QMdiSubWindow


class MainWindow(QMainWindow):
    """
    Main application window.
    """
    mdi: QMdiArea = None
    window1: QMdiSubWindow = None

    def __init__(self, parent: Optional[QWidget] = None) -> None:
        """
        Initialize the main window, child widgets, etc.
        """
        super().__init__(parent)

        self.initialize_widgets()
        self.setCentralWidget(self.mdi)

        self.setWindowTitle("Fracc")

    def initialize_widgets(self) -> None:
        """
        Create widgets contained in the window.
        """
        self.mdi = QMdiArea(self)
        self.window1 = QMdiSubWindow(self.mdi)
