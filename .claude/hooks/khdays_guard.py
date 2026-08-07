#!/usr/bin/env python3
"""Claude Code hooks that enforce the khdays active-function lock."""
from __future__ import annotations

import json
import os
import re
import sys
from pathlib import Path
from typing import Any

FUNC_TOKEN_RE = re.compile(r"func_(?:ov\d{3}_)?[0-9a-fA-F]{8}")
MUTATING_BASH_RE = re.compile(
    r"(?:\bsed\s+-i\b|\bperl\s+-pi\b|\bmv\b|\bcp\b|\brm\b|\bdel\b|\bmove\b|"
    r"\bcopy\b|\btouch\b|\bgit\s+add\b|\bcat\s*<<|>>|(?<![<])>(?![>]))",
    re.IGNORECASE,
)


def root_from_input(data: dict[str, Any]) -> Path:
    raw = data.get("cwd") or os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
    return Path(raw).resolve()


def active_state(root: Path) -> dict[str, Any] | None:
    path = root / "build" / "active_function.json"
    if not path.exists():
        return None
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception:
        return {"function": "UNKNOWN", "state_error": True}


def block_stop(reason: str) -> int:
    print(json.dumps({"decision": "block", "reason": reason}, ensure_ascii=False))
    return 0


def deny_tool(reason: str) -> int:
    print(json.dumps({
        "hookSpecificOutput": {
            "hookEventName": "PreToolUse",
            "permissionDecision": "deny",
            "permissionDecisionReason": reason,
        }
    }, ensure_ascii=False))
    return 0


def session_context(active: dict[str, Any]) -> int:
    function = active.get("function", "UNKNOWN")
    candidate = active.get("candidate", "unknown")
    diff = active.get("current_diff", "unknown")
    print(
        "KHDAYS ACTIVE-FUNCTION LOCK: "
        f"{function}; candidate={candidate}; current_diff={diff}. "
        "Do not select or edit another function. Run "
        "`python .claude/hooks/khdays_control.py status` before work."
    )
    return 0


def handle_stop(data: dict[str, Any], active: dict[str, Any]) -> int:
    # A Stop hook continuation triggers Stop again. Allow that second stop so
    # Claude Code does not hit its eight-block safety cap. With /loop, the next
    # scheduled turn will recover the same active-function lock.
    if data.get("stop_hook_active") is True:
        return 0
    function = active.get("function", "UNKNOWN")
    candidate = active.get("candidate", "unknown")
    diff = active.get("current_diff", "unknown")
    return block_stop(
        f"Active function {function} is incomplete. Continue only this function. "
        f"Candidate: {candidate}. Current residue: {diff}. "
        "The turn may end only after `python .claude/hooks/khdays_control.py complete` returns 0."
    )


def normalized_path(raw: str) -> str:
    return raw.replace("\\", "/").lower()


def handle_pretool(data: dict[str, Any], active: dict[str, Any], root: Path) -> int:
    tool = str(data.get("tool_name", ""))
    inp = data.get("tool_input") or {}
    function = str(active.get("function", "")).lower()
    if not function:
        return 0

    if tool in {"Edit", "Write", "MultiEdit", "NotebookEdit"}:
        raw_path = str(inp.get("file_path") or inp.get("path") or "")
        path = normalized_path(raw_path)
        if path.endswith("build/active_function.json") or "/semantic_receipts/" in path or "/match_receipts/" in path:
            return deny_tool("State and receipt JSON files may only be changed through khdays_control.py.")
        tokens = {t.lower() for t in FUNC_TOKEN_RE.findall(path)}
        foreign = sorted(t for t in tokens if t != function)
        if foreign:
            return deny_tool(
                f"Active lock is {function}; editing another function is forbidden: {', '.join(foreign)}"
            )
        if function in path and any(x in path for x in ("/nonmatching/", "/blocked/", "/deferred/")):
            return deny_tool(f"{function} cannot be moved or written to nonmatching/blocked/deferred.")
        return 0

    if tool in {"Bash", "PowerShell"}:
        command = str(inp.get("command", ""))
        lower = command.lower().replace("\\", "/")
        if "khdays_control.py" in lower:
            return 0
        if "active_function.json" in lower and re.search(r"\b(rm|del|erase|unlink|move|mv)\b", lower):
            return deny_tool("The active-function lock may only be removed by khdays_control.py complete.")
        if function in lower and any(x in lower for x in ("nonmatching/", "blocked/", "deferred/")):
            if MUTATING_BASH_RE.search(command):
                return deny_tool(f"{function} cannot be parked, blocked, deferred, copied, or moved away.")
        if MUTATING_BASH_RE.search(command):
            tokens = {t.lower() for t in FUNC_TOKEN_RE.findall(command)}
            foreign = sorted(t for t in tokens if t != function)
            if foreign:
                return deny_tool(
                    f"Active lock is {function}; mutating another function is forbidden: {', '.join(foreign)}"
                )
    return 0


def main() -> int:
    try:
        data = json.load(sys.stdin)
    except Exception:
        return 0
    root = root_from_input(data)
    active = active_state(root)
    event = str(data.get("hook_event_name", ""))
    if active is None:
        return 0
    if active.get("state_error"):
        return deny_tool("build/active_function.json is invalid JSON; repair it before continuing.") if event == "PreToolUse" else block_stop("build/active_function.json is invalid JSON; repair it before continuing.")
    if event == "SessionStart":
        return session_context(active)
    if event == "Stop":
        return handle_stop(data, active)
    if event == "PreToolUse":
        return handle_pretool(data, active, root)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
