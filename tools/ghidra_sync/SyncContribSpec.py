# Apply a contribution sync spec (csig.py output) to Ghidra: prototypes, parameter names,
# plate comments, and the files' local struct layouts (scoped under /khdays/contrib).
import json, re, os, sys
import java.lang.Exception
from ghidra.program.model.data import (IntegerDataType, UnsignedIntegerDataType, ShortDataType, UnsignedShortDataType,
    ByteDataType, SignedByteDataType, CharDataType, LongLongDataType, UnsignedLongLongDataType, FloatDataType, DoubleDataType,
    VoidDataType, PointerDataType, ArrayDataType, StructureDataType, CategoryPath, Undefined, DataTypeConflictHandler)
from ghidra.program.model.listing import ParameterImpl, ReturnParameterImpl, Function
from ghidra.program.model.symbol import SourceType

# The spec is csig.py's output. ROOT is the repo when this script runs from tools/ghidra_sync/;
# a copy living in a Ghidra script directory outside the repo falls back to the checkout below.
_here = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(_here)) if os.path.basename(_here) == "ghidra_sync" else "E:/KH 3582/decomp"
SPEC = os.path.join(ROOT, "build", "ghidra_sync_spec.json")
LOG = os.path.join(ROOT, "build", "ghidra_sync.log")
dtm = currentProgram.getDataTypeManager()
st = currentProgram.getSymbolTable()
log = open(LOG, "w")
def out(s):
    log.write(s + "\n")

BUILTIN = {
    "u8": ByteDataType(), "s8": SignedByteDataType(), "char": CharDataType(), "vu8": ByteDataType(),
    "u16": UnsignedShortDataType(), "s16": ShortDataType(), "vu16": UnsignedShortDataType(), "fx16": ShortDataType(),
    "u32": UnsignedIntegerDataType(), "s32": IntegerDataType(), "vu32": UnsignedIntegerDataType(), "BOOL": IntegerDataType(),
    "u64": UnsignedLongLongDataType(), "s64": LongLongDataType(), "fx64": LongLongDataType(),
    "float": FloatDataType(), "double": DoubleDataType(), "void": VoidDataType(),
}
_fx32 = dtm.getDataType("/fx32")
BUILTIN["fx32"] = _fx32 if _fx32 is not None else IntegerDataType()
GENERIC = set(["Actor", "Obj", "Entry", "Node", "S", "T", "Self", "State", "Runtime", "Part", "Rec", "Msg", "Blk12", "Blk44",
               "Placement", "Hit", "HitRecord", "AnimState", "Quat", "InitConfig", "OpenParams", "RigHeader", "Widget", "Scroll",
               "Panel", "Item", "Block", "Ctx", "Sub", "Table", "Slot", "Record", "Params", "Header", "Frame", "List", "Link",
               "Body", "Model", "Model0c", "Data", "Info", "Cmd", "Target", "Player", "Enemy", "Attach", "Desc", "Unit", "Task",
               "ActorNode", "ActorSub", "ReactionCtx", "ComboRecord", "ComboLock", "SweepContact", "PlayerSlot", "FanQuery",
               "BlendTable", "StreamGroup", "CueEntry", "PanelInitConfig", "SlotLink", "Vec3", "Manager", "Handle", "Owner"])

def find_named_type(name):
    """An existing Ghidra type named `name` anywhere (root, /khdays, ...)."""
    for cat in ("/khdays/", "/", "/khdays/contrib/"):
        t = dtm.getDataType(cat + name)
        if t is not None:
            return t
    lst = java.util.ArrayList()
    dtm.findDataTypes(name, lst)
    for t in lst:
        if not isinstance(t, PointerDataType):
            return t
    return None

import java.util

