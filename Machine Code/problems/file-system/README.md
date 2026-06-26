# In-memory File System

**Target time:** 60 min

## Problem
An in-memory file system: mkdir, addContentToFile, readContentFromFile, ls.

## Requirements
- mkdir(path) creates nested dirs
- addContentToFile(path, content) creates/append file
- readContentFromFile(path) returns content
- ls(path) lists dir entries sorted (or filename if file)

## Passing criteria
- nested mkdir works
- ls sorts entries
- read returns appended content

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
