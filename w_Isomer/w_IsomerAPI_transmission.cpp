#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "d_TransmissionCalc.h"
#include "L_IsomerElement.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSet>
#include <QTextStream>

#include <cmath>
#include <functional>

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void IsomerAPI::on_actionCalc_Transmission_triggered()
{
    qDebug() << "[tmssngDlg TRIGGERED]";
    transmissionDlg tmssnDlg(this);

    if (tmssnDlg.exec() == QDialog::Accepted) {
        qDebug() << "[tmssngDlg ACCEPTED]";

        // std::tie(A,Z) = tmssnDlg.getOptions();
        std::tuple<int,int,float> selIsoOpts = tmssnDlg.getOptions();

        /// Catch failed entries before running
        if (selIsoOpts == std::make_tuple(-1,-1,-1)) return;
        int Z;
        int A;
        float maxT12;
        std::tie(Z,A,maxT12) = selIsoOpts;
        std::pair<int,int> selIsoKey = {Z,A};
        qDebug() << "[actTransmission: check maxT12]" << maxT12;

        if (!filteredIsotopes.contains(selIsoKey)) {
            int Z;
            int A;
            std::tie(Z, A) = selIsoKey;

            QString isotopeName = atomicSymbol(Z).isEmpty()
                                      ? tr("A=%1, Z=%2").arg(A).arg(Z)
                                      : QString::number(A) + atomicSymbol(Z);

            QMessageBox::warning(
                this,
                tr("No filtered isotope"),
                tr("%1 is not available in the current filtered results. "
                   "Adjust the filters or choose an isotope that is listed.")
                    .arg(isotopeName));
            return;
        }

        writeDecayTXT(selIsoKey, maxT12);
    }

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::writeDecayTXT(QPair<int, int> isoKey, float maxT12){
    qDebug() << "[writeDecayTXT for A,Z]" << isoKey;
    Isotope iso = filteredIsotopes.value(isoKey);
    int Z;
    int A;
    std::tie(Z,A) = isoKey;
    QString symbol = atomicSymbol(Z);
    QString AStr = QString::number(A);

    qDebug() << "[writeDecayTXT: symbol]" << symbol << Z;

    // ------------------------------------------

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Text File"), AStr + symbol + "_decay_data",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    QMap<int, Level> lvlMap;

    for (Level &lvl : iso.levels) {
        lvlMap[lvl.lvlID] = lvl;
    }
    lvlMap.insert(iso.groundState.lvlID,iso.groundState);
    qDebug() << "[writeDecayTXT lvlIDs]" << lvlMap.keys() << lvlMap.count();


    /// If user decides to save the file
    if (!fileName.isEmpty()) {
        QFile textFile(fileName);

        for (Level &lvl : iso.levels) {
            lvlMap[lvl.lvlID] = lvl;
        }



        QVector<Level> storeDecays;

        if (textFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "[writeDecayTXT: start writing!]";
            QTextStream out(&textFile);
            out << "#Isotope: " + AStr + symbol << "\n";
            out << "#Level Format (LVL): E_LVL;dE_LVL;IT_RATIO;T12;dT12;JPI\n";
            out << "#Gamma Format (GAM): E_GAM;dE_GAM;E_LVL;dE_LVL;JPI;I_GAM;M_GAM\n\n";
            // out << "entry;E_GAM;dE_GAM;E_LVL;dE_LVL;JPI;I_GAM;M_GAM";


            // -----------------------------------------------------------------------------------

            for (Level &lvl : iso.levels) {
                qDebug() << "[writeDecayTXT: call decayAlgo for level]" << lvl.lvlEnergy << lvl.lvlID;
                Level decay = vecDecayAlgo(&lvl, lvlMap, maxT12, true).first();
                storeDecays.append(decay);
                // qDebug() << "[writeDecayTXT: Check decay size]" << decay.lvlEnergy << decay.lvlID << decay.transitions.count();
            }



            for (Level &lvl : storeDecays) {

                /// Level Format (LVL): E_LVL;dE_LVL;IT_RATIO;T12;dT12;JPI
                out <<"LVL"<<";"<< lvl.lvlEnergy<<";"<<lvl.dlvlEnergy<<";"<<lvl.IT<<
                    ";"<<lvl.halfLife<<";"<<lvl.dhalfLife<<";"<<lvl.spin<<"\n";
                for (Transition &tr : lvl.transitions) {

                    /// Gamma Format (GAM): E_GAM;dE_GAM;E_LVL;dE_LVL;JPI;I_GAM;M_GAM
                    out << "GAM"<<";"<<tr.gamEnergy<<";"<<tr.dgamEnergy<<
                        ";"<<tr.lvlEnergy<<";"<<tr.dlvlEnergy<<
                        ";"<<lvl.spin<<";"<<tr.IGam<<";"<<tr.MGam<<"\n";
                }
                out << "\n";
            }

            textFile.close();
        }
    }
}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVector<Level> IsomerAPI::vecDecayAlgo(
    Level *selLvl,
    QMap<int, Level> lvlMap,
    double T12_deadEnd,
    bool transBool)
{
    qDebug() << "[vecDecayAlgo]"
             << "E:" << selLvl->lvlEnergy
             << "ID:" << selLvl->lvlID
             << "trCount:" << selLvl->transitions.count();

    if (!transBool) {
        QVector<Level> plottedLevels;
        QSet<int> visitedLevelIds;

        std::function<void(const Level &, bool)> collectLevel;

        collectLevel = [&](const Level &currentLevel, bool followTransitions) {
            // Ground state is drawn separately by graphicsView.
            if (currentLevel.lvlEnergy == 0.0) {
                return;
            }

            if (visitedLevelIds.contains(currentLevel.lvlID)) {
                return;
            }
            visitedLevelIds.insert(currentLevel.lvlID);

            Level plottedLevel = currentLevel;
            plottedLevel.transitions.clear();

            const int plottedIndex = plottedLevels.size();
            plottedLevels.append(plottedLevel);

            if (!followTransitions) {
                return;
            }

            for (const Transition &transition : currentLevel.transitions) {
                if (!lvlMap.contains(transition.finID)) {
                    qWarning() << "Missing FINAL_LEVEL_ID:"
                               << transition.finID
                               << "for GAMMA_ID:" << transition.trID;
                    continue;
                }

                plottedLevels[plottedIndex].transitions.append(transition);

                const Level finalLevel = lvlMap.value(transition.finID);
                const bool isGroundState = finalLevel.lvlEnergy == 0.0;
                const bool isDeadEnd =
                    finalLevel.halfLife >= T12_deadEnd;

                if (!isGroundState) {
                    // Add every visible final level as a plotted line.
                    // Only expand its outgoing transitions if it is not a dead end.
                    collectLevel(finalLevel, !isDeadEnd);
                }
            }
        };

        collectLevel(*selLvl, true);
        return plottedLevels;
    } else {

        Level tmpLevel = *selLvl;
        tmpLevel.transitions.clear();

        QVector<Level> lvlVec;

        for (const Transition &tr : selLvl->transitions) {

            // qDebug() << "[vecDecayAlgo: transition]"
            //          << tr.gamEnergy << tr.trID;

            Level &finLvl = lvlMap[tr.finID];

            bool escape =
                (finLvl.halfLife >= T12_deadEnd) ||
                (finLvl.lvlEnergy == 0.0);

            // Always preserve this transition
            tmpLevel.transitions.append(tr);

            // qDebug() << "[vecDecayAlgo: finLvl]"
            //          << finLvl.lvlEnergy
            //          << finLvl.lvlID
            //          << "escape:" << escape;

            if (escape) {
                if (!transBool) {lvlVec.append(finLvl);}
                continue;
            }

            QVector<Level> child =
                vecDecayAlgo(&finLvl,lvlMap,T12_deadEnd,transBool);

            if (transBool) {tmpLevel.transitions.append(
                    child.first().transitions);
            } else { lvlVec.append(child);}
        }

        if (transBool) lvlVec.append(tmpLevel);


        qDebug() << "[vecDecayAlgo: check lvlVec size]" << lvlVec.size();
        return lvlVec;
    }


}

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

