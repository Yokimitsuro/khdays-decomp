"""SEMANTIC_GATE evidence for func_ov002_02051eec."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_LoadAnimTables"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_LoadAnimTables in arm9_ov002 and read back in the "
     "prototype returned after saving."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Five parameters named pActor, pAnimState, nGroup, nHeap and nBaseId. "
     "pActor supplies the animation object at +4 handed to the table build; "
     "pAnimState is the block that owns the id list, the loaded blocks and "
     "the tables; nGroup is the archive group folded into the path; nHeap is "
     "the heap tag, always used as nHeap + 7; nBaseId is added to each entry "
     "id to give the file id. Read back in the prototype."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "All locals named across two passes and read back: nCount, nIndex, "
     "nEntry, nOffset, nDirWord, nFileId, pBlock, pIdCursor and nScan; the "
     "second pass reported RENAMEDCOUNT 2 for the two the decompiler "
     "regenerated after the struct was applied."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_LoadAnimTables(int pActor, Ov002AnimStateBlock *pAnimState, "
     "int nGroup, int nHeap, int nBaseId), read back from Ghidra."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Ov002AnimStateBlock extended with anAnimIds, a char[13] at +8 "
     "terminated by -1, and apBlocks, a void*[13] at +0x18. Those two fill "
     "exactly the gap up to pTables at +0x4c and close the struct at 84 "
     "bytes, which the read back confirms field by field. The block array is "
     "the one the teardown at 02051fc8 frees, so the constructor, the "
     "teardown and the mode apply now share a single type."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Ov002AnimStateBlock pointer applied to pAnimState and confirmed in the "
     "read back prototype; the extended layout re-read after save."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Both script runs returned success true with no endTransaction error, "
     "and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "struct layout was re-read afterwards and shows all six fields."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: every parameter and local of this function carries "
     "a semantic name, and the two callees it reaches beyond the heap "
     "allocator keep the names they already had."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the only layout touched is Ov002AnimStateBlock, "
     "extended in place rather than duplicated, and its C mirror in the "
     "integrated source carries the same offsets and field names."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
