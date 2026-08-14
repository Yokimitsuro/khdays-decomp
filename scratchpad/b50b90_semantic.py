"""SEMANTIC_GATE evidence for func_ov002_02050b90."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_UpdateCameraDistance"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_UpdateCameraDistance in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::02050b90 returns "
     "function_name Ov002_UpdateCameraDistance with param_count 1."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "One parameter, nSelector, the same selector the plain lookup at "
     "02050a54 takes: it is multiplied by twelve and used to reach both the "
     "target the smoothing aims at and the floor the two rate limits clamp "
     "against."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "All ten locals renamed and read back: pCamera, pTable, nOffset, "
     "nWanted, nLength, nStep, nDot, nProbe, aTo and aAim."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_UpdateCameraDistance(int nSelector), read back from Ghidra "
     "after saving."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Extended Ov002CameraDistEntry and corrected where it sits. This "
     "function indexes from 0207e764 with the same twelve-byte stride that "
     "02050a54 uses from 0207e76c, which proves the record array starts at "
     "0207e764 and that the other label is field +8 of record zero, not the "
     "start; the typing put in last function was therefore eight bytes off "
     "and has been re-based. The struct now names nTargetDistance at 0 and "
     "nBaseDistance at 8, read back at those offsets, and the array is "
     "Ov002CameraDistEntry[11] of length 132 at 0207e764. The stale label at "
     "0207e76c was renamed aOv002CameraDistBaseColumn so it says what it is "
     "instead of claiming to be the table."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read back after save: the table at 0207e764 is Ov002CameraDistEntry[11] "
     "length 132, the struct shows nTargetDistance at 0 and nBaseDistance at "
     "8, and the two labels resolve to aOv002CameraDistTable and "
     "aOv002CameraDistBaseColumn respectively."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Both script runs returned success true with no endTransaction error, "
     "and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature, the struct and both labels were re-read afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: every parameter and local is named, the callees "
     "already carried names, and the correction removed a misleading label "
     "rather than adding one."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync, and one removed: the integrated C reads the record at "
     "the same stride now encoded in Ov002CameraDistEntry, and the type in "
     "Ghidra now sits where the two functions' indexing actually proves it "
     "sits rather than eight bytes into it."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
