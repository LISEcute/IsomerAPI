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
    double emission;
    QString label;
};


struct Level {
    // QString AZ;
    double lvlEnergy;
    QString spin;
    double halfLife;
    QVector<Transition> transitions;
};

struct Isotope {
    int A;
    int Z;
    QVector<Level> levels;
};

// struct Level {
//     // QString AZ;
//     double lvlEnergy;
//     QString spin;
//     QString halfLife;
// };


#endif // VECTORSTRUCTURES_H

