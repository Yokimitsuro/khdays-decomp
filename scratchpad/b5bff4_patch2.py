"""Case 1: the ROM keeps column*6 in a register for the first pair and only
re-derives it with an mla for the second. The candidate fuses both into mla.
"""
p = "build/try/func_ov002_0205bff4.c"
s = open(p).read()

OLD = """    case 1: {
        int nIndex;

        func_ov002_0205afb4(nFrom + nColumn * 6, nFrom, 1,
                            func_ov002_0205a600(nFrom + nColumn * 6), 0);
        nIndex = nColumn * 6 + nTo;
"""
NEW = """    case 1: {
        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
"""
assert OLD in s
open(p, "w").write(s.replace(OLD, NEW))
print("patched")
