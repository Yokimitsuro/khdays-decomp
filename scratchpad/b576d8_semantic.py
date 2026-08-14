"""SEMANTIC_GATE evidence for func_ov002_020576d8."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_BlitNibbleRun"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_BlitNibbleRun in arm9_ov002 and read back by address: "
     "the signature endpoint at arm9_ov002::020576d8 returns function_name "
     "Ov002_BlitNibbleRun with param_count 7 and an empty callee list, which "
     "matches the function having no relocations."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Seven parameters named pDst, nRight, nCount, nWidth, nPad, nRow and "
     "pSrc, the last three arriving on the stack at sp+0x10, sp+0x14 and "
     "sp+0x18 above the four pushed words. pDst is the tiled character "
     "buffer; nRight is the right margin subtracted from the aligned width; "
     "nCount is the run length and gates both loops; nWidth and nPad are "
     "summed and rounded up to a whole tile; nRow scales by four, the stride "
     "of one pixel row inside a tile; pSrc is the run of pixel values."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "All locals named and read back: nStart, nColumn, nAligned, nIndex, "
     "pCursor and pSrcByte. The decompiler renumbers its generated names on "
     "every pass, so the final script renames whatever still matches the "
     "generated pattern rather than a fixed list; a second run of it reports "
     "RENAMEDCOUNT 0, which proves none are left."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_BlitNibbleRun(byte *pDst, int nRight, int nCount, int "
     "nWidth, int nPad, int nRow, byte *pSrc), read back from Ghidra after "
     "saving."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No new layout: this function touches no struct at all. Its destination "
     "is a raw tiled character buffer addressed by arithmetic, 0x20 bytes per "
     "tile and four bytes per pixel row within a tile, and its source is a "
     "flat run of bytes; both arrive as parameters, so there is no global or "
     "object to type. The tile geometry is recorded in the plate comment "
     "rather than invented as a struct, since a character buffer has no "
     "fields. Reviewed Ov002UiContext and Ov002RootContext, the two ov002 "
     "context types, and neither is reached from here."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Both pointer parameters typed as byte pointers, matching the unsigned "
     "byte loads the disassembly actually uses, and confirmed in the read "
     "back prototype; the five integer parameters typed int."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Every script run returned success true with no endTransaction error, "
     "and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature was re-read afterwards and still shows the new name, the "
     "seven parameters and the empty callee list."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: the function has no callees to name, and every "
     "parameter and local now carries a semantic name."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: no type was created or changed and the integrated C "
     "declares no struct, so there is nothing that can drift from Ghidra."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
