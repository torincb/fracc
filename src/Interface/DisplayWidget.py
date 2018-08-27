import numpy as np
from scipy.ndimage import imread

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Axes, Figure

from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QFileDialog

from Interface.MainWindow import Communicate
# from Interface.UI.DisplayWidgetUI import Ui_DisplayWidget


class DisplayWidget(QWidget):
    """
    This widget interactively displays 2D rendered results using matplotlib.
    """
    _communicate = None

    canvas = None
    toolbar = None
    btn_select_region = None

    ax = None

    def __init__(self, communicate: Communicate) -> None:
        """
        Initialize the widget.
        :param communicate: Communicate object of the main window
        """
        super(DisplayWidget, self).__init__()
        # self.setupUi(self)

        self._communicate = communicate

        self.setup_widgets()
        self.setup_signals()

    def setup_widgets(self) -> None:
        """
        Initialize child widgets.
        """
        # TODO: Switch to Designer when this inevitably becomes too complicated (but how do I incorporate matplotlib
        # TODO: widgets that way? should I leave empty layouts and then create those widgets here?)
        self.canvas = FigureCanvas(Figure(figsize=(5, 3)))
        self.toolbar = NavigationToolbar(self.canvas, self)
        self.btn_select_region = QPushButton("Select render region")

        controls_layout = QVBoxLayout()
        controls_layout.addWidget(self.btn_select_region)
        controls_layout.addStretch()

        plot_layout = QVBoxLayout()
        plot_layout.addWidget(self.canvas)
        plot_layout.addWidget(self.toolbar)

        root_layout = QHBoxLayout()
        root_layout.addLayout(controls_layout)
        root_layout.addLayout(plot_layout)

        self.setLayout(root_layout)

    def setup_signals(self) -> None:
        """
        Initialize signals.
        """
        self.btn_select_region.clicked.connect(self.on_select_region)

    def on_select_region(self) -> None:
        """
        Allow the user to select a region on the plot.
        """
        # TODO: Implement
        if self.ax is None:
            self.ax = self.canvas.figure.add_subplot(111)
        else:
            self.ax.clear()
        file = QFileDialog.getOpenFileName()[0]
        if file:
            meem = imread(file)
            self.ax.imshow(meem)
            self.canvas.draw()
