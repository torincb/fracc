from PySide2.QtWidgets import QWidget

from Interface.MainWindow import Communicate
from Interface.UI.RenderControlWidgetUI import Ui_RenderControlWidget


class RenderControlWidget(QWidget, Ui_RenderControlWidget):
    """
    This widget contains the controls for rendering output.
    """
    _communicate = None

    def __init__(self, communicate: Communicate) -> None:
        """
        Initialize the widget.
        :param communicate: Communicate object of the main window
        """
        super(RenderControlWidget, self).__init__()
        self.setupUi(self)

        self._communicate = communicate
