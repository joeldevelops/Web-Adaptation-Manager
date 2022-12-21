/*
 * ReactiveAdaptationManager3.cpp
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#include <managers/adaptation/ReactiveAdaptationManager3.h>
#include "managers/adaptation/UtilityScorer.h"
#include "managers/execution/AllTactics.h"

Define_Module(ReactiveAdaptationManager3);

ReactiveAdaptationManager3::ReactiveAdaptationManager3() {
    totalRevenue = 0;
    totalCost = 0;
}

ReactiveAdaptationManager3::~ReactiveAdaptationManager3() {
    // TODO Auto-generated destructor stub
}

Tactic* ReactiveAdaptationManager3::evaluate() {

    const double EVALUATION_PERIOD = 20;

    Model* pModel = getModel();
    const double dimmerStep = 1.0 / (pModel->getNumberOfDimmerLevels() - 1);
    double dimmer = pModel->getDimmerFactor();
    double spareUtilization =  pModel->getConfiguration().getActiveServers() - pModel->getObservations().utilization;
    bool isServerBooting = pModel->getServers() > pModel->getActiveServers();
    double responseTime = pModel->getObservations().avgResponseTime;
    
    EnergyModel eModel(pModel);
    CostModel cModel(&eModel, EVALUATION_PERIOD);

    double cost = cModel.getCost();
    double revenue = cModel.getRevenue();
    totalRevenue += revenue;
    totalCost += cost;
    std::cout << "SYS COST: " << cost << " EUR\tTOT COST: " << totalCost << " EUR\tTOT REV: " << totalRevenue << " EUR\tBAL: " << totalRevenue - totalCost << " EUR\n\n";


    // TODO Make requestsHandled in CostModel public so we can get it from here
    //long long requestsHandled = cModel.requestsHandled;

    // TODO update rolling log(s) with new values
    
    MacroTactic* pMacroTactic = new MacroTactic;
    return pMacroTactic;       
}



