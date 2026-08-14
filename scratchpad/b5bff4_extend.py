"""In the reproduction the only thing that flipped the pair was extending the
class past the switch. Try that on the real function and watch the map, even
where it costs size, to confirm the lever transfers.
"""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from b5bff4_map import report, SYM

BASE = open("build/try/%s.c" % SYM).read()
report("base", BASE)

TAIL = """    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, 0);
"""
assert TAIL in BASE

report("tail_uses_class",
       BASE.replace(TAIL, """    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, nClass);
"""))

report("tail_stores_class",
       BASE.replace(TAIL, """    s->bKind = (u8)nClass;
    func_ov002_0205b7dc(s->bMode, nTo, 0);
"""))

report("class_zeroed_tail",
       BASE.replace(TAIL, """    nClass = 0;
    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, nClass);
"""))

report("session_reread_tail",
       BASE.replace(TAIL, """    data_ov002_0207f620->bKind = (u8)nTo;
    func_ov002_0205b7dc(data_ov002_0207f620->bMode, nTo, 0);
"""))
