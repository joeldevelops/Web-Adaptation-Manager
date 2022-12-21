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

RollingLog<long long>* ReactiveAdaptationManager3::requestLog = new RollingLog<long long>(5);
RollingLog<double>* ReactiveAdaptationManager3::revenueLog = new RollingLog<double>(5);
RollingLog<double>* ReactiveAdaptationManager3::costLog = new RollingLog<double>(5);
RollingLog<double>* ReactiveAdaptationManager3::latencyLog = new RollingLog<double>(5);

ReactiveAdaptationManager3::ReactiveAdaptationManager3() {
    totalRevenue = 0;
    totalCost = 0;
    error = 0;
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
    long long prediction = requestLog->predictNext();
    long long requests = cModel.getRequestsHandled();

    totalRevenue += revenue;
    totalCost += cost; 

    if (requestLog->getHistory().size() > 2) 
        error += (requests > prediction) ? requests - prediction : prediction - requests;
    std::cout << "REQ PRED: " << prediction << " (ERR: " << abs(requests - prediction) / (double)requests * 100 << "%)  \tSYS COST: " << cost << " EUR\tTOT COST: " << totalCost << " EUR\tTOT REV: " << totalRevenue << " EUR\tBAL: " << totalRevenue - totalCost << " EUR\n";
    std::cout << "SERV. T.: " << responseTime << "\tERR TOT: " << error << "\n";

    std::cout << "eREV: " << revenueLog->predictNext() << "\teCOST: " << costLog->predictNext() << "\teLATENCY: " << latencyLog->predictNext() << "\n\n";

    long long requestsHandled = cModel.getRequestsHandled();
    requestLog->addEntry(requestsHandled);
    revenueLog->addEntry(revenue);
    costLog->addEntry(cost);
    latencyLog->addEntry(responseTime);

    
    MacroTactic* pMacroTactic = new MacroTactic;
    return pMacroTactic;       
}




/**
 * The stuff below is a failed attempt
 * If you guys have any ideas on how to salvage it then great, if not, we can get rid of it
*/

ReactiveAdaptationManager3::ModelPredictor::ModelPredictor(long long requests, int servers, int threads, double dimmer, Model* model) {
    this->requests = requests;
    this->servers = servers;
    this->threads = threads;
    this->dimmer = dimmer;
    this->model = model;
    this->currentState = model->getObservations();    
    serverExample = EnergyModel::getServers().front();
}

double ReactiveAdaptationManager3::ModelPredictor::estimateLatency() {
    // estimate time per job based on proposed dimmer assuming same number of servers
    // assumes dimmer and latency are directly proportional (more dimmer, more latency)
    double latencySameServers = latencyLog->getHistory().front() *  model->getDimmerFactor() / dimmer;
    // adjust for new number of servers
    // assumes servers and latency are indirectly proportional (more servers, less latency)
    double latencyNewServers = latencySameServers * model->getActiveServers() / servers;
    // adjust for new requests
    // assumes direct proportionality (more requests, more latency)
    double latencyNewReqs = latencyLog->getHistory().front() * requests / latencyNewServers; 
    return latencyNewReqs;
}

double ReactiveAdaptationManager3::ModelPredictor::estimateCost() {
    // estimate utilization with predicted requests
    // more requests, more utilization
    double utilSameServers = requests * currentState.utilization / requestLog->getHistory().front();
    // now adjust to new number of servers
    // more servers, less utilization
    double utilNewServers = model->getActiveServers() * utilSameServers / servers;
    // adjust to estimated request count
    // more requests, more cost
    double utilNewReqs = requests * utilNewServers / requestLog->getHistory().front();
    return utilNewReqs;
}

double ReactiveAdaptationManager3::ModelPredictor::estimateRevenue() {
    return estimateCost() * model->getDimmerFactor() * 1.05;
}



