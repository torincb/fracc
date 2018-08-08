from typing import Optional
from PySide2.QtWidgets import QWidget
from ui.ComputationWidgetUI import Ui_ComputationWidget


class ComputationWidget(QWidget, Ui_ComputationWidget):
    """
    This widget contains the controls for fractal generation.
    """
    def __init__(self, parent: Optional[QWidget] = None) -> None:
        """
        Initialise the widget.
        """
        super(ComputationWidget, self).__init__()
        self.setupUi(self)
