//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <model/ElectricityCostModel.h>

ElectricityCostModel::ElectricityCostModel() {

}

double ElectricityCostModel::cost = ElectricityCostModel::max / ElectricityCostModel::min;

bool ElectricityCostModel::initialized = false;

double ElectricityCostModel::updateCost() {
    const int SEED = 1337; //time(NULL);

    if (!initialized) {
        initialized = true;
        srand(SEED);
    }

    int action = rand() % 3;
    double changeAmt = 0.05 * (max - min); // don't make huge jumps, only 5% of range

    switch (action) {
    case 0: // increase
        cost += changeAmt;
        break;
    case 1: // decrease
        cost -= changeAmt;
        break;
    case 2: // nothing
        break;
    }

    if (cost > max) cost = max;
    if (cost < min) cost = min;
}

double ElectricityCostModel::getElectricityCost() {
    ElectricityCostModel::updateCost();
    return ElectricityCostModel::cost;
}

double ElectricityCostModel::getElectricityCostNoUpdate() {
    return cost;
}
