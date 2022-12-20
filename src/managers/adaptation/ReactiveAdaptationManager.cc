/*******************************************************************************
 * Simulator of Web Infrastructure and Management
 * Copyright (c) 2016 Carnegie Mellon University.
 * All Rights Reserved.
 *  
 * THIS SOFTWARE IS PROVIDED "AS IS," WITH NO WARRANTIES WHATSOEVER. CARNEGIE
 * MELLON UNIVERSITY EXPRESSLY DISCLAIMS TO THE FULLEST EXTENT PERMITTED BY LAW
 * ALL EXPRESS, IMPLIED, AND STATUTORY WARRANTIES, INCLUDING, WITHOUT
 * LIMITATION, THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, AND NON-INFRINGEMENT OF PROPRIETARY RIGHTS.
 *  
 * Released under a BSD license, please see license.txt for full terms.
 * DM-0003883
 *******************************************************************************/

#include "ReactiveAdaptationManager.h"
#include "managers/adaptation/UtilityScorer.h"
#include "managers/execution/AllTactics.h"
#include "model/EnergyModel.h"
#include "model/CostModel.h"

using namespace std;

Define_Module(ReactiveAdaptationManager);

/**
 * Reactive adaptation
 *
 * RT = response time
 * RTT = response time threshold
 *
 * - if RT > RTT, add a server if possible, if not decrease dimmer if possible
 * - if RT < RTT and spare utilization > 1
 *      -if dimmer < 1, increase dimmer else if servers > 1 and no server booting remove server
 */

double ReactiveAdaptationManager::totalCost = 0;
double ReactiveAdaptationManager::totalRevenue = 0;

Tactic* ReactiveAdaptationManager::evaluate() {
    MacroTactic* pMacroTactic = new MacroTactic;
    Model* pModel = getModel();
    const double dimmerStep = 1.0 / (pModel->getNumberOfDimmerLevels() - 1);
    double dimmer = pModel->getDimmerFactor();
    double spareUtilization =  pModel->getConfiguration().getActiveServers() - pModel->getObservations().utilization;
    bool isServerBooting = pModel->getServers() > pModel->getActiveServers();
    double responseTime = pModel->getObservations().avgResponseTime;
    double evaluationPeriod = 20;
    EnergyModel eModel(pModel);
    CostModel cModel(&eModel, evaluationPeriod);
    double cost = cModel.getCost();
    totalCost += cost;
    totalRevenue += cModel.getRevenue();
    cout << "SYS COST: " << cost << " EUR\tTOT COST: " << totalCost << " EUR\tTOT REV: " << totalRevenue << " EUR\tBAL: " << totalRevenue - totalCost << " EUR\n\n";


    if (responseTime > RT_THRESHOLD) {
        if (!isServerBooting
                && pModel->getServers() < pModel->getMaxServers()) {
            pMacroTactic->addTactic(new AddServerTactic);
        } else if (dimmer > 0.0) {
            dimmer = max(0.0, dimmer - dimmerStep);
            pMacroTactic->addTactic(new SetDimmerTactic(dimmer));
        }
    } else if (responseTime < RT_THRESHOLD) { // can we increase dimmer or remove servers?

        // only if there is more than one server of spare capacity
        if (spareUtilization > 1) {
            if (dimmer < 1.0) {
                dimmer = min(1.0, dimmer + dimmerStep);
                pMacroTactic->addTactic(new SetDimmerTactic(dimmer));
            } else if (!isServerBooting
                    && pModel->getServers() > 1) {
                pMacroTactic->addTactic(new RemoveServerTactic);
            }
        }
    }

    return pMacroTactic;
}
