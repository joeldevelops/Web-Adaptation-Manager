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
    pollingIntervalLen = 1;
}

CostModel::CostModel(EnergyModel* eModel, double pollingIntervalLen) {
    this->eModel = eModel;
    this->pollingIntervalLen = pollingIntervalLen;
}

CostModel::~CostModel() {
    // TODO Auto-generated destructor stub
}

double CostModel::getCost() {
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
    energyCost = ElectricityCostModel::getElectricityCost();
    std::cout << "\neCOST: " << energyCost << "EUR/KWh\n";
    return energyUsed;
}
