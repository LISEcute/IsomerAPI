#include "w_IsomerAPI.h"
#include "ui_w_IsomerAPI.h"

#include "L_IsomerElement.h"

#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QSqlError>

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void IsomerAPI::statRefresh()
{
  qDebug();

  // queryStr = "SELECT COUNT(DISTINCT LEVEL_ID) FROM Isomers WHERE T12 >= 0.01 AND LEVEL != 0";
  // QVariant isomCount = queryModel(queryStr);
  int isomCount = levelProxy->rowCount();

  queryStr = "SELECT MIN(E_GAMMA) FROM Isomers";
  QVariant minGamma = queryModel(queryStr);

  queryStr = "SELECT MAX(E_GAMMA) FROM Isomers";
  QVariant maxGamma = queryModel(queryStr);

  queryStr = "SELECT MIN(T12) FROM Isomers WHERE LEVEL != 0 AND T12 >= 0.01";
  QVariant minT12 = queryModel(queryStr);

  queryStr = "SELECT MAX(T12) FROM Isomers WHERE LEVEL != 0 AND T12 >= 0.01";
  QVariant maxT12 = queryModel(queryStr);


  ui->le_isomerCounts->setText(QString::number(isomCount));
  ui->le_isotopeCounts->setText(QString::number(filteredIsotopes.size()));

  ui->le_lowGammaSum->setText(minGamma.toString());
  ui->le_highGammaSum->setText(maxGamma.toString());

  ui->le_lowT12Sum->setText(QString::number(minT12.toFloat(), 'g', 4));
  ui->le_highT12Sum->setText(QString::number(maxT12.toFloat(), 'g', 4));

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QVariant IsomerAPI::queryModel(const QString &queryRequest)
{
  QString fullQuery = queryRequest;
  QString filter = modelFull->filter(); // ``` model full attempt
  // qDebug() << "[queryModel FILTER VALUE]" << filter;
  if (!filter.isEmpty()) {
      if (fullQuery.contains("WHERE", Qt::CaseInsensitive))
          fullQuery += " AND " + filter;
      else
          fullQuery += " WHERE " + filter;
      // qDebug() << "[queryModel: TRIGGERED empty query]";
    }
  if (query.exec(fullQuery) && query.next()) {
      qDebug() << "[queryModel: exec, fullQuery value]" << fullQuery;
      qDebug() << "[queryModel -- query value]" << query.value(0);
      qDebug();
      return {query.value(0)};
  } else {
      qDebug() << "[queryModel: NO EXECUTION]" << query.lastError().text();
      qDebug() << "[queryModel: BROKEN REQUEST]" << fullQuery << "\n";
  }
  return {};
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::sourceFilter()
{
  // empty entry safety net
  if (ui->cb_sourceFilter->currentText() == "") ui->cb_sourceFilter->setCurrentText("All Sources");

  QString text = ui->cb_sourceFilter->currentText();
  qDebug() << "[sourceFilter l70 TEXT]: " << text;
  QStringList reqSources = text.split(';', Qt::SkipEmptyParts);

  bool validSearch = std::any_of(reqSources.begin(), reqSources.end(), [&](QString item) {
      qDebug() << "[sourceFilter: check item]" << item;
      return entrySources.contains(item);
  });

  qDebug() << "[sourceFilter: available entrySources]" << entrySources;

  if (reqSources.contains("All Sources")) {
      modelFull -> setFilter("");
      qDebug() << "[sourceFilter: All sources triggered - clear filters]";
  } else if (!validSearch) {
      QMessageBox::critical(this,"Error!","Check the source entry is a possible source!");
      qDebug() << "[sourceFilter: INVALID SEARCH]" << reqSources;
  } else {
      QStringList quoted;
      for (const QString &src : reqSources) {
          quoted.append("'" + src + "'");

      }
      modelFull->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
      qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
      qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
  }

  /// DEPRECATED WITH PROXY MODEL METHOD
  // for (auto &model : modelsVector) {

  //     if (reqSources.contains("All Sources")) {
  //         model -> setFilter("");
  //         qDebug() << "[sourceFilter: All sources triggered - clear filters]";
  //     } else if (!validSearch) {
  //         QMessageBox::critical(this,"Error!","Check the source entry is a possible source!");
  //         qDebug() << "[sourceFilter: INVALID SEARCH]" << reqSources;
  //     } else {
  //         QStringList quoted;
  //         for (const QString &src : reqSources) {
  //             quoted.append("'" + src + "'");

  //         }
  //         model->setFilter(QString("SOURCE IN (%1)").arg(quoted.join(',')));
  //         qDebug() << "[sourceFilter l77: NO ALL SOURCES]: " << quoted;
  //         qDebug() << "[sourceFilter l78: Check format for SQL]: " << quoted.join(',');
  //     }

  // }
  qDebug() << "\n";

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::applyFilters()
{
    // cacheLevel->rebuild// cache();
    // bool rowSelected = ui->tableView_Dev->selectionModel()->hasSelection();
    // qDebug() << "[applyFilters: OLD FILTER VALUE?]" << modelFull->filter();
    // if (rowSelected){
    //   qDebug() << "[applyFilters: SELECTION DETECTED]" << rowSelected;
    // } else {qDebug() << "[applyFilters: SELECTION SKIPPED]" << rowSelected;}

  sourceFilter();

  // qDebug() << "[sourceFILTER PATH CHECK]" << QDir::current() << QDir::currentPath();
  // qDebug() << "[applyFilters: OLD FILTER VALUE?]" << modelFull->filter();

  QStringList conditions;
  QStringList isoConditions;

  const QString sourceExpr = modelFull->filter();
  if (!sourceExpr.isEmpty()) {
      conditions.append(QString("(%1)").arg(sourceExpr));
  }

  auto appendRangeCondition = [&conditions](const QString &column,
                                            QLineEdit *lowEdit,
                                            QLineEdit *highEdit,
                                            bool allowNull = false) {
      if (!lowEdit->text().isEmpty()) {
          QString condition = QString("%1 >= %2").arg(column, lowEdit->text());
          if (allowNull) {
              condition = QString("(%1 OR %2 IS NULL)").arg(condition, column);
          }
          conditions.append(condition);
      }

      if (!highEdit->text().isEmpty()) {
          QString condition = QString("%1 <= %2").arg(column, highEdit->text());
          if (allowNull) {
              condition = QString("(%1 OR %2 IS NULL)").arg(condition, column);
          }
          conditions.append(condition);
      }
  };

  auto zFilterValue = [](const QString &textValue) {
      bool isInt = false;
      textValue.toInt(&isInt);

      if (isInt) {
          return textValue;
      }

      return QString::number(atomicSymbol(textValue));
  };

  appendRangeCondition("T12", ui->le_T121, ui->le_T122, true);
  appendRangeCondition("E_GAMMA", ui->le_GE1, ui->le_GE2);
  appendRangeCondition("LEVEL", ui->le_FINE1, ui->le_FINE2);

  if (!ui->le_numA0->text().isEmpty()) {
      const QString condition = QString("A_IT = %1").arg(ui->le_numA0->text());
      conditions.append(condition);
      isoConditions.append(condition);
  } else {
      if (!ui->le_numA1->text().isEmpty()) {
          const QString condition = QString("A_IT >= %1").arg(ui->le_numA1->text());
          conditions.append(condition);
          isoConditions.append(condition);
      }

      if (!ui->le_numA2->text().isEmpty()) {
          const QString condition = QString("A_IT <= %1").arg(ui->le_numA2->text());
          conditions.append(condition);
          isoConditions.append(condition);
      }
  }

  if (!ui->le_numZ0->text().isEmpty()) {
      const QString condition = QString("Z_IT = %1").arg(zFilterValue(ui->le_numZ0->text()));
      conditions.append(condition);
      isoConditions.append(condition);
  } else {
      if (!ui->le_numZ1->text().isEmpty()) {
          const QString condition = QString("Z_IT >= %1").arg(zFilterValue(ui->le_numZ1->text()));
          conditions.append(condition);
          isoConditions.append(condition);
      }

      if (!ui->le_numZ2->text().isEmpty()) {
          const QString condition = QString("Z_IT <= %1").arg(zFilterValue(ui->le_numZ2->text()));
          conditions.append(condition);
          isoConditions.append(condition);
      }
  }

  QString filterExpr = conditions.join(" AND ");
  const QString isoCondition = isoConditions.join(" AND ");

  if (!filterExpr.isEmpty() && !isoCondition.isEmpty()) {
      filterExpr = QString("(%1) OR (%2 AND E_GAMMA IS NULL)").arg(filterExpr, isoCondition);
  }

  if (filterExpr.isEmpty()) {
      qDebug() << "[applyFilters: empty filter avoided, restoring default filter bounds]";
      setDefaultFilters();
      applyFilters();
      return;
  }


  modelFull->setFilter(filterExpr);
  qDebug() << "[applyFilters: check filterExpr]" << filterExpr;
  if (!modelFull->select()) {
      qWarning() << modelFull->lastError().text();
      return;
  }
  fetchAllModelRows();
  levelProxy->rebuildCache();
  gammaProxy->invalidate();

  ui->tableView_Dev->setModel(modelFull);

  // qDebug() << "[applyFilters: Check filterExpr]:" << filterExpr << model->filter();

  filteredIsotopes = prepData();
  qDebug() << "[applyFilters: isotope count]" << filteredIsotopes.count() << filteredIsotopes.size();

  statRefresh();

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearFilters()
{
    // ~~~ Define sumamryStats groupbox lines for easy clearing
    summaryStats = ui->gb_summaryStats->findChildren<QLineEdit*>();
    qDebug() << "[clearFilters CHECK FULL FILTER - before]" << modelFull->filter();

    // qDebug() << "[clearFilters: groupbox type?]" << std::as_const(filterBounds) + std::as_const(summaryStats);
    for (QLineEdit* le : std::as_const(filterBounds) + (std::as_const(summaryStats))) {
      QString objName = le->objectName();
      // qDebug() << "[clearFilters l170: Check object name]" << objName;
      if (le->objectName() != "") {
          le->setText("");
        }
    }
    if (ui->cb_sourceFilter->count() > 0) {
        ui->cb_sourceFilter->setCurrentText("All Sources");
    }

    modelFull->setFilter("1 = 0");
    if (!modelFull->select()) {
        qWarning() << modelFull->lastError().text();
    }
    levelProxy->rebuildCache();
    gammaProxy->invalidate();
    filteredIsotopes.clear();
    ui->tableView_Dev->setModel(modelFull);

    qDebug() << "[clearFilters CHECK FULL FILTER - after]" << modelFull->filter();
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::setDefaultFilters()
{
    if (ui->cb_sourceFilter->count() > 0) {
        ui->cb_sourceFilter->setCurrentText("All Sources");
    }

    ui->le_T121->setText("0.1");
    ui->le_T122->setText("10");
    ui->le_GE1->clear();
    ui->le_GE2->clear();
    ui->le_numA0->clear();
    ui->le_numZ0->clear();
    ui->le_numA1->setText("70");
    ui->le_numA2->setText("80");
    ui->le_numZ1->clear();
    ui->le_numZ2->clear();
    ui->le_FINE1->setText("0");
    ui->le_FINE2->setText("3000");
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::fetchAllModelRows()
{
    while (modelFull && modelFull->canFetchMore()) {
        modelFull->fetchMore();
    }
}


//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

QMap<QPair<int,int>,Isotope> IsomerAPI::prepData()
{

  // qDebug() << "[prepData: BEGIN PREP]";
  QString fullQuery =
        "SELECT A_IT,Z_IT,E_GAMMA,D_EG,T12,D_T12,LEVEL,D_LEVEL,JPI,IT_RATIO,I_GAMMA,M_GAMMA,LEVEL_ID,GAMMA_ID,FINAL_LEVEL_ID FROM Isomers";

  QString filter = modelFull->filter();
  if (!filter.isEmpty()) {
      fullQuery += " WHERE " + filter;
    }

// QPair<int,int> acts as isotope key with A,Z number
  QMap<QPair<int,int>,Isotope> isotopeMap;

  // QVector<Level> prepLevel;
  // QVector<Transition> prepTransition;

  query.exec(fullQuery);

  // prepLevel.push_back({0,"",""});

  while (query.next())
    {
      int A = query.value("A_IT").toInt();
      int Z = query.value("Z_IT").toInt();

      // ~~~~~ isotope key established
      QPair<int,int> key(Z,A);

      double tmpLevelE = query.value("LEVEL").toDouble();
      QString tmpdLevelE = query.value("D_LEVEL").toString();

      double tmpGammaE = query.value("E_GAMMA").toDouble();
      QString tmpdGammaE = query.value("D_EG").toString();


      // double tmpFinal = tmpLevelE - tmpGammaE;
      // QString tmpEmission = QString("%1").arg(tmpGammaE);


      Isotope& iso = isotopeMap[key];
      iso.A = A;
      iso.Z = Z;

      Level* levelPtr = nullptr;

      // ~~~~~ check for level nearness -- later include customization of plots based on diff
      // for (Level& lvl : iso.levels) {
      //     if (qFuzzyCompare(lvl.lvlEnergy + 1.0, tmpLevelE + 1.0)) {
      //         levelPtr = &lvl;
      //         break;
      //     }
      // }

      // ~~~~~ if no near levels, make new entry -- watch for level skipping!!
      if (!levelPtr) {
          if (tmpLevelE != 0.0) {
              Level newLevel;
              newLevel.lvlEnergy = tmpLevelE;
              newLevel.dlvlEnergy = query.value("D_LEVEL").toString();
              newLevel.spin = query.value("JPI").toString();
              newLevel.halfLife = query.value("T12").toDouble();
              newLevel.dhalfLife = query.value("D_T12").toString();

              newLevel.lvlID = query.value("LEVEL_ID").toInt();

              newLevel.IT = query.value("IT_RATIO").toInt();

              // qDebug() << "[prepData: check level skipping]";

              iso.levels.append(newLevel);
              levelPtr = &iso.levels.last();
          } else if (tmpLevelE == 0) {
              Level groundState;
              groundState.lvlEnergy = tmpLevelE;
              groundState.dlvlEnergy = query.value("D_LEVEL").toString();
              groundState.spin = query.value("JPI").toString();
              groundState.halfLife = query.value("T12").toDouble();
              groundState.dhalfLife = query.value("D_T12").toString();
              groundState.lvlID = query.value("LEVEL_ID").toInt();

              groundState.IT = query.value("IT_RATIO").toDouble();


              iso.groundState = groundState;
              levelPtr = &iso.groundState;

          }

      }


      // ~~~~~ add transitions
      Transition tr;

      tr.lvlEnergy = tmpLevelE;
      tr.dlvlEnergy = tmpdLevelE;
      tr.gamEnergy = tmpGammaE;
      tr.dgamEnergy = tmpdGammaE;
      tr.label = query.value("E_GAMMA").toString();
      tr.trID = query.value("GAMMA_ID").toInt();
      tr.finID = query.value("FINAL_LEVEL_ID").toInt();

      tr.IGam = query.value("I_GAMMA").toDouble();
      tr.MGam = query.value("M_GAMMA").toString();

      // ~~~~~ point to current level
      levelPtr -> transitions.append(tr);
      // qDebug() << "[prepData: isotope check]" << query.value("A_IT") << query.value("Z_IT");
    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();

    // for (Isotope &storedIso : isotopeMap) {
    //     qDebug() << "[prepData: check isotopes key]" << storedIso.A << storedIso.Z;
    //     qDebug() << "[prepData: check if isotope empty levels]" << storedIso.levels.isEmpty();
    //     qDebug();
    // }
    /// Clean entries with only ground level
    for (auto storedIso = isotopeMap.begin(); storedIso != isotopeMap.end(); )
    {
        if (storedIso->levels.isEmpty()) {
            storedIso = isotopeMap.erase(storedIso);
            // qDebug() << "[prepData: isotope is empty]" << storedIso.key() << atomicSymbol(storedIso.key().first);
            // qDebug() << "   gs:" << storedIso->groundState.lvlID;

        } else {
            ++storedIso;
        }
    }

    qDebug() << "[prepData: check isotope count]" << isotopeMap.count();

    return isotopeMap;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

void IsomerAPI::clearSelection(int page){
    if (page == 0) {
        ui->tableView_GammaSolo->selectionModel()->clearSelection();
    } else if (page == 1) {
        ui->tableView_IsomerSolo->selectionModel()->clearSelection();
    } else if (page == 2) {
        ui->tableView_Isomer->selectionModel()->clearSelection();
        ui->tableView_Gammas->selectionModel()->clearSelection();
    } else if (page == 3) {
        ui->tableView_Dev->selectionModel()->clearSelection();
    }
}

bool IsomerAPI::checkSelection(int page){
    if (page == 0) {
        return ui->tableView_GammaSolo->selectionModel()->hasSelection();

    } else if (page == 1) {
        return ui->tableView_IsomerSolo->selectionModel()->hasSelection();
    } else if (page == 2) {
        return (ui->tableView_Isomer->selectionModel()->hasSelection() or
                ui->tableView_Gammas->selectionModel()->hasSelection());
    } else if (page == 3) {
        return(ui->tableView_Dev->selectionModel()->hasSelection());
    }

    return false;
}

QTableView *IsomerAPI::getTableView(int page, SchemeType schemeType) {
    if (page == 0) {
        return ui->tableView_GammaSolo;
    } else if (page == 1) {
        return ui->tableView_IsomerSolo;
    } else if (page == 2) {
        if (schemeType == SchemeType::DecayFromLevel) {
            return ui->tableView_Isomer;
        } else if (schemeType == SchemeType::GammaCoincidence) {
            return ui->tableView_Gammas;
        }
    } else if (page == 3) {
        qDebug() << "[getTableView: do not run this for dev view]";
        return nullptr; // Aborts function and returns a null pointer
    }

    return nullptr; // Fallback for any unexpected values
}

