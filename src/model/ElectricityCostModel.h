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

#ifndef MODEL_ELECTRICITYCOSTMODEL_H_
#define MODEL_ELECTRICITYCOSTMODEL_H_

#include <cstdlib>
#include <time.h>

class ElectricityCostModel {

public:
    ElectricityCostModel();
    static constexpr double max = 0.6;  // EUR per KWh
    static constexpr double min = 0.2;  // EUR per KWh

    static double getElectricityCost();
    static double getElectricityCostNoUpdate();

private:
    static double cost;  // EUR per KWh

    static double updateCost();

    static bool initialized;;
};

#endif /* MODEL_ELECTRICITYCOSTMODEL_H_ */
