"""Record the semantic-gate evidence for the active function."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected",
     "Decompilacion y desensamblado leidos en Ghidra antes del C. Modo ARM "
     "confirmado, 349 instrucciones, 58 bloques, 54 llamadas, complejidad "
     "ciclomatica 30, en arm9_ov002::0205bff4. Callees ya nombrados que fijan "
     "la semantica: ov002_ClassifyCode, Ov002_FindSlotByKey, "
     "Ov002_Ctx_FindActiveEntryByTag, Ov002_SelectEntry, List_GetNthObject, "
     "NNS_FndGetNextListObject, Ov002_ForwardToSubDc."),
    ("semantic_name", "Ov002_PanelApplyCursorMove"),
    ("function_rename_readback",
     "Leido de vuelta por direccion: NAME Ov002_PanelApplyCursorMove."),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205bff4. La funcion clasifica el modo de panel "
     "activo, repinta el hueco que se abandona y el que se entra, y anota el "
     "nuevo hueco en la sesion, asi que el nombre describe el movimiento de "
     "cursor del panel y no una accion generica."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Ghidra tenia CUATRO parametros inventados, param_1 a param_4 en r0 a r3, "
     "cuando la funcion solo recibe dos. Corregido a nFromSlot y nToSlot, "
     "ambos int, y leido de vuelta: PARAMS 2. r2 y r3 no se leen nunca antes "
     "de escribirse, lo que confirma la aridad real de 2."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "El unico local de pila verdadero es el que el clasificador rellena por "
     "su parametro de salida: Stack[-0x28], renombrado nColumns y tipado int. "
     "Los cuatro huecos por debajo, Stack[-0x2c] a Stack[-0x38], son el area "
     "de argumentos salientes que mwcc reserva para las llamadas de ocho "
     "argumentos a func_ov002_0205b0dc, y quedan nombrados aOutArgSlot0 a 3 "
     "para que no se confundan con variables del programa."),
    ("prototype_readback",
     "void Ov002_PanelApplyCursorMove(int nFromSlot, int nToSlot)"),
    ("prototype_evidence",
     "Retorno void: r0 no se define en la salida y ningun caller usa el "
     "resultado. Aridad 2 verificada por lectura de r0 y r1 unicamente."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No descubre layout nuevo. El tipo Ov002PanelSession ya existe en "
     "/khdays, 1572 bytes, y cubre TODOS los desplazamientos que toca esta "
     "funcion: bKind en 0, bMode en 1, bIndex en 2, bListIndex en 3, bKey en "
     "4, bDefaultKind en 7, nField000c en 12, wField0014 en 20, aEntries en "
     "50, listItems en 1152, listEntries en 1176 y pCachedEntry en 1188. Se "
     "reutiliza tal cual en vez de crear un tipo rival; el struct del .c es "
     "solo la herramienta de codegen y agrupa el relleno en arrays."),
    ("types_applied_readback",
     "GLOBAL arm9_ov002.bss::0207f620 type=Ov002PanelSession * "
     "names=[gOv002PanelSession]"),
    ("types_evidence",
     "El pool slot guarda un PUNTERO a la sesion, no la sesion: el ROM hace "
     "ldr r2,[pc] y despues ldr r8,[r2], asi que la profundidad de puntero "
     "correcta es una. Tipado en el address space arm9_ov002.bss; en el "
     "espacio de codigo arm9_ov002 la misma direccion da CodeUnitInsertion"
     "Exception por memoria insuficiente, que es la separacion .bss de los "
     "overlays."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY y ninguno "
     "dejo transaccion propia abierta; el unico objeto de transaccion visible "
     "es el que el bridge abre para el script en curso. Sin errores de "
     "endTransaction."),
    ("program_saved_readback",
     "save_program devolvio Program saved successfully y el read-back "
     "posterior informa CHANGED False."),
    ("save_evidence",
     "Guardado con una llamada separada a save_program, no dentro del script "
     "que aplica los cambios, y comprobado despues con isChanged."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: ov002 queda en 244 sin nombrar. Esta funcion "
     "sale de esa cuenta al recibir nombre semantico, asi que la deuda baja; "
     "no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py no lista Ov002PanelSession, es decir no hay "
     "variantes en conflicto de ese tipo en el arbol. No se creo ningun tipo "
     "nuevo, de modo que no puede aparecer divergencia."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    ok = r.returncode == 0
    if not ok:
        fail += 1
    print("%-34s %s %s" % (field, "OK" if ok else "FAIL",
                           "" if ok else r.stdout.strip() + r.stderr.strip()))
print("failures:", fail)
