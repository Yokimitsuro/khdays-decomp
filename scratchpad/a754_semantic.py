"""Semantic receipt for func_ov002_0205a754."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelListHasUsableEntry"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205a754. Responde si la lista tiene alguna entrada "
     "que el panel pueda usar: la recorre con NNS_FndGetNextListObject y, por "
     "cada Ov002PanelEntry, pregunta al filtro de grupo en 0x0205a714 por su "
     "nKey. La que pasa cuenta de inmediato si nAnyTag esta puesto; si no, "
     "ademas tiene que llevar nTag distinto de cero. La llama "
     "Ov002_PanelAnyListEntryAvailable, casada antes en esta misma sesion, "
     "sobre las listas 0 y 2."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad DOS, confirmada en el desensamblado: solo r0 y r1 se leen antes de "
     "escribirse; el prologo los copia a r7 y r6 para sobrevivir a las "
     "llamadas. Renombrados a pList y nAnyTag. El segundo NO es un indice de "
     "lista sino un permiso: cuando no es cero se salta la comprobacion del "
     "tag, y el caller le pasa 1 justo para la lista 2."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el prologo no tiene sub sp y ninguna llamada pasa "
     "de dos argumentos, asi que el r3 empujado es solo relleno de alineacion. "
     "La entrada recorrida vive en r5, la lista en r7, el permiso en r6 y el "
     "cero del filtro en r4, que mwcc mantiene en registro durante todo el "
     "bucle. Read-back LOCALS 0, asi que no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_PanelListHasUsableEntry(NNSFndList *pList, int nAnyTag). "
     "Devuelve 0 o 1: la salida temprana es movne r0,#1 con ldmiane, y la "
     "salida por agotamiento pone mov r0,#0. El caller lo usa como entero."),
    ("layout_decision", "reused"),
    ("layout_evidence",
     "Reutiliza dos tipos existentes sin cambiarlos. NNSFndList, aplicado al "
     "parametro pList: read-back len=12 con head_object, tail_object, "
     "num_objects y offset. Y Ov002PanelEntry para los objetos recorridos: la "
     "funcion lee +0x00 y +0x02 con ldrh, que son exactamente nKey y nTag "
     "ushort del tipo existente de 8 bytes, el mismo que ya reutilizo "
     "func_ov002_0205b778 para leer +0x02. Esta funcion lo confirma de forma "
     "independiente al leer AMBOS campos. No aparece ningun offset nuevo."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: pList tipado NNSFndList * en r0 y "
     "nAnyTag int en r1, NNSFndList len=12 con sus cuatro campos, "
     "Ov002PanelEntry len=8 con nKey +0x00, nTag +0x02 y nState +0x04, y el "
     "prototipo del caller Ov002_PanelAnyListEntryAvailable. No se creo ni "
     "extendio ningun tipo."),
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
     "tools/audit_struct_sync.py sale con codigo 0 y no lista NNSFndList ni "
     "Ov002PanelEntry con variantes en conflicto. Esta tanda no toco ningun "
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
