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

std::vector<double> EnergyModel::getUtilizations() {
    std::vector<double> result;

    std::vector<MTBrownoutServer*> servers = getServers();

    for (unsigned int i = 0; i < servers.size(); i++) {
        int maxThreads = servers.at(i)->getMaxThreads();
        int usedThreads = servers.at(i)->getRunningJobs();
        double utilization = usedThreads / (double)maxThreads;
        std::cout << utilization * 100 << "% " << "(max power:" << servers.at(i)->getMaxPower() << " )\t";
    }
    std::cout << "\n";

    //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

    return result;
}
