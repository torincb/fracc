import logging
import logging.config
import os
import os.path as path
import subprocess
import sys
from PySide2 import QtWidgets


def setup_logging() -> None:
    """
    Sets up logging.
    """
    logging.config.fileConfig("logging.ini")


def setup_simple_logging() -> None:
    """
    Sets up a console handler which receives all logs of all levels. Useful for dev purposes.
    """
    logging.config.dictConfig({
        "version": 1,
        "handlers": {
            "console": {
                "class": "logging.StreamHandler",
                "formatter": "simple",
                "stream": sys.stdout
            }
        },
        "formatters": {
            "simple": {
                "format": r"%(asctime)s - %(levelname)s: %(message)s",
                "datefmt": r"%H:%M:%S"
            }
        },
        "root": {
            "level": "DEBUG",
            "handlers": ["console"]
        }
    })


def generate_ui() -> None:
    """
    Generates all the UI files in the project, using the pyside2-uic script. Currently assumes all UI files are in
    directories named 'UI', at any level within this script's directory.
    """
    logging.debug("Generating UI...")

    root_path = path.dirname(path.abspath(__file__))
    logging.debug(f"Source root: {root_path}")

    for dirname, _, filenames in os.walk(root_path):
        if path.basename(dirname) == "UI":
            for filename in filenames:
                if path.splitext(filename)[1].lower() == ".ui":
                    file_path = path.join(dirname, filename)

                    if not _is_generated(file_path):
                        _invoke_uic(file_path)


def _invoke_uic(file_path: str) -> None:
    """
    Invokes pyside2-uic to convert a single UI file. If the command fails, its error output is shown and an exception is
    raised.
    """
    py_file_path = path.splitext(file_path)[0] + ".py"

    logging.info(f"Generating {py_file_path} ...")

    call = ["pyside2-uic", "-o", py_file_path, file_path]
    result = subprocess.run(call, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if result.returncode != 0:
        call_str = " ".join(['"' + arg + '"' if " " in arg else arg for arg in call])
        logging.critical(f"command failed (exit status {result.returncode}): {call_str}")
        logging.critical(f"with output:\n{result.stderr.decode()}")

        # (Try to) delete the failed file (it still produces an empty file upon failure)
        try:
            os.remove(py_file_path)
        except OSError:
            pass

        raise RuntimeError("Failed to generate UI file: %s" % file_path)


def _is_generated(file_path: str) -> bool:
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


def _main() -> None:
    """
    Serves as fracc's entry point. Initializes the GUI and runs the QT application.
    """
    setup_logging()

    logging.info("Fracc session started")

    generate_ui()

    app = QtWidgets.QApplication(sys.argv)

    # DO NOT move this import to the top!
    from Interface.MainWindow import MainWindow

    main_window = MainWindow(app)
    main_window.show()
    app.exec_()

    logging.info("Fracc session ended")


if __name__ == "__main__":
    _main()
