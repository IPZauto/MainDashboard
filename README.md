Część projektu zajamująca się opracowaniem głównego pulpitu/ekranu/dashboardu na symulator pojazdu. Dashboard zawierać będzei podstawowe zegary oraz wskaźniki a także bardziej skomplikowane systeemy adatptujące się do zmęczenia użytkownika.

## VS Code development

Open this `MainDashboard` directory as the VS Code workspace. Install the recommended extensions, CMake 3.21+, Ninja, a C++17 compiler, clangd, and Qt 6.8+ with Qt Quick, Quick Controls, WebSockets and QML development tools (`qmllint`, `qmlls`). Use a Qt kit matching your compiler. On Windows, run VS Code from an MSVC developer shell when using an MSVC Qt kit.

`CMakePresets.json` contains shared Debug, Release and QML lint presets. `CMakeUserPresets.json` contains local SDK settings and is ignored by Git. On a fresh checkout, copy `CMakeUserPresets.json.example` to `CMakeUserPresets.json`. Set `QT_ROOT_DIR` to the Qt kit directory (for example `/home/you/Qt/6.8.3/gcc_64` or `C:/Qt/6.8.3/msvc2022_64`), or replace `$env{QT_ROOT_DIR}` in the local presets with that directory. Put the kit's `bin` directory on PATH for Qt tools and Windows runtime DLLs, then restart VS Code.

From this directory:

```sh
cmake --preset local-debug
cmake --build --preset local-debug
cmake --build --preset local-lint
```

The executable is `build/local-debug/bin/ZegaryApp` (`ZegaryApp.exe` on Windows). Release builds use `local-release` for both configure and build.

In VS Code, select the `local-debug` CMake configure preset. Ctrl+Shift+B configures and builds. Run **Tasks: Run Task → Lint QML** for Qt's module-aware QML checks. F5 offers Linux/GDB and Windows/MSVC debugger configurations; select `ZegaryApp` as the CMake launch target. MinGW users can adapt the GDB configuration with their `gdb.exe` path.

clangd reads `build/local-debug/compile_commands.json` for C++ diagnostics and runs the checks in `.clang-tidy`. Configure first so that generated headers and compiler flags are available. C++ IntelliSense from the Microsoft extension is disabled to avoid duplicate diagnostics; that extension supplies the debugger. Qt's QML extension supplies QML language support; use the `qmlls` from your Qt kit. CMake generates `.qmlls.ini` files for module/build discovery. If you choose a different build preset, update clangd's compilation database path in `.vscode/settings.json`.

QML lint may report existing unqualified accesses to C++ context properties such as `backend` and `styl`. Those objects are supplied at runtime in `App/main.cpp`; this cleanup does not migrate the backend API or suppress those diagnostics.

## Project layout

- `Zegary/App/main.cpp`: application entry point and backend wiring.
- `Zegary/ZegaryContent/`: ordinary QML components and canonical dashboard images.
- `Zegary/*.cpp`, `Zegary/*.h`: existing C++ backend.
- `Zegary/config/`: bundled configuration defaults.

The application no longer requires Qt Design Studio or downloads Studio components during configuration. `GaugeArc.qml` and `GradientRectangle.qml` use standard Qt Quick Shapes to preserve the gauges and diagonal needle gradients. Existing startup values, configuration behavior and telemetry handling are unchanged.

## Research configuration

The app creates `config/config.json` beside the executable on its first run.
Edit that file, not the bundled source copy, for subsequent runs. Existing legacy
`setup` configs must be replaced with `Zegary/config/config.json`; invalid files
produce a startup error rather than silently changing the experiment.

- `debug`: enables the subdued **Settings** button at the bottom right. Default:
  `false` in the original template. Enable it in the file and restart to edit settings live.
  Open the panel with **Settings** or **Ctrl+,**.
- `mode`: `manual` holds the selected colors; `demo` plays `demoSteps` in order.
  Each step has `background`, `foreground`, and `durationMs`. `demoLoop` repeats
  the list; otherwise the final step remains displayed.
- `background` and `foreground`: target colors, strictly `#RRGGBB`. Foreground
  is shared by side-panel text and the main gauge arcs. The inner arcs and
  gradient needles retain their original colors. Both sides use the same
  colors and timing; the middle panel and status icons retain their appearance.
- `baseBackground` and `baseForeground`: colors during the pause/off phase.
- `flash`: `steady`, `fade`, or `flash`. Fade runs fade-in → hold → fade-out →
  pause. Flash switches instantly between target and base, using hold/pause.
  Steady always displays target colors.
- `fadeInMs`, `holdMs`, `fadeOutMs`, `pauseMs`: whole milliseconds, 0–3,600,000.
  Hold and pause must be positive when flashing. Zero-length fades are allowed.
  Timing/effect settings apply to every demo step; each step starts a new cycle.
- `websocketUrl`: empty for local control. Any valid `ws://` or `wss://` URL takes
  priority over manual/demo, regardless of `release`. Existing `formData` fatigue
  messages select the original presets; the configured flashing timings apply.
  A disconnected remote stays in remote mode with its last colors, rather than
  silently starting a local demo. Clear the URL to return to local control.
- The telemetry/WebSocket connection dialog opens on every startup, regardless
  of `release` or `debug`. The `release` flag is retained for future release
  behavior; it currently does not gate the dialog or remote-control priority.

**Apply** validates and previews settings without writing the file. **Save**
validates, writes atomically, and applies. Both restart the demo/flash cycle.
Closing the panel keeps applied changes; unapplied edits are discarded.
The panel also accepts the demo step list as JSON. Invalid edits leave the active
settings and saved file unchanged.

Timing follows a monotonic clock and is rendered on the application/display
schedule; millisecond values are requested durations, not a guarantee of physical
display timing. Validate display timing for the research setup.

## Deployment package (Linux / Windows)

From this directory, build a Release package for the current operating system:

```sh
cmake -DQT_ROOT=/path/to/Qt/kit -P scripts/deploy.cmake
```

You can omit `-DQT_ROOT` when `QT_ROOT_DIR` is set. Requires CMake 3.21+, Ninja,
Qt 6.8+ and a matching compiler. On Windows, run from the compiler's developer
shell (or a MinGW environment matching the Qt kit). Build on the same operating
system and architecture as the recipient; this script does not cross-compile.

The script builds in `build/deploy-release`, installs Qt/QML runtime dependencies,
and creates a timestamped folder and ZIP under `dist`. Send the whole ZIP, not
just the executable. Extract it to a writable folder and launch
`start-dashboard.sh` on Linux or `Start Dashboard.cmd` on Windows.
The editable config is `bin/config/config.json` inside the package.

Optional arguments (place before `-P`):

- `-DCONFIG_FILE=/path/to/config.json`: package your research config instead of
  the source template. Its debug flag, URLs and colors are preserved unchanged.
- `-DOUTPUT_DIR=/path/to/new-package`: choose a new output folder. Existing
  output folders/ZIPs are refused to protect saved settings.
- `-DBUILD_DIR=/path/to/build`: choose the build directory.
- `-DJOBS=4`: choose build parallelism.

Release compilation does not change the JSON `release` or `debug` flags. Linux
packages still rely on the destination's system libraries, graphics drivers and
compatible glibc; build on the oldest Linux distribution you intend to support.
