/*
 * CostModel.cpp
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#include <model/CostModel.h>

Define_Module(CostModel)

CostModel::CostModel() {
    eModel = nullptr;
}

CostModel::CostModel(EnergyModel* eModel, double pollingIntervalLen) {
    this->eModel = eModel;
    this->pollingIntervalLen = pollingIntervalLen;
    requestsHandled = calcRequestsHandled();
    cost = calcCost();
    revenuePerAd = calcRevenuePerAd();
    revenue = calcRevenue();
    std::cout<<"REQs: " << requestsHandled << "\tREVENUE: " << revenue << "EUR\tREV/AD: " << revenuePerAd << "EUR\n";
}

CostModel::~CostModel() {
    // TODO Auto-generated destructor stub
}

double CostModel::calcCost() {
    double powerDraw = eModel->getWallPowerDraw();
    double energyUsed = powerToEnergy(powerDraw);
    double cost = energyToCost(energyUsed);
    return cost;
}

double CostModel::powerToEnergy(double powerDraw) {
    constexpr double KWH_PER_SEC = 1.0 / 3600;
    return powerDraw * pollingIntervalLen * KWH_PER_SEC;
}

double CostModel::energyToCost(double energyUsed) {
    double energyCost = ElectricityCostModel::getElectricityCost();
    //std::cout << "ENRG_COST: " << energyCost << "EUR/KWh\n";
    return energyUsed;
}

long long CostModel::calcRequestsHandled() {
    std::vector<MTBrownoutServer*> servers = EnergyModel::getServers();
    long long total = 0;
    for (auto const& server : servers) {
        total += server->getRequestsHandled();
    }
    return total;
}

double CostModel::calcRevenue() {
    double dimmer = EnergyModel::model->getDimmerFactor();
    //std::cout << "Dimmer: " << dimmer << std::endl;
    double adsServedEstimate = requestsHandled * dimmer;
    double revenue = adsServedEstimate * revenuePerAd;
    return revenue;
}

double CostModel::getCost() {
    return cost;
}

double CostModel::getRevenue() {
    return revenue;
}

double CostModel::getCostPerReq() {
    return cost / requestsHandled;
}

double CostModel::getRevenuePerReq() {
    return revenue / requestsHandled;
}

double CostModel::calcRevenuePerAd() {
    double costPerRequest = getCostPerReq();
    double markedUpCost = (1 + adMarkup) * costPerRequest;
    constexpr double PRECISION = 10e5;

    // find the random amount within 'adPriceRange' of that
    int upperMargin = (1 + adPriceRange) * markedUpCost * PRECISION; // 10e5 for 5 decimal precision
    int lowerMargin = (1 - adPriceRange) * markedUpCost * PRECISION; // 10e5 for 5 decimal precision

    int range = upperMargin - lowerMargin;
    int valueInt = rand() % range + lowerMargin;
    double value = (double)valueInt / PRECISION;
    //std::cout << "CPR: " << costPerRequest << "EUR\t MARKED: " << markedUpCost << "EUR\tFINAL: " << value << "EUR\n";
    return value;
}

double CostModel::getRevenuePerAd() {
    return revenuePerAd;
}

long long CostModel::getRequestsHandled() {
    return requestsHandled;
}
