/*
 * CostModel.h
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#ifndef MODEL_COSTMODEL_H_
#define MODEL_COSTMODEL_H_

#include "model/EnergyModel.h"
#include <omnetpp.h>
#include "model/ElectricityCostModel.h"

class CostModel  : public omnetpp::cSimpleModule {
public:
    CostModel();
    CostModel(EnergyModel* eModel, double pollingIntervalLen);
    virtual ~CostModel();

    double getCost();
    double energyCost;


private:
    EnergyModel* eModel;
    double adMarkup;
    double adPriceRange;
    double pollingIntervalLen; // in seconds

    double powerToEnergy(double powerDraw);  // energy in KWh
    double energyToCost(double energyUsed);

};

#endif /* MODEL_COSTMODEL_H_ */
