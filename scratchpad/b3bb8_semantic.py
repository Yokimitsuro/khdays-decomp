"""SEMANTIC_GATE evidence for func_ov002_02053bb8."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_GetItemResource"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_GetItemResource in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::02053bb8 returns "
     "function_name Ov002_GetItemResource with param_count 1."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "One parameter, nItemId. It is passed to Ov002_ItemIdToSlot to get the "
     "tracked slot and is compared against 0x18 on the untracked path, so it "
     "is the item id and not the slot; the disassembly keeps it in r4 across "
     "the call precisely for that second test."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Both locals renamed and read back: iVar1 to nSlot, iVar2 to nResource."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_GetItemResource(int nItemId), read back from Ghidra after "
     "saving."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "The global at 0207f60c was undefined data carrying only a DAT_ label "
     "even though forty matched sources reach through it, so there was no "
     "existing type to extend and no rival to avoid. Created Ov002UiContext "
     "at 0xe0 bytes, which covers every offset the matched tree uses through "
     "this global: 0xc, 0x12, 0x52, 0x58, 0x94, 0xa4, 0xb0 and 0xdc. Named "
     "the two fields this function proves: anItemResourceFallback, an int[15] "
     "at 0x58 bounded by the next known offset, and pItemResourceTable, an "
     "int pointer at 0x94 whose entry for a slot sits at index slot plus one. "
     "Read back at offsets 88 and 148. Later functions extend the rest."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "The global itself typed as Ov002UiContext * and labelled "
     "pOv002UiContext. It lives in the arm9_ov002.bss address space, not the "
     "code space, which is why the first attempt reported insufficient "
     "memory; read back after the retarget as type Ov002UiContext * of "
     "length 4."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Both script runs returned success true; the one that failed did so with "
     "a CodeUnitInsertionException from the wrong address space, which left "
     "no transaction open, and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature and the struct layout were re-read afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: both callees already carried names, "
     "Ov002_ItemIdToSlot and G2S_GetBG0ScrPtr, the parameter and both locals "
     "are named, and the global this function reaches lost its DAT_ label."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the integrated C reaches the context through the same "
     "two offsets now named in Ghidra and declares no struct of its own."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
