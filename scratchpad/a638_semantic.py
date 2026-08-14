"""Semantic receipt for func_ov002_0205a638."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelAnyCellAvailable"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205a638. Responde si hay alguna celda disponible en "
     "la fila actual: cierto si la consulta global func_ov002_020575d0 devuelve "
     "distinto de cero, o si la mascara de habilitados no es cero y el segundo "
     "byte de alguna celda no es cero. Su resultado va como quinto argumento de "
     "func_ov002_0205b6dc tanto en el repaint como en el rebuild."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CERO, confirmada en el desensamblado: ningun registro de argumento "
     "se lee antes de escribirse; el prologo carga directamente el global. "
     "Read-back PARAMS 0."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es solo push {r3,r4,r5,lr} sin sub sp. "
     "El indice del bucle y su cota viven en r1 y r2, y el acumulador del "
     "resultado en r5, todos registros. Read-back LOCALS 0, asi que no hay nada "
     "que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_PanelAnyCellAvailable(void). Devuelve 0 o 1 en r0, valor que los "
     "dos callers usan como entero."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No descubre layout nuevo. Los tres campos que toca ya estaban tipados y "
     "verificados por read-back: bColumns uchar en +0x30, aCells "
     "Ov002PanelCell[551] en +0x32 y dwEnabledMask int en +0x4a8. Los dos "
     "primeros los habia establecido la tanda de func_ov002_0205b7dc y esta "
     "funcion los confirma de forma independiente: vuelve a indexar las celdas "
     "con desplazamiento a la izquierda uno y lectura en +0x33, es decir el "
     "segundo byte, que es exactamente la interpretacion de celda de dos bytes "
     "que se aplico alli."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion de los tres campos y del pool slot "
     "arm9_ov002.bss::0207f620 como Ov002PanelSession *. No se creo ni extendio "
     "ningun tipo porque no hacia falta."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los dos scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py no lista Ov002PanelSession ni Ov002PanelCell "
     "con variantes en conflicto. Esta tanda no toco ningun tipo."),
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
