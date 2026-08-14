"""SEMANTIC_GATE evidence for func_ov002_0205d214."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_HandlePanelInput"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_HandlePanelInput in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::0205d214 returns "
     "function_name Ov002_HandlePanelInput with param_count 2."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Two parameters, not the four the decompiler guessed. The whole "
     "disassembly was read: r2 and r3 are written before any read, and the "
     "pushed r3 slot at sp+0 is only ever used as the out parameter of "
     "ov002_ClassifyCode, so nothing arrives in them. Named nRaw, the input "
     "code that gets normalised, and nSound, the id played afterwards and "
     "forced negative by the cancel case to suppress it."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Nine locals renamed and read back: pSession, nCode, nPrevClass, "
     "nClass, nCount, nColumn, nColumnByte, nTracker and nDivMod. Three "
     "remaining slots are decompiler artifacts of the argument registers, "
     "in_r2, in_r3 and one spare; they carry no value in the ROM, which is "
     "why the prototype is two parameters, and they were given neutral spare "
     "names rather than invented meanings."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_HandlePanelInput(int nRaw, int nSound), read back from "
     "Ghidra after saving. Two callee prototypes were corrected in the same "
     "batch from the same evidence: 0205bbbc takes one argument, since the "
     "ROM sets r0 alone before the call, and 0205cbd0 takes none."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Extended the existing Ov002PanelSession, found at /khdays/ rather than "
     "the root, with the six bytes this function proves and no rival type. "
     "bListIndex at +3, previously pad0003, is the panel-list index clamped "
     "against its count; bDefaultKind at +7, carved out of pad0006, is the "
     "kind the restore case copies into bKind; bCursorRow at +0x31, "
     "previously pad0031, is the row the cursor rectangle is drawn on; and "
     "bListRowBase and bListRowOffset at +0x4ac and +0x4ad, previously the "
     "two-byte pad04ac, are the list area's first row and the drop from it to "
     "the cursor. The size is unchanged at 1572, so every new field landed in "
     "existing padding."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "The struct layout was re-read after save and shows bListIndex at 3, "
     "bDefaultKind at 7 with pad0006 shrunk to one byte and pad0008 covering "
     "the rest, and the size still 1572."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "The first run raised before opening any transaction, because the struct "
     "lookup by root path missed a type filed under /khdays/; the retry and "
     "the follow-up both returned success true with no endTransaction error, "
     "and the save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature and the struct layout were re-read afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt, and some removed: every parameter and real local "
     "is named, and two callees that carried guessed four-argument signatures "
     "now carry the arity the disassembly proves."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the integrated C reaches the same six offsets now "
     "named in Ghidra, and its local struct is a codegen mirror with matching "
     "offsets rather than a rival model."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
