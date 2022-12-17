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

#ifndef MODEL_POWERSUPPLY_PSUFACTORY_H_
#define MODEL_POWERSUPPLY_PSUFACTORY_H_

#include "model/powerSupply/psuBase.h"
#include "model/powerSupply/psuGold.h"
#include "model/powerSupply/psuTitanium.h"
#include "model/powerSupply/psuPlatinum.h"

static class psuFactory {
public:
    psuFactory();
    virtual ~psuFactory();
    static psuBase* get(std::string psuClass, double maxPower);
};

#endif /* MODEL_POWERSUPPLY_PSUFACTORY_H_ */
