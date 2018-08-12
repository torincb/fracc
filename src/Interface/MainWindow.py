import logging

from PySide2.QtCore import Qt
from PySide2.QtGui import QPixmap
from PySide2.QtWidgets import QApplication, QDockWidget, QFileDialog, QLabel, QTabWidget, QMainWindow, QMdiArea,\
    QMdiSubWindow

from Interface.AlgorithmControlWidget import AlgorithmControlWidget
from Interface.Communicate import Communicate
from Interface.DisplayWidget import DisplayWidget
from Interface.RenderControlWidget import RenderControlWidget
from Interface.UI.MainWindowUI import Ui_MainWindow


class MainWindow(QMainWindow, Ui_MainWindow):
    """
    Main application window.
    """
    # Widgets
    mdi = None
    algorithm_controls = None
    render_controls = None
    display = None
    # display_window = None

    # Internals
    _app = None
    _communicate = Communicate()

    def __init__(self, app: QApplication) -> None:
        """
        Initialize the _main window.
        """
        super(MainWindow, self).__init__()
        self.setupUi(self)

        self._app = app

        self.setup_widgets()
        self.setCentralWidget(self.mdi)

        self.setup_signals()

        self.setWindowTitle("Fracc")
        self.centre_on_screen()

    def setup_widgets(self) -> None:
        """
        Create widgets contained in the window.
        """
        self.mdi = QMdiArea(self)

        self.algorithm_controls = AlgorithmControlWidget(self._communicate)
        self.render_controls = RenderControlWidget(self._communicate)
        self.display = DisplayWidget(self._communicate)

        display_window = QMdiSubWindow(self.mdi)
        display_window.setWindowTitle("Display")
        display_window.setWidget(self.display)
        # self.display_window.setGeometry(0, 0, 400, 300)

        controls_tabs = QTabWidget()
        controls_tabs.addTab(self.algorithm_controls, self.algorithm_controls.windowTitle())
        controls_tabs.addTab(self.render_controls, self.render_controls.windowTitle())

        controls_dock = QDockWidget("Controls", self)
        controls_dock.setFloating(False)
        controls_dock.setWidget(controls_tabs)
        self.addDockWidget(Qt.LeftDockWidgetArea, controls_dock)

    def setup_signals(self) -> None:
        """
        Connect handlers to signals.
        """
        self._communicate.display_requested.connect(self.on_display_requested)

    def centre_on_screen(self) -> None:
        """
        Positions the window at the centre of the screen, and resizes it appropriately.
        """
        # Get the dimensions of the available screen space
        scrn_rect = self._app.desktop().availableGeometry()
        x, y, w, h = [getattr(scrn_rect, a)() for a in ("x", "y", "width", "height")]

        # Take 70% of screen and centre window
        win_w = int(0.8 * w)
        win_h = int(0.8 * h)
        win_x = int(x + (w - win_w) / 2)
        win_y = int(y + (h - win_h) / 2)

        self.setGeometry(win_x, win_y, win_w, win_h)

    def on_display_requested(self, param: str) -> None:
        """
        Called when a display is requested.
        """
        # TODO: implement
        logging.error("Unimplemented!")
        # file = QFileDialog.getOpenFileName()[0]
        # if file:
        #     pmap = QPixmap(file)
        #     if pmap:
        #         lbl = QLabel()
        #         lbl.setPixmap(pmap)
        #         self.display_window.setWidget(lbl)
        #         self.display_window.setGeometry(
        #             self.display_window.x(),
        #             self.display_window.y(),
        #             pmap.width(),
        #             pmap.height()
        #         )
        #     else:
        #         logging.error(f"Failed to open image: {file}")
