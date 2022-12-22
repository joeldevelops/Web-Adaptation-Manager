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

using namespace std;

RollingLog<long long>* ReactiveAdaptationManager3::requestLog = new RollingLog<long long>(5);
RollingLog<double>* ReactiveAdaptationManager3::revenueLog = new RollingLog<double>(5);
RollingLog<double>* ReactiveAdaptationManager3::costLog = new RollingLog<double>(5);
RollingLog<double>* ReactiveAdaptationManager3::latencyLog = new RollingLog<double>(5);
RollingLog<double>* ReactiveAdaptationManager3::costMarginLog = new RollingLog<double>(5);

ReactiveAdaptationManager3::ReactiveAdaptationManager3() {
    totalRevenue = 0;
    totalCost = 0;
    totalBudget = 0;
    error = 0;
}

ReactiveAdaptationManager3::~ReactiveAdaptationManager3() {
    // TODO Auto-generated destructor stub
}

Tactic* ReactiveAdaptationManager3::evaluate() {

    const double EVALUATION_PERIOD = getSimulation()->getSystemModule()->par("evaluationPeriod");
    const double LATENCY_THRESH = RT_THRESHOLD;
    const double COST_THRESH = par("budgetPerInterval");
    const double LOOKBACK = 5;

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
    long long prediction = requestLog->predictNext();
    long long requests = cModel.getRequestsHandled();

    totalRevenue += revenue;
    totalCost += cost; 
    totalBudget += COST_THRESH;

    cout << "COST: " << cost << ((cost > COST_THRESH) ? " [!!!]" : " ");
    cout << "\tCOST TTL: " << totalCost;
    cout << "\tBUDGET TTL: " << totalBudget;
    cout << "\tREVENUE: " << revenue;
    cout << "\tBALANCE: " << totalRevenue - totalCost;
    cout << endl;
    cout << "LATENCY: " << responseTime << ((responseTime > RT_THRESHOLD) ? " [!!!]" : " ");
    cout << "\tDIMMER: " << dimmer;
    cout << endl << endl;

    long long requestsHandled = cModel.getRequestsHandled();
    requestLog->addEntry(requestsHandled);
    revenueLog->addEntry(revenue);
    costLog->addEntry(cost);
    latencyLog->addEntry(responseTime);
    costMarginLog->addEntry(COST_THRESH - cost);
    
    double expLatency = latencyLog->predictNext();
    double expRequests = requestLog->predictNext();
    double avgUtil = eModel.getAvgUtilization();

    bool isLoadIncreasing = expRequests > requests;
    bool isOverLatency = responseTime > LATENCY_THRESH;
    bool isOverBudget = cost > COST_THRESH || totalCost > totalBudget;

    bool isUnderUtilized = avgUtil < 0.2;
    bool isOverUtilized = avgUtil > 0.9;
    bool canAddServers = pModel->getServers() < pModel->getMaxServers();
    bool canRemoveServers = pModel->getActiveServers() > 1;
    bool canIncreaseDimmer = dimmer < 1;
    bool canLowerDimmer = dimmer > 0;

    MacroTactic* mTactic = new MacroTactic;

    if (isOverLatency) {
        // Lower the dimmer a bit since that has an immediate effect
        if (canLowerDimmer) {
            mTactic->addTactic(new SetDimmerTactic(max(0.0, dimmer - dimmerStep)));
        }

        // Can we add a new server? That would have a more permanent effect
        if (!isServerBooting && canAddServers && !isOverBudget) {
            mTactic->addTactic(new AddServerTactic);
        }
    }
    else if (isLoadIncreasing && expLatency > LATENCY_THRESH * 0.8) {
        if (!isServerBooting && canAddServers && !isOverBudget) {
            mTactic->addTactic(new AddServerTactic);
        }
        else {
            mTactic->addTactic(new SetDimmerTactic(max(0.0, dimmer - dimmerStep)));
        }
        
    }
    else if (!isLoadIncreasing) {
        if (canIncreaseDimmer && !isOverBudget) mTactic->addTactic(new SetDimmerTactic(min(1.0, dimmer + dimmerStep)));

        if (spareUtilization > 1 && canRemoveServers && expRequests < 0.9 * requests) {
                mTactic->addTactic(new RemoveServerTactic);
            }
        else if (isOverBudget && spareUtilization > 0.5 && canRemoveServers) {
            mTactic->addTactic(new RemoveServerTactic);
        }
    }
    
    return mTactic;       
}
