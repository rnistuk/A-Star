A-Star — CLAUDE.md
============================

An interactive A* pathfinding visualization built on SDL2. You draw obstacles on a
node grid and watch the algorithm search and settle on an optimal path in real time.
Based on OneLoneCoder's A* tutorial — a learning project for graph search, heuristics,
and rendering a live algorithm with SDL2.

Project Structure
-----------------

*   `a-star/` — the application. `main.cpp` is the entry point (SDL event loop,
    rendering, input handling); `src/Node.{h,cpp}` and `src/Graph.{h,cpp}` hold the
    grid model and the A* search itself. Start in `main.cpp`, then read `Graph`.
*   `a-star/CMakeLists.txt` — defines the `a-star` executable and links SDL2.
*   `CMakeLists.txt` (root) — finds SDL2 via pkg-config and adds the `a-star` subdir.
*   `res/` — screenshots used by the README (not loaded at runtime).
*   `cmake-build-debug/` — CLion's generated build dir (not source).

Environment
-----------

*   IDE: CLion
*   Language: C++17
*   Build system: CMake 3.15+
*   Key dependencies: SDL2 (found via pkg-config — `brew install sdl2` on macOS).
    Tested on macOS (Catalina 10.15.4+).

Building and Testing
--------------------

```
mkdir build && cd build
cmake ..
make
./a-star/a-star
```

Controls: click a node to add an obstacle, Shift+Click to move the start, Ctrl+Click
to move the end.

No automated tests yet — verification is visual (run it and confirm the path renders
and re-routes around obstacles).

Conventions
-----------

*   TDD — write failing tests first, then minimum code to pass
*   No comments unless the why is non-obvious
*   No speculative code — only implement what is needed right now
*   Commit messages: short, descriptive, imperative tense ("add Beer-Lambert attenuation" not "added" or "adding")
*   C++17, `#include`-what-you-use; keep SDL specifics in `main.cpp`, keep the search
    logic in `Graph`/`Node` so the algorithm stays testable independent of rendering
*   No test framework is wired up yet — adding one (GoogleTest via CMake) is the first
    step if behaviour needs locking down

Current State
-------------

### Completed

*   Interactive grid visualization with clickable obstacles
*   Adjustable start/end positions (Shift+Click / Ctrl+Click)
*   A* search with visual feedback for searched nodes and final path
*   Graceful handling of unreachable destinations
*   **SOLID refactor — model decoupled from SDL.** DONE, builds clean, visually verified.
    `Node` is a pure data struct; `Graph` holds no SDL (only the search). All pixel
    geometry lives in `src/GridLayout.h` (`to_pos`, `center`, `node_contains_point`); all
    SDL drawing lives in `src/GraphRenderer.{h,cpp}` (`draw` orchestrates
    `draw_connections`/`draw_nodes`/`draw_path`, plus the `node_at` hit-test). `main.cpp`
    owns a `GraphRenderer graph_renderer`. Node colours come from a `node_colors`
    `unordered_map` in an anonymous namespace; connection and path lines now share
    `GridLayout::center`, fixing the old ~`node_border/2` px centring mismatch. This
    unblocks testing `solve_astar` without a renderer.

### In Progress

*   None — ready to start the test framework (see Next).

### Next

*   Wire up GoogleTest via CMake and cover `Graph::solve_astar` independent of SDL —
    open/closed sets, heuristic, and the unreachable case. First failing test first (TDD).
*   Document SDL2 install per-platform (macOS done; Linux `apt` not yet)

### Decisions Pending

*   None

Do Not Touch
------------

*   Nothing off limits at this time.

Pair Programming
----------------

*   Driver writes all code — navigator (Claude) does not write code unless explicitly asked
*   Navigator provides: direction, design decisions, code review, and course corrections
*   One step at a time — navigator waits for driver to confirm before moving to the next
*   Navigator confirms tests pass before suggesting the next step
*   Navigation is terse — no lengthy explanations unless explicitly asked
*   If navigator disagrees with an approach, say so once then follow the driver's lead

Karpathy Rules
--------------

All rules apply to every task unless explicitly overridden.

### Rule 1 — Think Before Coding

State assumptions explicitly. If uncertain, ask rather than guess. Present multiple interpretations when ambiguity exists. Push back when a simpler approach exists. Stop when confused. Name what's unclear.

### Rule 2 — Simplicity First

Minimum code that solves the problem. Nothing speculative. No features beyond what was asked. No abstractions for single-use code. Test: would a senior engineer say this is overcomplicated? If yes, simplify.

### Rule 3 — Surgical Changes

The driver should touch only what is necessary to make the current test pass. Don't "improve" adjacent code, comments, or formatting. Don't refactor what isn't broken. Match existing style. Navigator warns the driver if this rule is being broken.

### Rule 4 — Agree on Done Before Starting

Before implementing anything, both driver and navigator should agree on what done looks like. A failing test is the preferred success criterion. Don't start until done is defined.

### Rule 5 — Dropped

Original rule was written for agentic coding and does not apply to this pair programming model.

### Rule 6 — Know When to Stop

If the session is getting long or context feels stale, checkpoint before continuing. Summarise what's done, what's verified, what's next. Update CLAUDE.md to reflect current state, then commit before ending the session. A fresh session with good context beats a stale one with accumulated confusion.

### Rule 7 — Surface Conflicts, Don't Average Them

If two patterns contradict, pick one (more recent / more tested). Explain why. Flag the other for cleanup. Don't blend conflicting patterns.

### Rule 8 — Read Before You Write

Before adding code, read exports, immediate callers, shared utilities. "Looks orthogonal" is dangerous. If unsure why code is structured a way, ask.

### Rule 9 — Test Behaviours, Not Functionality

Tests verify what the code does from the outside, not how it does it internally. Tests must encode WHY the behaviour matters, not just WHAT it does. A test that can't fail when business logic changes is wrong.

### Rule 10 — Checkpoint After Every Significant Step

Summarize what was done, what's verified, what's left. Don't continue from a state you can't describe back. If you lose track, stop and restate.

### Rule 11 — Match the Codebase's Conventions, Even If You Disagree

Conformance > taste inside the codebase. If you genuinely think a convention is harmful, surface it. Don't fork silently.

### Rule 12 — Fail Loud

"Completed" is wrong if anything was skipped silently. "Tests pass" is wrong if any were skipped. Default to surfacing uncertainty, not hiding it.
