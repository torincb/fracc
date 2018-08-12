from PySide2.QtCore import QObject, Signal


class Communicate(QObject):
    """
    Contains signals that will be used by multiple child widgets.
    """
    # TODO: how is this to be parameterized?
    display_requested = Signal(str)

    def __init__(self) -> None:
        """
        Initialize the object.
        """
        super(Communicate, self).__init__()
