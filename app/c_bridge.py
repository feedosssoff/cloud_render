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

        self._ensure_compiled(is_windows)
        self.lib = ctypes.CDLL(self.lib_path)

    def _ensure_compiled(self, is_windows):
        compiled = os.path.exists(self.lib_path)
        if compiled and os.path.exists(self.c_source):
            if os.path.getmtime(self.c_source) > os.path.getmtime(self.lib_path):
                compiled = False

        if not compiled:
            print(f"Компиляция ядра {self.c_source} -> {self.lib_path}")
            if is_windows:
                cmd = ["gcc", "-O3", "-shared", "-o", self.lib_path, self.c_source, "-lm"]
            else:
                cmd = ["gcc", "-O3", "-shared", "-fPIC", "-o", self.lib_path, self.c_source, "-lm"]

            res = subprocess.run(cmd, capture_output=True, text=True)
            if res.returncode != 0:
                raise RuntimeError(f"Ошибка компиляции ядра:\n{res.stderr}")
            print("Библиотека успешно скомпилирована")
