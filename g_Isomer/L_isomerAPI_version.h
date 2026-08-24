#define isomerAPI_version      "1.4.4"
#define isomerAPI_date         "24-AUG-2026"

//-----------------------------
// 1.1.110        11/10/25
// Hudson and Daniel versions

//-----------------------------
// 1.2.0          11/11/25
// project re-organization

//-----------------------------
// 1.3.0          3/20/26  Hudson
// Major updates including column
// reformatting, summary statistics,
// level scheme improvements, isotope
// hashmap storage system, etc.

//-----------------------------
// 1.3.1          5/8/26  Hudson
// Multiple views included (Isomer/Gamma solo
// and split view) but filters not visualized,
// about page created and attached to
// about button within help drop down.

//-----------------------------
// 1.3.2          5/23/26  Oleg
// Reorganized IsomerAPI as a cleaner w_Isomer Qt/SQLite module, added icon/QSS/resource support,
// improved split-database filtering/statistics/level-scheme tools, and prepared Windows deployment files.

//-----------------------------
// 1.3.3          6/8/26  Hudson
// Updates to table-view header formatting and view toggling buttons, included clickable labels in about page,
// developing file saving feature.

//-----------------------------
// 1.3.4          6/9/26  Oleg
// Main window layout update

//-----------------------------
// 1.3.5          6/10/26  Oleg
// implementation of LISE o_Element file and its support (class Celement)

//-----------------------------
// 1.3.6          6/10/26  Oleg
// cursor icons update


//-----------------------------
// 1.3.7          6/24/26  Hudson
// included updated DB from ENSDF parse as "nndc_scan_DB.sqlite", fixed arising errors from including new database,
// fixed column formatting issues withs scientific notation, fixed datatype assignment and filtering bugs,
// currently split tables (Isomers & Gammas) are not updating -- navigate to Options->View Select->Development View

//-----------------------------
// 1.3.8          6/24/26  Oleg
// squezzing DB folder, reanming


//-----------------------------
// 1.3.9          6/25/26  Hudson
// fix major bugs with filters not working, restructure filter query method, add keystroke shortcut

//-----------------------------
// 1.3.10          6/29/26  Oleg
// About dialog modifications
// MSVC config update


//-----------------------------
// 1.3.11          7/16/26  Hudson
// Updated database to all NNDC values for isotopes in original LISE++ database
// Fixed about page clickable label tool tips

//-----------------------------
// 1.3.12          7/20/26  Hudson
// Split database view is working with full filtering capabilities
// Working on dialogues/algorithm to plot only selected gammas/levels selected in the view
// Fixed escape shortcut for deselecting (takes current page, clears selection from page), and minor UI tweaks

//-----------------------------
// 1.3.13          7/23/26  Hudson
// Modifications to Isomer table filtering for more valuable information (fixed duplicates and ground states appearing)
// Modified dT12 to scientific notation to narrow column size
// Updated some UI features (header font, summary display in scientific, Isomer column order changed)


//-----------------------------
// 1.3.14          7/31/26  Hudson
// Slight UI modifications, updates to levelScheme with NNDC Dataset web access to compare plot and values in NNDC
// Updates to Level and Transition structures for better data access and handling
// Improvements to filtering and function structure (more accessible utilities)
// Calculate Transmission utility currently makes saveable .txt with organized level/transition for selected isotope under filters applied (early version)
// Known issues with some data entries (primarily 257Rf and 68Co), working to fix

//-----------------------------
// 1.3.15          8/1/26  Oleg
// Updated project file for local MinGW/MSVC install output folders
// Resolved MSVC compile error by typing selected isotope key as QPair<int,int>
// Reduced qmake/build warnings by disabling unused Qt version and DISTFILES blocks
// Compressed deployment database set by keeping nndc_DB_fullScan.sqlite and removing obsolete split/others DB files
// Rebuilt MinGW and MSVC install executables with the refreshed package layout
// Updated project-local install output paths

//-----------------------------
// 1.3.16          8/1/26  Oleg
// Typed selected isotope key handling for transmission export
// Refined main window layout and level-scheme toolbar placement
// Updated application layout and level-scheme toolbar placement

