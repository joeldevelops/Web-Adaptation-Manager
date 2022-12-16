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

class EnergyModel {
public:
    EnergyModel(Model* model);
    virtual ~EnergyModel();
    Model* getModel();

//protected:
    Model* model;
    double dynamicRange;
    double efficiencyPSU;
    double maxPower;

    std::vector<double> getUtilizations();
    std::vector<MTBrownoutServer*> getServers();
};

#endif /* MODEL_ENERGYMODEL_H_ */
