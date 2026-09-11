"""Register map of every parameter and local, from the compiler's own DWARF.

    python tools/regmap_dwarf.py <file.c> [more.c ...]

Compiles each file with the project flags plus -g (measured on
func_ov022_0208ded4: the .text is byte-identical with and without -g), then
reads DW_AT_location of every DW_TAG_formal_parameter and DW_TAG_variable.
A value that lives in a callee-saved register prints as r4..fp; one that the
compiler kept in a scratch register prints r0..r3; aggregates print "stack".

Use it instead of fingerprinting instructions when a residue is only register
names: it names which VALUE sits in which register, for any function, in one
command. The DIE order it prints is the compiler's symbol order (parameters
first, locals in reverse declaration order), which is also the order the
allocator hands out callee-saved registers from the top when nothing carries
a priority - so a value out of that sequence is the one with a priority.
"""
import os, sys, subprocess
os.chdir("E:/KH 3582/decomp")
sys.path.insert(0, "tools")
from match import FLAGS, MWCC, LIC
from elftools.elf.elffile import ELFFile
from elftools.dwarf.descriptions import describe_DWARF_expr
from elftools.dwarf.locationlists import LocationParser, LocationExpr

REGS = {0: "r0", 1: "r1", 2: "r2", 3: "r3", 4: "r4", 5: "r5", 6: "r6", 7: "r7", 8: "r8", 9: "sb", 10: "sl", 11: "fp", 12: "ip", 13: "sp", 14: "lr"}

def reg_of(expr_bytes):
    if not expr_bytes:
        return None
    op = expr_bytes[0]
    if 0x50 <= op <= 0x6f:          # DW_OP_reg0..31
        return REGS.get(op - 0x50, "r%d" % (op - 0x50))
    if op == 0x90:                   # DW_OP_regx
        return REGS.get(expr_bytes[1], "r%d" % expr_bytes[1])
    if 0x70 <= op <= 0x8f:           # DW_OP_breg
        return "stack"
    if op == 0x91:                   # DW_OP_fbreg
        return "stack"
    return "expr%02x" % op

def dump(cpath):
    o = cpath + ".g.o"
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = list(FLAGS)
    if cpath.lower().endswith(".cpp"):
        flags[flags.index("c99")] = "c++"
    r = subprocess.run([MWCC, "-c", "-g", *flags, "-o", o, cpath], capture_output=True, text=True, env=env)
    if r.returncode != 0:
        print(os.path.basename(cpath), "COMPILE FAIL"); return
    elf = ELFFile(open(o, "rb"))
    dw = elf.get_dwarf_info(relocate_dwarf_sections=False)
    locparser = LocationParser(dw.location_lists())
    out = []
    for cu in dw.iter_CUs():
        for die in cu.iter_DIEs():
            if die.tag not in ("DW_TAG_formal_parameter", "DW_TAG_variable"):
                continue
            name = die.attributes.get("DW_AT_name")
            loc = die.attributes.get("DW_AT_location")
            if name is None or loc is None:
                continue
            name = name.value.decode() if isinstance(name.value, bytes) else str(name.value)
            try:
                parsed = locparser.parse_from_attribute(loc, cu["version"], die)
            except Exception:
                parsed = None
            regs = []
            if isinstance(parsed, LocationExpr):
                regs.append(reg_of(bytes(parsed.loc_expr)))
            elif isinstance(parsed, list):
                for ent in parsed:
                    if hasattr(ent, "loc_expr"):
                        regs.append(reg_of(bytes(ent.loc_expr)))
            elif loc.form.startswith("DW_FORM_block") or loc.form == "DW_FORM_exprloc":
                regs.append(reg_of(bytes(loc.value)))
            regs = [x for x in regs if x]
            kind = "param" if die.tag == "DW_TAG_formal_parameter" else "local"
            out.append((kind, name, "/".join(dict.fromkeys(regs)) or "?"))
    print("== " + os.path.basename(cpath))
    for kind, name, regs in out:
        print("   %-5s %-12s %s" % (kind, name, regs))

for c in sys.argv[1:]:
    dump(c)
