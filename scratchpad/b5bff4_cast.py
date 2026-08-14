"""The reproduction says a cast of the global through an integer, or a no-op
pointer addition, changes how mwcc ranks the session without changing the code
size. Apply it to the real function.
"""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from b5bff4_map import report, SYM

BASE = open("build/try/%s.c" % SYM).read()
SES = "    Ov002PanelSession *s = data_ov002_0207f620;\n"
assert SES in BASE

report("base", BASE)
report("via_int", BASE.replace(
    SES, "    Ov002PanelSession *s ="
         " (Ov002PanelSession *)(int)data_ov002_0207f620;\n"))
report("plus_zero", BASE.replace(
    SES, "    Ov002PanelSession *s ="
         " (Ov002PanelSession *)((char *)data_ov002_0207f620 + 0);\n"))
report("via_uint", BASE.replace(
    SES, "    Ov002PanelSession *s ="
         " (Ov002PanelSession *)(unsigned int)data_ov002_0207f620;\n"))
report("via_void", BASE.replace(
    SES, "    Ov002PanelSession *s ="
         " (Ov002PanelSession *)(void *)data_ov002_0207f620;\n"))
