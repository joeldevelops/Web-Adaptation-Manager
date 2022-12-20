/*
 * EnergyModel.cpp
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#include <model/EnergyModel.h>


using namespace omnetpp;


EnergyModel::EnergyModel(Model* model) {
    this->model = model;
}

EnergyModel::~EnergyModel() {
    return;
}

Model* EnergyModel::getModel() {
    return model;
}

std::vector<MTBrownoutServer*> EnergyModel::getServers() {
    std::vector<MTBrownoutServer*> result;

    int serverCount = model->getActiveServers();
    cSimulation* simulation = getSimulation();
    for (unsigned int i = 1; i <= serverCount; i++) {
        std::stringstream id;
        id << "server";
        id << i;

        cModule* server_uncast = simulation->getSystemModule()->getSubmodule(id.str().c_str())->getSubmodule("server");
        if (!server_uncast) std::cout << "Couldn't get submodule " << id.str() << std::endl;
        MTBrownoutServer* server = dynamic_cast<MTBrownoutServer*>(server_uncast);

        result.push_back(server);
        id.clear();
    }
    return result;
}

std::vector<double> EnergyModel::getUtilizations(std::vector<MTBrownoutServer*> servers) {
    std::vector<double> result;

    for (unsigned int i = 0; i < servers.size(); i++) {
        int maxThreads = servers.at(i)->getMaxThreads();
        int usedThreads = servers.at(i)->getRunningJobs();
        double utilization = usedThreads / (double)maxThreads;
        result.push_back(utilization);
    }

    return result;
}

std::vector<double> EnergyModel::getInternalPowerDraws(std::vector<MTBrownoutServer*> servers) {
    std::vector<double> result;
    std::vector<double> utilizations = getUtilizations(servers);

    for (unsigned int i = 0; i < servers.size(); i++) {
        double dynamicRange = servers.at(i)->getDynamicRange();
        double utilization = utilizations.at(i);

        // calculate the formula for the graph of the dynamic range
        double slope = ((1 - dynamicRange) / (1 - 0.1));
        double bias = dynamicRange - (slope * 0.1);

        double efficiency = utilization * slope + bias;
        double powerDraw = efficiency * servers.at(i)->getMaxPower();
        result.push_back(powerDraw);

        std::cout << "Server " << i << ": \t UTIL: " << utilizations.at(i)*100 << "%\t PWR_USAGE: " << efficiency * 100 << "%\t PWR: " << powerDraw << "W\n";
    }

    return result;
}

double EnergyModel::getWallPowerDraw() {
    std::vector<MTBrownoutServer*> servers = getServers();
    std::vector<double> internalPowerDraws = getInternalPowerDraws(servers);
    psuFactory powerSupplyFactory;

    double totalWallPower = 0;

    for (unsigned int i = 0; i < servers.size(); i++) {
        MTBrownoutServer* server = servers.at(i);
        double internalPowerDraw = internalPowerDraws.at(i);

        psuBase* psu = powerSupplyFactory.get(server->getPSUClass());
        double wallPower = psu->getWallPower(server->getMaxPower(), internalPowerDraws.at(i));

        totalWallPower += wallPower;

        std::cout << "[Server" << i << " WALLPWR: " << wallPower << "W] ";
    }
    std::cout << "\n";

    return totalWallPower;
}

