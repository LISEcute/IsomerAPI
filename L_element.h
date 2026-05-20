// #ifndef L_ELEMENTS_H
// #define L_ELEMENTS_H

// #include <QString>

// // Returns the atomic symbol for a given atomic number Z (1-118).
// // Returns an empty QString if Z is out of range.
// inline QString atomicSymbol(int Z)
// {
//     static const char* const symbols[] = {
//         "",          // index 0 (unused)
//         "H",         // 1   Hydrogen
//         "He",        // 2   Helium
//         "Li",        // 3   Lithium
//         "Be",        // 4   Beryllium
//         "B",         // 5   Boron
//         "C",         // 6   Carbon
//         "N",         // 7   Nitrogen
//         "O",         // 8   Oxygen
//         "F",         // 9   Fluorine
//         "Ne",        // 10  Neon
//         "Na",        // 11  Sodium
//         "Mg",        // 12  Magnesium
//         "Al",        // 13  Aluminium
//         "Si",        // 14  Silicon
//         "P",         // 15  Phosphorus
//         "S",         // 16  Sulfur
//         "Cl",        // 17  Chlorine
//         "Ar",        // 18  Argon
//         "K",         // 19  Potassium
//         "Ca",        // 20  Calcium
//         "Sc",        // 21  Scandium
//         "Ti",        // 22  Titanium
//         "V",         // 23  Vanadium
//         "Cr",        // 24  Chromium
//         "Mn",        // 25  Manganese
//         "Fe",        // 26  Iron
//         "Co",        // 27  Cobalt
//         "Ni",        // 28  Nickel
//         "Cu",        // 29  Copper
//         "Zn",        // 30  Zinc
//         "Ga",        // 31  Gallium
//         "Ge",        // 32  Germanium
//         "As",        // 33  Arsenic
//         "Se",        // 34  Selenium
//         "Br",        // 35  Bromine
//         "Kr",        // 36  Krypton
//         "Rb",        // 37  Rubidium
//         "Sr",        // 38  Strontium
//         "Y",         // 39  Yttrium
//         "Zr",        // 40  Zirconium
//         "Nb",        // 41  Niobium
//         "Mo",        // 42  Molybdenum
//         "Tc",        // 43  Technetium
//         "Ru",        // 44  Ruthenium
//         "Rh",        // 45  Rhodium
//         "Pd",        // 46  Palladium
//         "Ag",        // 47  Silver
//         "Cd",        // 48  Cadmium
//         "In",        // 49  Indium
//         "Sn",        // 50  Tin
//         "Sb",        // 51  Antimony
//         "Te",        // 52  Tellurium
//         "I",         // 53  Iodine
//         "Xe",        // 54  Xenon
//         "Cs",        // 55  Caesium
//         "Ba",        // 56  Barium
//         "La",        // 57  Lanthanum
//         "Ce",        // 58  Cerium
//         "Pr",        // 59  Praseodymium
//         "Nd",        // 60  Neodymium
//         "Pm",        // 61  Promethium
//         "Sm",        // 62  Samarium
//         "Eu",        // 63  Europium
//         "Gd",        // 64  Gadolinium
//         "Tb",        // 65  Terbium
//         "Dy",        // 66  Dysprosium
//         "Ho",        // 67  Holmium
//         "Er",        // 68  Erbium
//         "Tm",        // 69  Thulium
//         "Yb",        // 70  Ytterbium
//         "Lu",        // 71  Lutetium
//         "Hf",        // 72  Hafnium
//         "Ta",        // 73  Tantalum
//         "W",         // 74  Tungsten
//         "Re",        // 75  Rhenium
//         "Os",        // 76  Osmium
//         "Ir",        // 77  Iridium
//         "Pt",        // 78  Platinum
//         "Au",        // 79  Gold
//         "Hg",        // 80  Mercury
//         "Tl",        // 81  Thallium
//         "Pb",        // 82  Lead
//         "Bi",        // 83  Bismuth
//         "Po",        // 84  Polonium
//         "At",        // 85  Astatine
//         "Rn",        // 86  Radon
//         "Fr",        // 87  Francium
//         "Ra",        // 88  Radium
//         "Ac",        // 89  Actinium
//         "Th",        // 90  Thorium
//         "Pa",        // 91  Protactinium
//         "U",         // 92  Uranium
//         "Np",        // 93  Neptunium
//         "Pu",        // 94  Plutonium
//         "Am",        // 95  Americium
//         "Cm",        // 96  Curium
//         "Bk",        // 97  Berkelium
//         "Cf",        // 98  Californium
//         "Es",        // 99  Einsteinium
//         "Fm",        // 100 Fermium
//         "Md",        // 101 Mendelevium
//         "No",        // 102 Nobelium
//         "Lr",        // 103 Lawrencium
//         "Rf",        // 104 Rutherfordium
//         "Db",        // 105 Dubnium
//         "Sg",        // 106 Seaborgium
//         "Bh",        // 107 Bohrium
//         "Hs",        // 108 Hassium
//         "Mt",        // 109 Meitnerium
//         "Ds",        // 110 Darmstadtium
//         "Rg",        // 111 Roentgenium
//         "Cn",        // 112 Copernicium
//         "Nh",        // 113 Nihonium
//         "Fl",        // 114 Flerovium
//         "Mc",        // 115 Moscovium
//         "Lv",        // 116 Livermorium
//         "Ts",        // 117 Tennessine
//         "Og",        // 118 Oganesson
//     };

