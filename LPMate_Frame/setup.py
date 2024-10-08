import sys
import os
from cx_Freeze import setup, Executable

# ADD FILES
files = ['icon.ico','themes/']

# TARGET
target = Executable(
    script="main.py",
    base="Win32GUI",
    icon="icon.ico"
)

# SETUP CX FREEZE
setup(
    name = "LPMate",
    version = "1.0",
    description = "Modern GUI for Python applications",
    author = "Andrew Yoon",
    options = {'build_exe' : {'include_files' : files}},
    executables = [target]
    
)
