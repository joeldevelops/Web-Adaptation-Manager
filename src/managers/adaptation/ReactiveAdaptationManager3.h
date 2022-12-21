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


class ReactiveAdaptationManager3 : public BaseAdaptationManager {
public:
    ReactiveAdaptationManager3();
    virtual ~ReactiveAdaptationManager3();

protected:
    virtual Tactic* evaluate();

private:
    double totalRevenue;
    double totalCost;

};

#endif /* MANAGERS_ADAPTATION_REACTIVEADAPTATIONMANAGER3_H_ */