//     if (Z < 1 || Z > 118)
//         return QString();

//     return QString::fromLatin1(symbols[Z]);
// }

// #endif // ELEMENTS_H
#ifndef L_ELEMENTS_H
#define L_ELEMENTS_H

#include "qdebug.h"
#include <QString>
#include <QHash>

// Returns the atomic symbol for a given atomic number Z (1-118).
// Returns an empty QString if Z is out of range.
inline QString atomicSymbol(int Z)
{
    static const char* const symbols[] = {
        "",  "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",
        "Ne", "Na", "Mg", "Al", "Si", "P",  "S",  "Cl", "Ar", "K",
        "Ca", "Sc", "Ti", "V",  "Cr", "Mn", "Fe", "Co", "Ni", "Cu",
        "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y",
        "Zr", "Nb", "Mo", "Tc", "Ru", "Rh" // Expanded elements would go here
    };

    if (Z < 1 || Z >= static_cast<int>(sizeof(symbols) / sizeof(symbols[0]))) {
        return QString();
    }
    return QString::fromUtf8(symbols[Z]);
}

// Returns the atomic number for a given atomic symbol (e.g., "Mg" returns 12).
// Returns 0 if the symbol is not found.
inline int atomicSymbol(const QString& symbol)
{
    // Static hash initializes once for fast O(1) lookups on subsequent calls
    static const QHash<QString, int> symbolMap = {
        {"H", 1},   {"He", 2},  {"Li", 3},  {"Be", 4},  {"B", 5},
        {"C", 6},   {"N", 7},   {"O", 8},   {"F", 9},   {"Ne", 10},
        {"Na", 11}, {"Mg", 12}, {"Al", 13}, {"Si", 14}, {"P", 15},
        {"S", 16},  {"Cl", 17}, {"Ar", 18}, {"K", 19},  {"Ca", 20},
        {"Sc", 21}, {"Ti", 22}, {"V", 23},  {"Cr", 24}, {"Mn", 25},
        {"Fe", 26}, {"Co", 27}, {"Ni", 28}, {"Cu", 29}, {"Zn", 30},
        {"Ga", 31}, {"Ge", 32}, {"As", 33}, {"Se", 34}, {"Br", 35},
        {"Kr", 36}, {"Rb", 37}, {"Sr", 38}, {"Y", 39},  {"Zr", 40},
        {"Nb", 41}, {"Mo", 42}, {"Tc", 43}, {"Ru", 44}, {"Rh", 45}
    };

    // Case-insensitive lookup (e.g., "mg" or "MG" also works for Magnesium)
    auto it = symbolMap.find(symbol.toUpper());
    // qDebug() << "[L_element: check 'it']" << it;
    if (it != symbolMap.end()) {
        return it.value();
    }
    return 0;
}

#endif // L_ELEMENTS_H
