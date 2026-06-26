# Text Editor (undo/redo)

**Target time:** 45 min

## Problem
A text editor supporting insert + undo + redo using the Command pattern.

## Requirements
- apply an edit command (insert text at position)
- undo reverts last command; redo re-applies
- new edit happens after undo clears the redo stack
- (bonus) delete/replace commands, cursor

## Passing criteria
- correct insert/undo/redo
- redo cleared on new edit
- new command type without editing Editor (Command/OCP)

## Drill
Timer ON → 5-min plan → complete `// TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
