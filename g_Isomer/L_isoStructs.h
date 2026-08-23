#ifndef VECTORSTRUCTURES_H
#define VECTORSTRUCTURES_H

#include <QString>
#include <QVector>
#include <QHash>
#include <QPair>


// struct Level {
//     // QString AZ;
//     double lvlEnergy;
//     QString spin;
//     QString halfLife;
//     QVector<Transition> transitions;
// };


struct Transition {
    // QString AZ;
    double lvlEnergy;
    QString dlvlEnergy;
    double gamEnergy;
    QString dgamEnergy;
    double IGam;
    QString MGam;

    QString label;
    int trID;
    int finID;
};


struct Level {
    // QString AZ;
    double lvlEnergy;
    QString dlvlEnergy;
    QString spin;
    double halfLife;
    QString dhalfLife;
    double IT;

    QVector<Transition> transitions;

    int lvlID;
};

struct Isotope {
    int A;
    int Z;
    QVector<Level> levels;
    Level groundState;

};



enum class SchemeType {
    FilteredIsotope,
    DecayFromLevel,
    GammaCoincidence
};

struct SchemeKey {
    int Z;
    int A;
    SchemeType type;
    int anchorId;  // LEVEL_ID for DecayFromLevel; GAMMA_ID for GammaCoincidence

    bool operator<(const SchemeKey &other) const {
        if (Z != other.Z) return Z < other.Z;
        if (A != other.A) return A < other.A;
        if (type != other.type) return type < other.type;
        return anchorId < other.anchorId;
    };
};

using SchemeMap = QMap<SchemeKey, Isotope>;

// struct Level {
//     // QString AZ;
//     double lvlEnergy;
//     QString spin;
//     QString halfLife;
// };


#endif // VECTORSTRUCTURES_H

