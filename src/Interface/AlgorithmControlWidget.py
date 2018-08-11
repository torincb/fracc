import logging

from PySide2.QtWidgets import QWidget

from Interface.Communicate import Communicate
from Interface.UI.AlgorithmControlWidgetUI import Ui_AlgorithmControlWidget


class AlgorithmControlWidget(QWidget, Ui_AlgorithmControlWidget):
    """
    This widget contains the controls for fractal generation.
    """
    _communicate = None

    def __init__(self, communicate: Communicate) -> None:
        """
        Initialize the widget.
        :param communicate: Communicate object of the main window
        """
        super(AlgorithmControlWidget, self).__init__()
        self.setupUi(self)

        self._communicate = communicate

        self.setup_signals()

    def setup_signals(self) -> None:
        """
        Sets up signals for controls.
        """
        self.btn_compute.clicked.connect(self.on_compute)

    def on_compute(self) -> None:
        """
        Called when 'Compute' is clicked.
        """
        self._communicate.display_requested.emit("test")
