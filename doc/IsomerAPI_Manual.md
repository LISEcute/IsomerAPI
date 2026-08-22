# IsomerAPI Manual

This manual explains how to run, build, use, and modify the current IsomerAPI codebase.

IsomerAPI is a Qt Widgets application for browsing isomer level and gamma transition data from an SQLite database. It is designed as a mostly self-contained module that can later be integrated with LISE++.

## Quick Start

### Run an Existing Build

The packaged executables are in:

- MinGW build: `_install/IsomerAPI.exe`
- MSVC build: `_install_MSVC/IsomerAPI.exe`

Run the executable from its install directory so it can find the database:

```powershell
cd C:\Users\taras\Documents\Codex\IsomerAPI\_install
.\IsomerAPI.exe
```

The required runtime database is:

```text
_install/lisecfg/nndc_DB_fullScan.sqlite
```

The application looks for this file relative to `QCoreApplication::applicationDirPath()`, so the deployed folder must keep the `lisecfg` subfolder beside the executable.

### Build in Qt Creator

Open:

```text
IsomerAPI.pro
```

Recommended environment:

- Qt Creator 16 or newer
- Qt 6.7.x
- MinGW 64-bit or MSVC 2019 64-bit kit

The project file sends build output to:

```text
_install       for win32-g++
_install_MSVC  for win32-msvc
```

### Build from PowerShell with MinGW

Adjust paths if your Qt installation is different:

```powershell
cd C:\Users\taras\Documents\Codex\IsomerAPI\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release
$env:Path = 'C:\Qt\6.7.0\mingw_64\bin;C:\Qt\Tools\mingw1120_64\bin;' + $env:Path
& 'C:\Qt\6.7.0\mingw_64\bin\qmake.exe' -o Makefile ..\..\IsomerAPI.pro -spec win32-g++ 'CONFIG+=qtquickcompiler' 'CONFIG+=release'
& 'C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe' -f Makefile.Release
```

### Deployment Notes

The deployment scripts are:

- `_install/deploy.bat`
- `_install_MSVC/deploy_MSVC.bat`

They call `windeployqt`. Check the `APPDIR` and `WDEP` variables before use; the scripts may need local path edits if Qt or the install directory moved.

## User Interface

When the program starts, it opens on the isomers-only page with default filters:

- `T1/2`: `0.1` to `10` microseconds
- `A_IT`: `50` to `80`
- `LEVEL`: `0` to `4000` keV

The main window has four table views:

- `Gammas`: gamma transition rows only
- `Isomers`: isomer level rows only
- `Isomers / Gammas`: split view with both isomer and gamma tables
- `Development View`: full model table for debugging/development

Use the view buttons or `Options -> View Select` to switch between them.

## Filtering Data

Filters are grouped in the right-side filter panel.

Supported filter inputs:

- Gamma energy range, in keV
- Level energy range, in keV
- Half-life range, in microseconds
- Source
- Mass number `A_IT`, exact or range
- Proton number `Z_IT`, exact or range

For `Z_IT`, the code accepts either a number or an element symbol. For example, both `26` and `Fe` can be used.

Buttons and shortcuts:

- `Apply Filters` or `Enter`: apply current filters
- `Clear Filters` or `C`: clear filters and refresh tables
- `Draw Scheme` or `D`: open level-scheme plotting
- `Esc`: clear table selection on the current page

The source filter supports:

- `All Sources`
- A single source selected from the combo box
- Semicolon-separated source entries, using the `Semicolon;List;Sources` pattern

Internally, `applyFilters()` builds an SQL filter expression and applies it to `modelFull`, then calls `prepData()` and `statRefresh()`.

## Summary Statistics

The summary panel is recalculated after filters are applied. It displays:

- Count of distinct isomer levels
- Count of isotopes in the prepared isotope map
- Minimum and maximum gamma energy
- Minimum and maximum half-life

These values come from SQL queries that are combined with the active table filter.

## Level-Scheme Plotting

Click `Draw Scheme` or press `D`.

If no row is selected, the program plots all filtered isotopes. If rows are selected, a drawing-options dialog appears. The currently implemented plotting path is the filtered-results option.

The level-scheme window provides:

- A graphics view of the selected isotope
- A menu of other filtered isotopes
- NNDC record links for the current isotope
- NNDC scheme links

The plotting code is split between:

- `w_schemeWindow.cpp`: window, isotope selection, NNDC links
- `w_schemeGraphic.cpp`: level and transition drawing

Transition line thickness is proportional to `I_GAMMA`.

## Transmission Export

Use:

```text
Calculate -> Isomer Transmission
```

The dialog asks for `A` and `Z`.

- `A` is the mass number.
- `Z` can be a proton number or an element symbol.

