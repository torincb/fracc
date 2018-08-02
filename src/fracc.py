import logging
import logging.config
import os
import os.path as path
import subprocess
import sys
from PySide2 import QtWidgets
from MainWindow import MainWindow


def setup_logging() -> None:
    """
    Sets up logging.
    """
    logging.config.fileConfig("logging.ini")


def invoke_uic(file_path: str) -> None:
    """
    Invokes pyside2-uic to convert a single path. If the command fails, its error output is shown and an exception is
    raised.
    """
    py_file_path = path.splitext(file_path)[0] + ".py"

    logging.debug("Generating %s ...", py_file_path)

    call = ["pyside2-uic", "-o", py_file_path, file_path]
    result = subprocess.run(call, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if result.returncode != 0:
        call_str = " ".join(['"' + arg + '"' if " " in arg else arg for arg in call])
        logging.critical("command failed (exit status %d): %s", result.returncode, call_str)
        logging.critical("with output:\n%s", result.stderr.decode())

        # (Try to) delete the failed file (it still produces an empty file upon failure)
        try:
            os.remove(py_file_path)
        except OSError:
            pass

        raise RuntimeError("Failed to generate UI file: %s" % file_path)


def is_generated(file_path: str) -> bool:
    """
    Given the path to a .ui file, checks whether a corresponding .py file exists and is newer than the .ui file. Returns
    True if these conditions are met, and False otherwise.
    """
    py_file_path = path.splitext(file_path)[0] + ".py"
    try:
        py_stat = os.stat(py_file_path)
    except OSError:
        # .py file does not exist
        return False

    ui_stat = os.stat(file_path)
    if ui_stat.st_mtime > py_stat.st_mtime:
        # .py file is older than .ui file
        return False

    return True


def generate_ui() -> None:
    """
    Generates all the UI files in the project, using the pyside2-uic script. Currently assumes all UI files are in the
    'ui' directory within this script's directory.
    """
    ui_path = path.join(path.dirname(path.abspath(__file__)), "ui")
    for dirname, _, filenames in os.walk(ui_path):
        for filename in filenames:
            if path.splitext(filename)[1].lower() == ".ui":
                file_path = path.join(dirname, filename)

                if not is_generated(file_path):
                    invoke_uic(file_path)


def main() -> None:
    """
    Serves as fracc's entry point. Initializes the GUI and runs the QT application.
    """
    setup_logging()

    logging.info("Fracc session started")

    generate_ui()

    app = QtWidgets.QApplication(sys.argv)

    main_window = MainWindow()
    main_window.show()
    app.exec_()

    logging.info("Fracc session ended")


if __name__ == "__main__":
    main()