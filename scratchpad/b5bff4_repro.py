"""Synthetic reproduction of the residue's shape: two int parameters, a global
struct pointer live across the whole body, a classifier call that reads a field
through that pointer, and a switch whose branches each need their own
temporaries. The aim is a repro that pushes the same nine registers and puts the
pointer in the LOW callee-saved register, so the search for a form that puts it
in a HIGH one can be done in milliseconds instead of on the 1416-byte function.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)

HDR = """typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bKind;
    u8 bMode;
    u8 bIndex;
    u8 bListIndex;
    u8 bKey;
    u8 pad0005[2];
    u8 bDefaultKind;
    u8 pad0008[4];
    int nField000c;
    u8 pad0010[4];
    u16 wField0014;
    u8 pad0016[0x1c];
    u8 aBitIndex[0x44e];
    u8 listItems[0x18];
    u8 listEntries[0xc];
    void *pCachedEntry;
} Sess;

extern Sess *gp;
extern int cls(int *pOut, int nCode);
extern int q0(int);
extern void q1(int, int, int);
extern void q2(int, int, int, int);
extern void *q3(void *, u16);
extern int q4(int, int);
extern void q5(void *, int, int, int, int, int, int, int);
extern void q6(int, int, int, u16, int);
"""


def analyse(src):
    p = "build/try/b5bff4_rp.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None, str(ex).split("\n")[0][:70]
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {"size": len(code), "push": ins[0]}
    for t in ins[:14]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            if "p0" not in d:
                d["p0"] = m.group(1)
            elif "k" not in d:
                d["k"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "p1" not in d:
            d["p1"] = m.group(1)
    return d, None


def show(tag, src):
    d, err = analyse(src)
    if err:
        print("%-24s FAIL %s" % (tag, err))
        return
    print("%-24s size=%-5d p0=%-4s p1=%-4s s=%-4s k=%-4s  %s"
          % (tag, d["size"], d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), d.get("k", "?"), d["push"]))


BODY = """
void rep(int nFrom, int nTo) {
    int nColumn;
    int nTag;
    Sess *s = gp;
    int nClass = cls(&nColumn, s->bMode);

    q1(s->bMode, nTo, 0);

    switch (nClass) {
    case 0:
        q1(s->wField0014, s->nField000c, 0);
        if (s->aBitIndex[0] == 0xff) {
            q1(3, 0, 1);
        } else {
            q1(3, 1, 1);
        }
        break;

    case 1: {
        int nOffset = nColumn * 6;

        q2(nFrom + nOffset, nFrom, 1, q0(nFrom + nOffset));
        s->bIndex = (u8)(nColumn * 6 + nTo);
        break;
    }

    case 2: {
        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
        u16 *pEntry;
        int bFlag;
        int nSlot;

        pEntry = (u16 *)q3(s->listItems, (u16)nOld);
        bFlag = 0;
        if (q4(0, *pEntry) != 0 && q4(1, *pEntry) != 0) {
            bFlag = 1;
        }
        nSlot = pEntry == 0 ? -1 : q0(*pEntry);
        q5(s->listItems, nSlot, nFrom, nOld, 1, bFlag, 0, 0);

        pEntry = (u16 *)q3(s->listItems, (u16)nNew);
        bFlag = 0;
        if (q4(0, *pEntry) != 0 && q4(1, *pEntry) != 0) {
            bFlag = 1;
        }
        nSlot = pEntry == 0 ? -1 : q0(*pEntry);
        q5(s->listItems, nSlot, nTo, nNew, 1, bFlag, 1, 0);
        s->bListIndex = (u8)(nColumn * 6 + nTo);
        break;
    }

    case 3: {
        int nOld = nFrom + nColumn * 6;
        u16 *pEntry;
        int nSlot;

        nClass = nTo + nColumn * 6;
        pEntry = (u16 *)q3(s->listEntries, (u16)nOld);
        nTag = pEntry != 0 ? q0(pEntry[1] & 0xff) : 0;
        nSlot = pEntry == 0 ? -1 : q0(*pEntry);
        q5(s->listEntries, nSlot, nFrom, nOld, 1, 1, 0, nTag);

        pEntry = (u16 *)q3(s->listEntries, (u16)nClass);
        nSlot = pEntry == 0 ? -1 : q0(*pEntry);
        q5(s->listEntries, nSlot, nTo, nClass, 1, 1, 1, nTag);
        s->bKey = (u8)nClass;
        s->pCachedEntry = pEntry;
        break;
    }

    case 5: {
        int bFlag = 0;
        u16 nKey = *(u16 *)s->pCachedEntry;

        if (q4(0, nKey) != 0 && q4(1, nKey) != 0) {
            bFlag = 1;
        }
        q6(4, 0, 0x3e0, (u16)(bFlag != 0 ? 0xf : 0xe), 1);
        q6(5, 0, 0x3f0, 0xf, 0);
        s->bDefaultKind = 0;
        break;
    }
    }

    s->bKind = (u8)nTo;
    q1(s->bMode, nTo, 0);
}
"""
show("repro base", HDR + BODY)
