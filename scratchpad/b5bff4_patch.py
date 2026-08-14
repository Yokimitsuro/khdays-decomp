"""The ROM emits all three tests first and the bodies after, which is a switch
lowered to a compare chain, not an if/else-if. Convert both chains in case 0.
"""
p = "build/try/func_ov002_0205bff4.c"
s = open(p).read()

old1 = """        if (nFrom == 0) {
            func_ov002_0205ae08(s->wField0014, s->nField000c, 0);
        } else if (nFrom == 1) {
            int nValue = func_ov002_0205a638();

            func_ov002_0205aba4(4, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
        } else if (nFrom == 2) {
"""
new1 = """        switch (nFrom) {
        case 0:
            func_ov002_0205ae08(s->wField0014, s->nField000c, 0);
            break;
        case 1: {
            int nValue = func_ov002_0205a638();

            func_ov002_0205aba4(4, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
        }
        case 2: {
"""
assert old1 in s
s = s.replace(old1, new1)

old2 = """            func_ov002_0205ab90(5, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
        }

        if (nTo == 0) {
            func_ov002_0205ae08(s->wField0014, s->nField000c, 1);
        } else if (nTo == 1) {
            if (s->aBitIndex[0] == 0xff) {
                func_ov002_0205ae08(3, 0, 1);
            } else {
                func_ov002_0205ae08(3, 1, 1);
            }
        } else if (nTo == 2) {
            func_ov002_0205ae08(4, 1, 1);
        }
        break;
"""
new2 = """            func_ov002_0205ab90(5, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
        }
        }

        switch (nTo) {
        case 0:
            func_ov002_0205ae08(s->wField0014, s->nField000c, 1);
            break;
        case 1:
            if (s->aBitIndex[0] == 0xff) {
                func_ov002_0205ae08(3, 0, 1);
            } else {
                func_ov002_0205ae08(3, 1, 1);
            }
            break;
        case 2:
            func_ov002_0205ae08(4, 1, 1);
            break;
        }
        break;
"""
assert old2 in s
s = s.replace(old2, new2)
open(p, "w").write(s)
print("patched")
