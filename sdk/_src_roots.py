"""Shared: enumerate every directory that holds a .c source file.

Includes src/{auto,calls,asm_stubs/*} and libs/<top>/<module>/{auto,calls,
asm_stubs/*}. Kept in sync with tools/audit_progress.py and tools/gen_delinks.py.
"""
import os


def src_roots(root):
    subs = ("auto", "calls", "asm_stubs/auto", "asm_stubs/calls")
    out = [os.path.join("src", s) for s in subs]
    ov_root = os.path.join(root, "src", "overlays")
    if os.path.isdir(ov_root):
        for ov in sorted(os.listdir(ov_root)):
            if not os.path.isdir(os.path.join(ov_root, ov)):
                continue
            for s in subs:
                out.append(f"src/overlays/{ov}/{s}")
    libs_root = os.path.join(root, "libs")
    if os.path.isdir(libs_root):
        for top in sorted(os.listdir(libs_root)):
            tp = os.path.join(libs_root, top)
            if not os.path.isdir(tp):
                continue
            for mod in sorted(os.listdir(tp)):
                mp = os.path.join(tp, mod)
                if not os.path.isdir(mp):
                    continue
                for s in subs:
                    out.append(f"libs/{top}/{mod}/{s}")
    return out
