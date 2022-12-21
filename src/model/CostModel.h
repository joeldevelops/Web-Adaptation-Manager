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
    double getRevenue();
    double getCostPerReq();
    double getRevenuePerReq();
    double getRevenuePerAd();

private:
    EnergyModel* eModel;
    const double adMarkup = 0.05;
    const double adPriceRange = 0.1;
    double pollingIntervalLen; // in seconds
    double cost;
    double revenue;
    double revenuePerAd;
    long long requestsHandled;


    double powerToEnergy(double powerDraw);  // energy in KWh
    double energyToCost(double energyUsed);

    // This function has side effects, only call it once per "evaluation"
    // It calculates the number of requests handled SINCE THE LAST CALL
    long long calcRequestsHandled(); // since last check

    /*
     * Only call once per adaptation loop "iteration". Has side effects.
     */
    double calcCost();

    /*
     * Only call once per adaptation loop "iteration". Has side effects.
     */
    double calcRevenue();

    /*
     * Only call once per adaptation loop "iteration". Has side effects.
     */
    double calcRevenuePerAd();

};

#endif /* MODEL_COSTMODEL_H_ */
