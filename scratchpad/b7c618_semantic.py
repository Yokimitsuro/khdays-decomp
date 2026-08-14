"""SEMANTIC_GATE evidence for func_ov002_0207c618."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_RebindAnimTracks"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_RebindAnimTracks in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::0207c618 returns "
     "function_name Ov002_RebindAnimTracks with param_count 3."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Three parameters named pAnim, nBlend and nFrame. pAnim is the animation "
     "object whose track table sits at +0xe0 as five halfwords; nBlend is the "
     "blend passed to the bind, an int here that the call narrows to short; "
     "nFrame is the frame every live track is seeked to. Read back in the "
     "prototype."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "The single local was renamed uVar1 to nTrack and read back; it is the "
     "0 to 4 track counter, used raw as the table index once converted."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_RebindAnimTracks(short *pAnim, int nBlend, int nFrame), read "
     "back from Ghidra after saving."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No new layout: this function touches exactly one field of the animation "
     "object, the five-halfword track table at +0xe0, and reaches it through "
     "the same short pointer arithmetic its callers and the bind at 0202accc "
     "already use. The animation object is owned by the middleware at "
     "0202accc and 01fff774, not by ov002, so extending an ov002 type for it "
     "would create a rival to the middleware's own view; "
     "Ov002AnimStateBlock, the ov002 type in this area, describes the state "
     "block and not the animation, and was reviewed and correctly left "
     "untouched."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "pAnim typed as short pointer, matching the halfword table indexing, and "
     "confirmed in the read back prototype; nBlend and nFrame typed int."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "run_ghidra_script returned success true with no endTransaction error, "
     "and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature was re-read afterwards and still shows the new name."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: both callees already carried the names "
     "BindAnimTrack and Anim_SetFrameWrapped, and every parameter and the "
     "single local of this function now have semantic names."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: no type was created or changed, and the integrated C "
     "declares no struct of its own, so there is nothing that can drift from "
     "Ghidra."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
