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

// struct Level {
//     // QString AZ;
//     double lvlEnergy;
//     QString spin;
//     QString halfLife;
// };


#endif // VECTORSTRUCTURES_H

