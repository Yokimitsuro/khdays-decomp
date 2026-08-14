"""Semantic receipt for func_ov002_0205ad5c."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelWriteSlotLabel"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205ad5c. Escribe la etiqueta de 8x2 tiles de un "
     "slot del panel en el recurso de item 0x09: limpia las dos filas de tiles "
     "del slot con MIi_CpuClear16 sobre 0x16 bytes, es decir once tiles, y "
     "despues escribe ocho glifos consecutivos desde nTile en la fila superior "
     "y los ocho siguientes, desde nTile+8, en la inferior. La llama "
     "Ov002_PanelRefreshRowHeader, casada la vuelta anterior, como PRIMERA de "
     "sus dos llamadas de widget."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CINCO, confirmada en el desensamblado: r0, r1, r2 y r3 se copian a "
     "callee-saved en el prologo antes de la llamada, y el quinto se lee con "
     "ldr r1,[sp,#0x20], justo por encima de los 32 bytes que empuja el "
     "prologo. Renombrados a nSlot, nColumn, nTile, nPalette y bRightAlign. "
     "nPalette se llama asi porque el ROM solo lo usa como operando desplazado "
     "orr rX,rY,r6,lsl #0xc, es decir el nibble alto de la entrada del mapa de "
     "tiles. Read-back PARAMS 5."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el prologo no tiene sub sp y ninguna llamada pasa "
     "de tres argumentos. Todo vive en registros: r9 el puntero de recurso, r4 "
     "la fila, r5 la sangria, r8 nColumn, r7 nTile, r6 nPalette, r2 el glifo "
     "inferior y r1 el indice del bucle. Read-back LOCALS 0, asi que no hay "
     "nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelWriteSlotLabel(int nSlot, int nColumn, int nTile, "
     "int nPalette, int bRightAlign). Retorno void: el epilogo restaura pc tras "
     "el bucle sin definir r0. Los parametros de glifo son int y NO u16: el ROM "
     "incrementa nTile y su pareja inferior sin enmascarar, y una version con "
     "u16 anade seis instrucciones lsl/lsr, exactamente 24 bytes de mas."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No descubre layout nuevo y no existe objeto tipable propio: la funcion no "
     "toca ninguna estructura ni ningun global. Trabaja sobre el mapa de tiles "
     "crudo que devuelve Ov002_GetItemResource(0x09), cuyo prototipo ya estaba "
     "revisado y leido de vuelta como int Ov002_GetItemResource(int nItemId), y "
     "todos los demas valores son parametros escalares. La geometria "
     "descubierta (fila = 0x18 - (6 - nSlot)*2, 32 entradas u16 por fila, 0x40 "
     "bytes de paso entre filas, glifos superiores en nTile e inferiores en "
     "nTile+8, paleta en el nibble alto) queda en el comentario de funcion de "
     "Ghidra porque son constantes de un mapa de tiles, no campos de un "
     "registro."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los cinco parametros int con su "
     "almacenamiento r0, r1, r2, r3 y Stack[0x0], el prototipo del callee "
     "Ov002_GetItemResource, y el del caller Ov002_PanelRefreshRowHeader, que "
     "confirma que su bRightAlign es el mismo eje que aqui. No se creo ni "
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
     "tools/audit_struct_sync.py sale con codigo 0 y no lista ningun conflicto. "
     "Esta tanda no creo ni modifico ningun tipo, asi que no puede introducir "
     "variantes rivales."),
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
