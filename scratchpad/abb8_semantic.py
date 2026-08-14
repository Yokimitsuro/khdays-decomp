"""Semantic receipt for func_ov002_0205abb8."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelApplySlotState"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205abb8. Aplica un descriptor de estado al nodo de "
     "seguimiento de tag de un slot: resuelve aNodes[nSlot] en +0x620 y "
     "aSlotStates[nState] en +0x5f4 y hace tail call al metodo de contexto en "
     "0x02053510. Es la PRIMERA llamada del cuerpo de "
     "Ov002_PanelPushSlotState, casada en la vuelta anterior."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad DOS, confirmada en el desensamblado: solo r0 y r1 se leen antes de "
     "escribirse, cada uno como indice de un array distinto, y r2 y r3 no se "
     "tocan. Renombrados a nSlot y nState, con los mismos nombres que el "
     "caller, que le pasa sus dos primeros parametros sin transformarlos. "
     "Read-back PARAMS 2 en r0 y r1."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales ni marco: la funcion es una hoja de tail call de ocho "
     "instrucciones, sin stmdb ni sub sp. Todo ocurre en r0, r1, r2 y r12. "
     "Read-back LOCALS 0, asi que no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelApplySlotState(int nSlot, int nState). Retorno void: no "
     "hay epilogo, la funcion sale por bx r12 heredando el retorno del destino, "
     "que tampoco define r0, y el caller no usa ningun resultado."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Extiende el tipo existente sin cambiar su tamano ni ningun offset. El "
     "array de palabras en +0x5f4 ya existia como aWords05f4 int[11], y esta "
     "funcion es la PRIMERA evidencia de que lo indexa: el ROM calcula "
     "s + nState*4 + 0x5f4 con el mismo nState que el caller compara contra 0, "
     "3 y 6, y las once entradas cubren exactamente el hueco hasta aNodes en "
     "+0x620. Renombrado a aSlotStates con comentario de campo que registra el "
     "indice. Read-back: aSlotStates int[11] de 44 bytes en +0x5f4, "
     "Ov002PanelSession sigue en 1572 bytes. Tambien se reutiliza sin cambios "
     "aNodes Ov002TagTrackerNode *[1], creado en la tanda anterior."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los dos parametros int en r0 y r1, "
     "los campos aSlotStates int[11] en +0x5f4 y aNodes "
     "Ov002TagTrackerNode *[1] en +0x620 con la sesion todavia en 1572 bytes, y "
     "el pool slot arm9_ov002.bss::0207f620 como Ov002PanelSession *. Ademas se "
     "leyo el destino del tail call, confirmado por relocs.txt: "
     "from:0x0205abdc kind:load to:0x02053510."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el que "
     "renombra el campo del struct."),
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
     "ni Ov002TagTrackerNode con variantes en conflicto. Se renombro un campo "
     "del tipo existente en vez de crear uno rival, y no se anadio ni movio "
     "ningun offset."),
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
