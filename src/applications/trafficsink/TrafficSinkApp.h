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

#ifndef __TTETHERNETMODELV2_TRAFFICSINK_H_
#define __TTETHERNETMODELV2_TRAFFICSINK_H_

#include <omnetpp.h>
#include "ApplicationBase.h"

namespace TTEthernetModel {

/**
 * @brief Traffic sink application used for statistics collection.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications
 *
 * @author Till Steinbach
 */
class TrafficSinkApp : public ApplicationBase
{
    private:
        /**
         * Signal that is emitted every time a frame was sent.
         */
        static simsignal_t rxPkSignal;

        /**
         * Signal that contains the latency until the frame enters the application.
         * Uses encapsulated packet or frame when nothing is encapsulated
         */
        static simsignal_t latencySignal;
    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize();

        /**
         * @brief collects incoming message and writes statistics.
         *
         * @param msg incoming frame
         */
        virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