class FileCtx:
    def __init__(self, entry):
        self.entry = entry
        self.stem = entry["name"]
        m = re.search(r"overlays/(ov\d+)/", entry["path"])
        self.unit = m.group(1) if m else ("libs" if entry["path"].startswith("libs/") else "main")
        self.defs = dict((s["name"], s) for s in entry["structs"])
        self.made = {}      # struct name -> DataType (created or found)
        self.failed = set()
        self.cat = CategoryPath("/khdays/contrib/" + self.unit)

    def resolve(self, base, ptr, arrays=None, for_struct=False):
        """-> (DataType, size, align). None when unresolvable."""
        dt = None
        if base == "funcptr":
            dt = PointerDataType(VoidDataType())
        elif base in BUILTIN:
            dt = BUILTIN[base]
        elif base.startswith("type "):
            dt = find_named_type(base[5:])
            if dt is None and base[5:] in self.defs:
                dt = self.struct_type(base[5:])
        elif base.startswith("struct "):
            dt = self.struct_type(base[7:])
        if dt is None:
            if ptr:
                dt = VoidDataType()
            else:
                return None
        for _ in range(ptr):
            dt = PointerDataType(dt)
        if arrays:
            for n in reversed(arrays):
                if n <= 0:
                    return None
                dt = ArrayDataType(dt, n, dt.getLength())
        size = dt.getLength()
        if size <= 0 and not (isinstance(dt, VoidDataType)):
            return None
        align = 1
        if ptr or arrays:
            base_dt = dt
            while isinstance(base_dt, ArrayDataType):
                base_dt = base_dt.getDataType()
            align = 4 if isinstance(base_dt, PointerDataType) else self.align_of(base_dt)
        else:
            align = self.align_of(dt)
        return dt, size, align

    def align_of(self, dt):
        if isinstance(dt, PointerDataType):
            return 4
        if isinstance(dt, StructureDataType) or dt.__class__.__name__ in ("StructureDB", "StructureDataType"):
            a = 1
            for c in dt.getComponents():
                cd = c.getDataType()
                a = max(a, self.align_of(cd))
            return a
        if isinstance(dt, ArrayDataType):
            return self.align_of(dt.getDataType())
        n = dt.getLength()
        return 4 if n >= 4 else (2 if n == 2 else 1)

    def layout(self, name, d, selfdt):
        """(fields, total, align) for the file's definition of `name`, or None. selfdt stands in for pointers to itself."""
        fields = []
        cur = 0
        salign = 1
        unit = None
        self.made[name] = selfdt
        for f in d["fields"]:
            if f.get("bits") is not None:
                r = self.resolve(f["base"], 0)
                if r is None:
                    out("  %s: struct %s field %s unresolved" % (self.stem, name, f["name"])); return None
                dt, size, align = r
                if unit is not None and unit[1] == size and unit[2] + f["bits"] <= size * 8:
                    unit[2] += f["bits"]
                    fields[-1][4] = fields[-1][4] + " " + f["name"] + ":" + str(f["bits"])
                    continue
                cur = (cur + align - 1) // align * align
                unit = [cur, size, f["bits"]]
                fields.append([cur, dt, size, f["name"], "bitfields: " + f["name"] + ":" + str(f["bits"])])
                salign = max(salign, align)
                cur += size
                continue
            unit = None
            r = self.resolve(f["base"], f["ptr"], f["array"] or None, True)
            if r is None:
                out("  %s: struct %s field %s unresolved (%s)" % (self.stem, name, f["name"], f["base"])); return None
            dt, size, align = r
            cur = (cur + align - 1) // align * align
            if f.get("off") is not None and f["off"] != cur:
                out("  %s: struct %s field %s computed 0x%x but commented 0x%x -- skipped" % (self.stem, name, f["name"], cur, f["off"])); return None
            fields.append([cur, dt, size, f["name"], None])
            salign = max(salign, align)
            cur += size
        total = (cur + salign - 1) // salign * salign
        if total == 0:
            return None
        return fields, total, salign

    def struct_type(self, name):
        if name in self.made:
            return self.made[name]
        if name in self.failed:
            return None
        d = self.defs.get(name)
        canon = d.get("canon") if d else None
        if canon:
            t = find_named_type(canon)
            if t is not None:
                self.made[name] = t
                return t
        generic = name in GENERIC or len(name) <= 4
        gname = name + "__" + self.stem if generic else name
        existing = None if generic else find_named_type(name)
        if existing is not None and (d is None or not d["ok"]):
            self.made[name] = existing
            return existing
        if d is None or not d["ok"]:
            self.failed.add(name)
            out("  %s: struct %s has no usable definition" % (self.stem, name))
            return None
        # sizing pass: self-pointers stand in as void*
        lay = self.layout(name, d, VoidDataType())
        if lay is None:
            del self.made[name]; self.failed.add(name)
            return None
        fields, total, salign = lay
        if existing is not None:
            if existing.getLength() == total:
                self.made[name] = existing
                return existing
            out("  %s: struct %s exists in Ghidra with size 0x%x, file says 0x%x -> %s in contrib" % (self.stem, name, existing.getLength(), total, name + "__" + self.stem))
            gname = name + "__" + self.stem
        already = dtm.getDataType(self.cat.getPath() + "/" + gname)
        if already is not None:
            self.made[name] = already
            return already
        stt = dtm.addDataType(StructureDataType(self.cat, gname, 0), DataTypeConflictHandler.KEEP_HANDLER)
        # real pass: self-pointers point at the DB struct
        lay = self.layout(name, d, stt)
        fields, total, salign = lay
        stt.growStructure(total)
        for off, dt, size, fname, comment in fields:
            try:
                stt.replaceAtOffset(off, dt, size, fname, comment)
            except (Exception, java.lang.Exception) as e:
                out("  %s: struct %s field %s at 0x%x failed: %s" % (self.stem, name, fname, off, str(e)[:60]))
        self.made[name] = stt
        out("  %s: created %s (0x%x, %d fields)" % (self.stem, gname, total, len(fields)))
        return stt