//-----------------------------
// 1.3.17          8/1/26  Oleg
// Updated main window UI layout
// Renamed cache level proxy files to o_cacheLevelProxy.cpp/.h and refreshed project references
// Kept MinGW/MSVC project version metadata synchronized

//-----------------------------
// 1.3.18          8/1/26  Oleg
// Renamed L_element.h to L_IsomerElement.h and refreshed project/header references

//-----------------------------
// 1.3.19          8/1/26  Oleg
// Added IsomerAPI block-scheme documentation as Graphviz source, PDF, and PNG files

//-----------------------------
// 1.3.20          8/10/26  Hudson
// Fixed level subscript with stylesheet for headers
// Decay algorithm created for transmission calculations with "dead end" half-lives
// Updated database with "FINAL_LEVEL_ID" for each transition, computationally increases speed significantly
// Cleaned and renamed files, managed comment documentation

//-----------------------------
// 1.3.21          8/13/26  Hudson
// Added inclusion of fast levels within filter constraints for plotting decay schemes
// Transmission information utility working for all levels within filtered results
// Included NNDC links for schemes, level wallet, etc.
// Added transition line thickness proportional to I_GAMMA

//-----------------------------
// 1.3.22          8/20/26  Hudson
// Updates to scheme-drawing architecture with new schemeKey and schemeMap structs
// vecDecayAlgo working for transmission utility and decay from levels
// Working "decay from selected level" draw schemes option
// Updates to levelScheme window to handle multiple decay scheme types (for isotope, for level decay)
// Fixes/failsafes added to transmissionCalc utility
// UI tweaks to fix formatting of tables

//-----------------------------
// 1.3.23          8/22/26  Oleg
// Decay scheme icon has been changed

//-----------------------------
// 1.3.24          8/22/26  Oleg
// Fixed filtered table display by fetching all SQL rows before proxy filtering
// Startup view now opens on the Isomers-only table with A range 40-100

//-----------------------------
// 1.3.25          8/22/26  Oleg
// Removed the unfiltered startup row fetch that could stall launch
// Kept full row fetching only after the narrowed startup/user filters are applied

//-----------------------------
// 1.3.26          8/22/26  Oleg
// Clear Filters now restores the bounded startup filter set instead of loading the full database
// Empty filter applications are guarded to prevent full-table UI fetches

//-----------------------------
// 1.3.27          8/22/26  Oleg
// Replaced duplicate-level proxy row scanning with a first-occurrence cache
// Reduced startup and filter refresh time for the bounded isomer table

//-----------------------------
// 1.3.28          8/22/26  Oleg
// Clear Filters now leaves filter cells empty and avoids loading the full database
// Cleared view is held with an empty SQL result until the user applies new filters

//-----------------------------
// 1.3.29          8/22/26  Oleg
// Drawing Options now defaults to Decays from selected level

//-----------------------------
// 1.3.30          8/22/26  Oleg
// Added qmake switch ISOMERAPI_DEBUG_TRACE to hide or show qDebug trace output

//-----------------------------
// 1.3.31          8/22/26  Oleg
// Added GLOBAL include path so clean builds compile shared utility sources
// Rebuilt all objects with qDebug trace output disabled by default

//-----------------------------
// 1.3.32          8/22/26  Oleg
// Split w_IsomerAPI.cpp into focused implementation files for drawing, filtering, and transmission logic

//-----------------------------
// 1.4.0           8/22/26  Oleg
// Promoted release version after startup/filter performance, debug-trace, build, and source-organization updates
// Added detailed Word documentation for modifications since 1.3.23

//-----------------------------
// 1.4.1           8/22/26  Oleg
// Level scheme windows are now parented to IsomerAPI and close with the main application window

//-----------------------------
// 1.4.2           8/22/26  Oleg
// Draw Scheme now always opens the plot choice dialog before plotting
// Level scheme windows remain top-level windows while owned by the main IsomerAPI window

//-----------------------------
// 1.4.3           8/23/26  Oleg
// folder w_Isomer --> g_Isomer

//-----------------------------
// 1.4.4           8/24/26  Hudson
// fixed compilation issues with stylesheet, Constant.h, and L_levelProxyModel
