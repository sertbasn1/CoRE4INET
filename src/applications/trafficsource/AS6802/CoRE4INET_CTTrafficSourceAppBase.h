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

#ifndef __CORE4INET_CTTRAFFICSOURCEBASE_H_
#define __CORE4INET_CTTRAFFICSOURCEBASE_H_

//CoRE4INET
#include "CoRE4INET_TrafficSourceAppBase.h"
#include "CoRE4INET_CTApplicationBase.h"

namespace CoRE4INET {

/**
 * @brief Base class for a traffic generator application.
 *
 * @sa ApplicationBase
 * @ingroup Applications
 */
class CTTrafficSourceAppBase : public virtual TrafficSourceAppBase, public virtual CTApplicationBase
{
    public:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize();
    protected:

        /**
         * @brief Generates and sends a new Message.
         *
         * The message is sent to the buffer with the ct_id defined in parameter ct_id of the module.
         * The message kind is defined by the buffer-type (RC/TT) of the buffer the message is sent to.
         * The size is defined by the payload parameter of the module.
         */
        virtual void sendMessage();
};

} //namespace

#endif
