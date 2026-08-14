"""Semantic receipt for func_ov002_0205a7b8."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelAnyListEntryAvailable"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205a7b8. Responde si alguna de las dos listas de "
     "entradas seguidas por el panel tiene algo que mostrar. Si "
     "Ov002_GetPanelField0058 devuelve distinto de cero la pregunta se reduce a "
     "si alguna lista tiene primer objeto, consultado con "
     "NNS_FndGetNextListObject; si devuelve cero, cada lista la recorre el "
     "ayudante filtrado en 0x0205a754, y la segunda se pide con su modo "
     "alternativo. Es la gemela de Ov002_PanelAnyCellAvailable: su resultado "
     "ocupa el mismo hueco de argumento de func_ov002_0205b6dc en el repaint, "
     "pero en el camino de kind 2 en vez del de kind 1."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CERO, confirmada en el desensamblado: ningun registro de argumento "
     "se lee antes de escribirse; el prologo carga directamente el global y "
     "pone el acumulador a cero. Read-back PARAMS 0."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es solo push {r3,r4,r5,lr} sin sub sp y "
     "sin ningun argumento saliente que pase de cuatro. El puntero de sesion "
     "vive en r4, el acumulador del resultado en r5 y la entrada consultada en "
     "r0, todos registros. Read-back LOCALS 0, asi que no hay nada que "
     "renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_PanelAnyListEntryAvailable(void). El epilogo devuelve r5 por r0 "
     "y el caller lo usa como entero."),
    ("layout_decision", "reused"),
    ("layout_evidence",
     "Reutiliza el layout existente sin cambiarlo y lo confirma de forma "
     "independiente. La funcion direcciona +0x480 y +0x498 del objeto de "
     "sesion; la diferencia es 0x18, es decir DOS entradas de NNSFndList, que "
     "el read-back da con len=12. Eso encaja exactamente con el campo lists "
     "NNSFndList[3] de 36 bytes en +0x480 que establecio la tanda de "
     "func_ov002_0205b7dc, y confirma que los indices usados son 0 y 2. No hay "
     "ningun offset nuevo: la funcion no lee ningun otro campo."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion: NNSFndList len=12, campo lists NNSFndList[3] de "
     "36 bytes en +0x480 de Ov002PanelSession, y el pool slot "
     "arm9_ov002.bss::0207f620 tipado Ov002PanelSession *. No se creo ni "
     "extendio ningun tipo porque no hacia falta."),
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
     "tools/audit_struct_sync.py sale con codigo 0 y no lista Ov002PanelSession "
     "ni NNSFndList con variantes en conflicto. Esta tanda no toco ningun "
     "tipo."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:120]))
print("failures:", fail)
