import os
import platform
import time
import subprocess
import ctypes


class CMathEngine:
    def __init__(self):
        self.base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.core_dir = os.path.join(self.base_dir, "core_c")
        self.c_source = os.path.join(self.core_dir, "math_engine.c")

        is_windows = platform.system() == "Windows"
        if is_windows:
            lib_name = "math_engine.dll"
        else:
            lib_name = "math_engine.so"
        self.lib_path = os.path.join(core_dir, lib_name)
