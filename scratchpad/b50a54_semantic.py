"""SEMANTIC_GATE evidence for func_ov002_02050a54."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_GetCameraDistance"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_GetCameraDistance in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::02050a54 returns "
     "function_name Ov002_GetCameraDistance, param_count 1 and the three "
     "callees Ov022_GetEntryField20ByIndex_fde0, FX_Inv and "
     "QueryActiveStateOrDelegate."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "One parameter, nSelector. It indexes the twelve-byte record table and "
     "is compared against 0 and 10, the two values that get the depth "
     "interpolation and the world offset; every other value returns the bare "
     "base. The four callers pass it from runtime fields, so its range is not "
     "visible in the source."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "All five locals renamed and read back: iVar3 to pActor, iVar4 to "
     "nScale, iVar5 to nBase, uVar2 to nActiveId, lVar1 to nProduct."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_GetCameraDistance(int nSelector), read back from Ghidra after "
     "saving."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "Both data symbols were undefined DAT_ labels in the arm9_ov002 space. "
     "They are eight bytes apart, so data_ov002_0207e764[2] and "
     "data_ov002_0207e76c[0] are the same word, which is what makes the "
     "interpolation pull selector 10 toward the selector 0 entry. Created "
     "Ov002CameraDistEntry, twelve bytes with nDistance int at 0, the stride "
     "the multiply proves; applied as Ov002CameraDistEntry[11] at 0207e76c "
     "and labelled aOv002CameraDistTable, with int[2] at 0207e764 labelled "
     "aOv002CameraDistHead. Eleven is the lower bound the code itself proves, "
     "since the function distinguishes selector 0 and selector 10 by name; "
     "the true count is set by the callers' data and is recorded as such in "
     "the plate comment rather than asserted."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read back after save: the table at 0207e76c is Ov002CameraDistEntry[11] "
     "of length 132 and the head at 0207e764 is int[2] of length 8; the "
     "struct layout itself shows nDistance at offset 0."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "The script run returned success true with no endTransaction error, and "
     "the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature, the struct and both data definitions were re-read "
     "afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: all three callees already carried names, every "
     "parameter and local is named, and the two data symbols lost their DAT_ "
     "labels."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the integrated C reads the table through the same "
     "stride now encoded in Ov002CameraDistEntry and declares no struct of "
     "its own; it keeps both data symbols as externs because the delink needs "
     "both relocations, which matches the two labels now in Ghidra."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
