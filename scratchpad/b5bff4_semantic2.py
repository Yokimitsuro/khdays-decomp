"""Update the semantic receipt after the layout batch. The earlier receipt said
no_new_layout, which was true of my own candidate but is no longer true: the
matched source establishes real layout, so the decision and its evidence have to
be corrected rather than left standing.
"""
import subprocess
import sys

MARKS = [
    ("layout_decision", "new_layout_applied"),
    ("layout_evidence",
     "El layout que establece la fuente casada SI es nuevo, asi que rectifico el "
     "no_new_layout que habia registrado antes con mi propio candidato. Aplicado "
     "extendiendo tipos existentes, nunca creando rivales: Ov002PanelEntry pasa "
     "de 2 a 8 bytes con nKey u16 en +0, nTag u16 en +2 y nState int en +4, "
     "campos que el codigo prueba en los casos 3 y 5; la region +0x480 de "
     "Ov002PanelSession deja de ser char[8] mas relleno y pasa a ser "
     "NNSFndList[3], tres headers contiguos de 12 bytes, reutilizando el "
     "NNSFndList que ya existia en /khdays; y pCachedEntry deja de ser byte* "
     "para ser Ov002PanelEntry*. Creado ademas el enum Ov002PanelClass con los "
     "seis valores del clasificador. La funcion usa los elementos 0 y 2 de la "
     "lista, +0x480 y +0x498; el header intermedio en +0x48c no se toca aqui "
     "pero queda tipado por el array."),
    ("types_evidence",
     "Read-back por direccion y por tipo: Ov002PanelEntry len=8 con sus tres "
     "campos, NNSFndList len=12 reutilizado, Ov002PanelClass con los seis "
     "valores, Ov002PanelSession con lists NNSFndList[3] de 36 bytes en +0x480 "
     "y pCachedEntry Ov002PanelEntry* en +0x4a4, y el pool slot "
     "arm9_ov002.bss::0207f620 como Ov002PanelSession* con nombre "
     "gOv002PanelSession. Ov002PanelMoveState NO se lleva a Ghidra: es un "
     "agregado local solo de matching y su campo nTagOrder esta muerto a "
     "proposito, asi que no es un campo de runtime."),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py no lista Ov002PanelEntry ni Ov002PanelSession "
     "como tipos con variantes en conflicto; NNSFndList aparece solo como parte "
     "de un tipo de ov008 sin discrepancia. Se extendieron tipos existentes en "
     "vez de crear rivales, de modo que no puede aparecer divergencia nueva."),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: ov002 queda en 244 sin nombrar, y esta funcion "
     "sale de esa cuenta por tener nombre semantico. No se introduce deuda."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    ok = r.returncode == 0
    if not ok:
        fail += 1
    print("%-30s %s %s" % (field, "OK" if ok else "FAIL",
                           "" if ok else (r.stdout + r.stderr).strip()[:90]))
print("failures:", fail)
