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

#include "core4inet/linklayer/filtering/IEEE8021Qci/meter/IEEE8021QciMeter.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciMeter);

void IEEE8021QciMeter::initialize()
{
    streamOutput = dynamic_cast<IEEE8021QciOutput*>(getParentModule()->getSubmodule("streamOutput"));
    if (!streamOutput)
    {
        throw cRuntimeError("Cannot find stream output module");
    }
}

void IEEE8021QciMeter::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        if (IEEE8021QciCtrl *ctrl = dynamic_cast<IEEE8021QciCtrl*>(msg))
        {
            cPacket *data = ctrl->decapsulate();
            delete ctrl;
            sendDirect(data, streamOutput->gate("filterIn"));
        }
        else
        {
            sendDirect(msg, streamOutput->gate("filterIn"));
        }
    }
}

} //namespace