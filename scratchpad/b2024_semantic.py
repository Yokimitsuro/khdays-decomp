"""Record the SEMANTIC_GATE evidence for the active function.

semantic-mark takes the field as a positional subcommand followed by its value;
boolean fields want the literal true, evidence fields want a sentence.
"""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_ApplyAnimMode"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_ApplyAnimMode in arm9_ov002 and read back by address: "
     "get_function_signature at arm9_ov002::02052024 returns "
     "function_name Ov002_ApplyAnimMode."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Five parameters named pActor, pAnimState, nNewMode, nKind and nFlags. "
     "pActor is the actor whose enable byte sits at +1, animation object at "
     "+4 and inline table at +0x13c; pAnimState is the animation state block; "
     "nNewMode is the requested mode; nKind the actor kind, where 1 gates the "
     "seek and 2 is excluded from the shared table path; nFlags is forwarded "
     "untouched to the five argument bind. Read back with param_count 5."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Four locals renamed and read back: bVar4 to bActorEnabled, iVar2 to "
     "nBlendCode, uVar3 to nTrack, cVar1 to nOldMode."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_ApplyAnimMode(int pActor, Ov002AnimStateBlock *pAnimState, "
     "int nNewMode, int nKind, int nFlags), read back from the signature "
     "endpoint after saving."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "Ov002AnimStateBlock created at 84 bytes and read back field by field: "
     "nCurrentMode char at 0, bModeChanged int at 4, pTables byte pointer at "
     "0x4c and nTableCount int at 0x50. The last two were already known from "
     "the teardown at 02051fc8, which frees pTables and walks nTableCount "
     "entries of stride 0x24; this function supplies the first two, the mode "
     "byte it compares and stores and the flag word it raises on a change."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Ov002AnimStateBlock pointer applied to pAnimState and confirmed in the "
     "read back prototype; the struct layout itself re-read after save."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "run_ghidra_script returned success true with no endTransaction error, "
     "and the following save succeeded, which proves no transaction leaked."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature and the struct layout were both re-read afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: three of the four callees were already named "
     "BindAnimTrack, Anim_SetFrameWrapped and RemapCodeValue, and every "
     "parameter and local of this function now carries a semantic name."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the only layout this function touches is "
     "Ov002AnimStateBlock, created here with the two offsets it proves and "
     "the two the teardown at 02051fc8 already proved, with no rival type for "
     "the same block."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