The selected isotope must exist in the currently filtered results. The export path is handled by:

```text
IsomerAPI::writeDecayTXT()
IsomerAPI::decayAlgo()
```

The saved text file uses semicolon-separated records:

```text
#Level Format (LVL): E_LVL;dE_LVL;IT_RATIO;T12;dT12;JPI
#Gamma Format (GAM): E_GAM;dE_GAM;E_LVL;dE_LVL;JPI;I_GAM;M_GAM
```

`decayAlgo()` follows transitions through fast levels until it reaches a dead-end level, currently controlled by the half-life threshold passed from `writeDecayTXT()`.

## Main Code Map

### Project Root

- `IsomerAPI.pro`: qmake project file, source/header/form lists, install output paths, version metadata for Windows
- `README.md`: short project summary
- `doc/`: documentation, intro slides, block-scheme files, this manual
- `_install/`: MinGW deployment folder
- `_install_MSVC/`: MSVC deployment folder

### Main Window

- `w_Isomer/w_IsomerAPI.ui`: main Qt Designer form
- `w_Isomer/w_IsomerAPI.h`
- `w_Isomer/w_IsomerAPI.cpp`

Important functions:

- Constructor: database setup, model/proxy setup, headers, defaults, shortcuts, signals
- `applyFilters()`: builds and applies SQL filters
- `sourceFilter()`: handles source selection
- `prepData()`: converts SQL rows into `Isotope`, `Level`, and `Transition` structs
- `statRefresh()`: updates summary fields
- `openDrawing()`: launches level-scheme plotting
- `writeDecayTXT()`: exports transmission/decay information
- `decayAlgo()`: recursively/iteratively prepares decay paths through fast levels

### Data Structures

- `w_Isomer/L_isoStructs.h`

Main structs:

- `Transition`: gamma energy, intensity, multipolarity, IDs, final level ID
- `Level`: level energy, spin, half-life, IT ratio, transitions, level ID
- `Isotope`: `A`, `Z`, levels, ground state

### Proxy Models

- `w_Isomer/L_levelProxyModel.h`: keeps first row per `LEVEL_ID`, with `T12 >= 0.01` and `LEVEL > 0`
- `w_Isomer/L_gammaProxyModel.h`: keeps rows with gamma energy
- `w_Isomer/o_cacheLevelProxy.*`: cache proxy helper, currently not active in the main model path

### Dialogs

- `d_DownloadFiles.*`: save/download dialog path
- `d_DrawingOptions.*`: drawing option selector
- `d_TransmissionCalc.*`: isotope selector for transmission export
- `d_ColumnsOptions.*`: column options dialog code
- `w_aboutIsomerAPI.*`: about dialog

### Level-Scheme Drawing

- `w_schemeWindow.*`: level-scheme window, isotope menu, NNDC links
- `w_schemeGraphic.*`: custom `QGraphicsItem` painter for levels and transitions

### Element Helpers

- `L_IsomerElement.h`: atomic number/symbol conversion helpers

## Database Expectations

The application expects an SQLite table named:

```text
Isomers
```

Important columns used by the code:

- `A_IT`
- `Z_IT`
- `LEVEL`
- `D_LEVEL`
- `JPI`
- `T12`
- `D_T12`
- `IT_RATIO`
- `E_GAMMA`
- `D_EG`
- `I_GAMMA`
- `D_IG`
- `M_GAMMA`
- `SOURCE`
- `LEVEL_ID`
- `GAMMA_ID`
- `FINAL_LEVEL_ID`

`FINAL_LEVEL_ID` is used by the transmission decay algorithm.

## Version Updates

Update both locations when making a release:

```text
IsomerAPI.pro
w_Isomer/L_isomerAPI_version.h
```

`IsomerAPI.pro` controls Windows executable metadata through `VERSION`. `L_isomerAPI_version.h` controls the visible version string in the About dialog and stores the changelog.

## Known Development Notes

- `Save As...` currently opens the download dialog and writes placeholder text; it is not a full table export yet.
- `Plot Selection (WIP)` and selected-level/selected-gamma drawing paths are not fully implemented.
- `LevelProxyModel` scans previous rows to suppress duplicate `LEVEL_ID` entries; this is simple but may become slow on very large filtered result sets.
- Many debug messages still use `qDebug()`. This is useful during development but noisy in console builds.
- The deployed database must stay beside the executable under `lisecfg/`.

## Related Documentation

- `doc/isomerapi-block-scheme.pdf`
- `doc/isomerapi-block-scheme.png`
- `doc/isomerapi-block-scheme.dot`
- `doc/Codex_Intro_for_IsomerAPI.pdf`
- `doc/Codex_Intro_for_IsomerAPI.pptx`