AF = currentProgram.getAddressFactory()
def find_function(stem):
    """By address when the name carries one (func_ovNNN_XXXXXXXX, func_XXXXXXXX, Name_0xXXXXXXXX), else by symbol."""
    m = re.match(r"^func_(ov\d+)_([0-9a-fA-F]{8})$", stem)
    if m:
        space = AF.getAddressSpace("arm9_" + m.group(1))
        if space is None:
            return None
        return getFunctionAt(space.getAddress(int(m.group(2), 16)))
    m = re.match(r"^func_([0-9a-fA-F]{8})$", stem) or re.match(r"^\w+_0x([0-9a-fA-F]{8})$", stem)
    if m:
        return getFunctionAt(AF.getDefaultAddressSpace().getAddress(int(m.group(1), 16)))
    for sym in st.getGlobalSymbols(stem):
        f = getFunctionAt(sym.getAddress())
        if f is not None:
            return f
    return None

spec = json.load(open(SPEC))
done = protos = plates = structs_total = 0
skipped = []
for entry in spec:
    stem = entry["name"]
    f = find_function(stem)
    if f is None:
        skipped.append(stem + ":nofunc"); continue
    curated = not (f.getName() == stem or f.getName().startswith("FUN_"))
    if curated:
        # a function named by hand keeps its prototype unless its parameters were never named
        pnames = [prm.getName() for prm in f.getParameters()]
        if any(not re.match(r"^param_\d+$", n) for n in pnames):
            if entry["plate"] and not (f.getComment() or "").strip():
                tid = currentProgram.startTransaction("contrib plate " + stem)
                try:
                    f.setComment(entry["plate"]); plates += 1
                finally:
                    currentProgram.endTransaction(tid, True)
            skipped.append(stem + ":curated(" + f.getName() + ")"); continue
    ctx = FileCtx(entry)
    tid = currentProgram.startTransaction("contrib sync " + stem)
    ok = False
    try:
        # structs first (also the ones only referenced by locals)
        for s in entry["structs"]:
            ctx.struct_type(s["name"])
        p = entry["proto"]
        if p:
            r = ctx.resolve(p["ret"]["base"], p["ret"]["ptr"])
            params = []
            good = r is not None
            for prm in p["params"]:
                rr = ctx.resolve(prm["base"], prm["ptr"])
                if rr is None:
                    good = False; break
                params.append(ParameterImpl(prm["name"], rr[0], currentProgram))
            if good:
                f.updateFunction(None, ReturnParameterImpl(r[0], currentProgram), params,
                                 Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, True, SourceType.USER_DEFINED)
                protos += 1
            else:
                out("  %s: prototype not applied (unresolved type)" % stem)
        if entry["plate"] and not (f.getComment() or "").strip():
            f.setComment(entry["plate"])
            plates += 1
        ok = True
        done += 1
    except (Exception, java.lang.Exception) as e:
        out("  %s: FAILED %s" % (stem, str(e)[:120]))
    finally:
        currentProgram.endTransaction(tid, ok)
    structs_total += len(ctx.made)
out("done=%d protos=%d plates=%d struct-refs=%d skipped=%s" % (done, protos, plates, structs_total, skipped[:20]))
log.close()
print("done=%d protos=%d plates=%d skipped=%d" % (done, protos, plates, len(skipped)))
print("isChanged=%s" % currentProgram.isChanged())
