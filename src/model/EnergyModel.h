/*
 * EnergyModel.h
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#ifndef MODEL_ENERGYMODEL_H_
#define MODEL_ENERGYMODEL_H_

#include <model/Model.h>
#include <omnetpp.h>
#include <vector>
#include <modules/MTBrownoutServer.h>
#include "model/powerSupply/psuFactory.h"
#include <string>

class EnergyModel {
public:
    EnergyModel(Model* model);
    virtual ~EnergyModel();
    Model* getModel();

    static Model* model;
    double dynamicRange;
    double efficiencyPSU;
    double maxPower;

    static std::vector<MTBrownoutServer*> getServers();
    std::vector<double> getUtilizations(std::vector<MTBrownoutServer*> servers);
    std::vector<double> getInternalPowerDraws(std::vector<MTBrownoutServer*> servers);
    std::vector<double> getInernalPowerDraws(std::vector<MTBrownoutServer*> servers);
    double getWallPowerDraw();
    double getAvgUtilization();
};

#endif /* MODEL_ENERGYMODEL_H_ */
