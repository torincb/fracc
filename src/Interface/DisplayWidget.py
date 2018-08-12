import numpy as np

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Axes, Figure

from PySide2.QtWidgets import QWidget, QVBoxLayout

from Interface.MainWindow import Communicate
# from Interface.UI.DisplayWidgetUI import Ui_DisplayWidget


class DisplayWidget(QWidget):
    """
    This widget interactively displays 2D rendered results using matplotlib.
    """
    _communicate = None
    _canvas = None

    def __init__(self, communicate: Communicate) -> None:
        """
        Initialize the widget.
        :param communicate: Communicate object of the main window
        """
        super(DisplayWidget, self).__init__()
        # self.setupUi(self)

        self._communicate = communicate

        self.setup_widgets()

    def setup_widgets(self) -> None:
        """
        Initialize child widgets.
        """
        x = np.linspace(0, np.pi*4)
        y = np.sin(x)

        self._canvas = FigureCanvas(Figure(figsize=(5, 3)))
        axes: Axes = self._canvas.figure.add_subplot(111)
        axes.plot(x, y)

        toolbar = NavigationToolbar(self._canvas, self)

        layout = QVBoxLayout()
        layout.addWidget(self._canvas)
        layout.addWidget(toolbar)

        self.setLayout(layout)
