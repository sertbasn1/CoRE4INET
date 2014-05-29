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

#include "CoRE4INET_BaseInControl.h"

namespace CoRE4INET {

simsignal_t BaseInControl::rxPkSignal = SIMSIGNAL_NULL;

void BaseInControl::initialize()
{
    Timed::initialize();
    rxPkSignal = registerSignal("rxPk");
}

void BaseInControl::setParameters(EtherFrame *frame)
{
    int i = frame->findPar("received_total");
    cMsgPar* par;
    if (i >= 0)
        par = &frame->par(i);
    else
        par = &frame->addPar("received_total");
    par->setLongValue((long) timer->getTotalTicks());

    i = frame->findPar("received_port");
    if (i >= 0)
        par = &frame->par(i);
    else
        par = &frame->addPar("received_port");
    par->setLongValue(getParentModule()->getIndex());
}

void BaseInControl::recordPacketReceived(EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

}
