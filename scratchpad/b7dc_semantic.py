"""Semantic receipt for func_ov002_0205b7dc."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelRepaintForKind"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205b7dc. La funcion toma el modo de panel, lo "
     "clasifica con el mismo clasificador que el rebuild, y segun la clase "
     "repinta el widget correspondiente al kind indicado o desarma los dos "
     "nodos de seguimiento. El rebuild func_ov002_0205bff4 la llama DOS veces, "
     "al entrar y al salir, asi que toda transicion de panel pasa por ella."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Ghidra daba CUATRO parametros. El prologo solo mueve r0, r1 y r2 a "
     "callee-saved (r0 a r9, r1 a r8, r2 a r7) y r3 nunca se lee antes de "
     "escribirse: es aridad TRES. Coincide ademas con la llamada del rebuild ya "
     "casado, que pasa tres argumentos. Corregido a nMode, nKind y nFlag, leido "
     "de vuelta PARAMS 3."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "El marco es sub sp #8 con dos huecos. Stack[-0x24] es nColumn, el "
     "parametro de salida que rellena func_ov002_0205a3f0, tipado int. "
     "Stack[-0x28] es el area del quinto argumento saliente de las llamadas de "
     "cinco argumentos a func_ov002_0205aa3c, func_ov002_0205b6dc y "
     "func_ov002_0205b640, y queda nombrado aOutArgSlot para no confundirlo con "
     "una variable del programa."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelRepaintForKind(int nMode, int nKind, int nFlag). Retorno "
     "void: r0 no se define en ninguna de las salidas y ningun caller usa el "
     "resultado."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Dos refinamientos reales sobre Ov002PanelSession, extendiendo el tipo "
     "existente. Primero, +0x08 deja de ser relleno y pasa a int nField0008: el "
     "camino de clase 0 con kind 0 lo lee con ldr y lo compara contra cero. "
     "Segundo, y mas importante, la region de +0x32 NO es un array de bytes "
     "planos sino de celdas de DOS bytes: el camino de clase 1 calcula "
     "nColumn*6, suma 2 y 3, desplaza a la izquierda uno y lee en +0x33, es "
     "decir el SEGUNDO byte de las celdas nColumn*6+2 y nColumn*6+3. Creado "
     "Ov002PanelCell de 2 bytes con bFirst y bSecond, y aplicado como "
     "Ov002PanelCell[551] en +0x32, conservando los 1102 bytes."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion: nField0008 int en +0x08, aCells "
     "Ov002PanelCell[551] de 1102 bytes en +0x32, y sin tocar los campos que ya "
     "estaban correctos (wField0014, wField0016, bColumns, bCursorRow, lists "
     "NNSFndList[3] en +0x480, pCachedEntry, bListRowBase y bListRowOffset). "
     "Ov002PanelCell len=2 con sus dos campos."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY y ninguno "
     "dejo transaccion propia abierta. Sin errores de endTransaction."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: esta funcion sale de la cuenta de ov002 al "
     "recibir nombre semantico, asi que la deuda baja."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py no lista Ov002PanelSession ni Ov002PanelCell "
     "con variantes en conflicto. Se extendio el tipo existente en vez de crear "
     "uno rival."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:80]))
print("failures:", fail)
