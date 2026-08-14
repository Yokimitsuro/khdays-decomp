"""SEMANTIC_GATE evidence for func_ov002_02073ed0."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_SetKeyNodeVisible"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_SetKeyNodeVisible in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::02073ed0 returns "
     "function_name Ov002_SetKeyNodeVisible with param_count 3."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Three parameters named nKey, bVisible and nPriority. nKey goes to "
     "ov002_FindKeyIndex to get the slot; bVisible picks between the setting "
     "and the clearing call; nPriority is masked to three bits and written at "
     "bit 16, and is untouched on the hiding path."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "All three locals renamed and read back as pContext, nIndex and pNode; a "
     "second run of the same script reports RENAMEDCOUNT 0, which proves none "
     "are left generated."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_SetKeyNodeVisible(int nKey, int bVisible, int nPriority), "
     "read back from Ghidra after saving."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No new layout. The chain this function walks belongs to types that are "
     "already modelled: the slot record array hangs off +0x44 of the context "
     "the global at 0207fa14 points to, and the node at +0xf4 of a record is "
     "an ov107 render node, owned by that overlay's own types rather than by "
     "ov002. The only field this function itself proves is the three-bit "
     "priority at bits 16 to 18 of the node's word at +0xc, which is a "
     "bitfield inside an ov107 structure, so it belongs in that overlay's "
     "model and is recorded in the plate comment rather than forced into an "
     "ov002 rival type. Reviewed Ov002PanelSession and Ov002UiContext; "
     "neither is reached from here."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "The three parameters typed int and confirmed in the read back "
     "prototype; no other object in this function is typable from here, as "
     "recorded above."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Both script runs returned success true with no endTransaction error, "
     "and the following save succeeded."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "A separate save_program call returned Program saved successfully; the "
     "signature was re-read afterwards and still shows the new name and the "
     "three parameters."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: all three callees already carried names, "
     "ov002_FindKeyIndex, Ov107_OrLowFlags and its clearing counterpart, and "
     "every parameter and local of this function is named."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: no type was created or changed, and the integrated C "
     "declares no struct, reaching the chain through the same offsets the "
     "plate comment records."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
