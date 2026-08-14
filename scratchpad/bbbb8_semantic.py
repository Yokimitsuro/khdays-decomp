"""SEMANTIC_GATE evidence for func_ov002_0206bbb8."""
import subprocess
import sys

CTL = [sys.executable, ".claude/hooks/khdays_control.py", "semantic-mark"]

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_AddMissionTally"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Renamed to Ov002_AddMissionTally in arm9_ov002 and read back by "
     "address: the signature endpoint at arm9_ov002::0206bbb8 returns "
     "function_name Ov002_AddMissionTally with param_count 3."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Three parameters, not the four the decompiler guessed: the "
     "disassembly never stores a fourth argument and the stack record is "
     "built only from r8, r9 and r7. Named nIndex, nKind and nValue. nIndex "
     "selects the slot or the posted id and is rejected when positive for "
     "the session-wide kinds; nKind selects the accumulator; nValue is the "
     "amount added, and a zero value makes the whole call a no-op."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Every local named across three passes, the decompiler renumbering them "
     "between passes: pRoot, ppRoot, nSlotIndex, nSlotIndexAlt, "
     "bSessionLive, nIdMask, nIdMaskWide, nScratchR1, nPackedCur, nAddLo, "
     "nAddHi, reqKind, reqIndex and reqValue. Final read back shows no "
     "generated name left."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_AddMissionTally(int nIndex, int nKind, int nValue), read "
     "back from Ghidra after saving."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Two existing types extended in place, no rival created. "
     "Ov002RootContext gained the four fields filling its unnamed gap between "
     "the leave byte at 0x8b68 and the scene hook at 0x8b7c: "
     "nTallyChangedMask u16 at 0x8b6a, nTallyScalar short at 0x8b6c, "
     "anTallySlots short[5] at 0x8b6e and nTallyPair int at 0x8b78, which "
     "close the gap exactly. Ov002SessionBlock gained anTallyIds char[5] at "
     "0xb9 and nTallyIdMask byte at 0xbe, filling its gap between aSlots and "
     "nPhase; the read back shows offsets 185 and 190 with nPhase still at "
     "192 and the size unchanged at 200."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Both struct layouts re-read field by field after save; the root stays "
     "36254 bytes and the session block 200, so the new fields landed in the "
     "existing padding rather than shifting anything."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "All three script runs returned success true with no endTransaction "
     "error, and both saves succeeded afterwards."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "Separate save_program calls returned Program saved successfully; the "
     "signature and both struct layouts were re-read afterwards."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "No new unnamed debt: every parameter, every local and every field this "
     "function touches now carries a semantic name, and the four offsets it "
     "writes in the root were previously anonymous padding."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "No struct desync: the integrated C reaches the root and session through "
     "the same offsets now named in Ghidra, and its only local struct is the "
     "eight-byte stack record handed to the deferred handler, which exists "
     "solely to make mwcc build the frame the ROM builds."),
]

for field, value in MARKS:
    r = subprocess.run(CTL + [field, value], capture_output=True, text=True)
    if r.returncode != 0:
        print("FAIL %-32s %s" % (field, (r.stderr or r.stdout).strip()[:140]))
    else:
        print("ok   %s" % field)
