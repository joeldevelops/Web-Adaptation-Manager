/*
 * ReactiveAdaptationManager3.h
 *
 *  Created on: Dec 15, 2022
 *      Author: root
 */

#ifndef MANAGERS_ADAPTATION_REACTIVEADAPTATIONMANAGER3_H_
#define MANAGERS_ADAPTATION_REACTIVEADAPTATIONMANAGER3_H_

#include "BaseAdaptationManager.h"
#include "model/CostModel.h"
#include "model/EnergyModel.h"
#include "managers/execution/AllTactics.h"
#include "RollingLog.h"
#include "model/Observations.h"


class ReactiveAdaptationManager3 : public BaseAdaptationManager {

protected:
    virtual Tactic* evaluate();
    double totalRevenue;
    double totalCost;
    static RollingLog<long long>* requestLog;
    static RollingLog<double>* revenueLog;
    static RollingLog<double>* costLog;
    static RollingLog<double>* latencyLog;
    long long error;

public:
    ReactiveAdaptationManager3();
    virtual ~ReactiveAdaptationManager3();

    class ModelPredictor {
    public:
        ModelPredictor(long long requests, int servers, int threads, double dimmer, Model* model);
        double estimateCost();
        double estimateLatency();
        double estimateRevenue();

    private:
        long long requests;
        int servers;
        int threads;
        double dimmer;
        Model* model;
        Observations currentState;
        const MTBrownoutServer* serverExample;
    };
};

#endif /* MANAGERS_ADAPTATION_REACTIVEADAPTATIONMANAGER3_H_ */
