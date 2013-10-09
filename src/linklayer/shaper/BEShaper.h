#ifndef __TTE4INET_BESHAPER_H
#define __TTE4INET_BESHAPER_H

#include <ModuleAccess.h>

namespace TTEthernetModel {

/**
 * @brief A Shaper for BEMessages.
 *
 * The BEShaper only allows lower priorities to transmit when there are no
 * BE messages queued. This class is usually used with BaseShaper as template
 * class, as there are usually no lower priority messages than BE messages.
 *
 * @see BaseShaper
 *
 */
template <class TC>
class BEShaper : public TC
{
    public:
        /**
         * @brief Constructor
         */
        BEShaper();
        /**
         * @brief Destructor
         */
        ~BEShaper();
    protected:
            /**
             * @brief Signal that is emitted when the queue length of best-effort messages changes.
             */
            static simsignal_t beQueueLengthSignal;
    private:
            /**
             * @brief Queue for best-effort messages
             */
            cQueue beQueue;
    protected:
            /**
             * Initializes the module
             *
             * @param stage The stages. Module initializes when stage==0
             */
            virtual void initialize(int stage);

            /**
             * @brief Returns the number of initialization stages this module needs.
             *
             * @return returns 1 or more depending on inheritance
             */
            virtual int numInitStages() const;


       /**
        * @brief Forwards the messages from the different buffers and LLC
        * according to the specification for BEMessages.
        *
        * Best-effort messages are send immediately, lower priority frames are queued
        * as long as there are best-effort messages waiting.
        * If the mac layer is idle, messages are picked from the queues according
        * to the priorities, using the template class.
        *
        * @param msg the incoming message
        */
        virtual void handleMessage(cMessage *msg);


        /**
         * @brief Queues messages in the correct queue
         *
         * Best-effort messages are queued in this module, other messages are forwarded to the
         * template classes enqueueMessage method
         *
         * @param msg the incoming message
         */
        virtual void enqueueMessage(cMessage *msg);

        /**
        * @brief this method is invoked when the underlying mac is idle.
        *
        * When this method is invoked the module sends a new message when there is
        * one. Else it saves the state and sends the message immediately when it is
        * received.
        *
        * @param msg the message to be queued
        */
        virtual void requestPacket();

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty();

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear();

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns NULL if the queue is empty.
         *
         * @return the message with the highest priority from any queue. NULL if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop();

        /**
        * @brief Returns a pointer to a frame directly from the queues.
        *
        * front must return a pointer to the same message pop() would return.
        *
        * @return pointer to the message with the highest priority from any queue. NULL if the
        * queues are empty
        */
        virtual cMessage *front();
};


template <class TC>
simsignal_t BEShaper<TC>::beQueueLengthSignal = SIMSIGNAL_NULL;

template <class TC>
BEShaper<TC>::BEShaper(){
    beQueue.setName("BE Messages");
}

template <class TC>
BEShaper<TC>::~BEShaper(){
    beQueue.clear();
}

template <class TC>
void BEShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if(stage==0){
        beQueueLengthSignal = cComponent::registerSignal("beQueueLength");
    }
}

template <class TC>
int BEShaper<TC>::numInitStages() const{
    if(TC::numInitStages()>1){
        return TC::numInitStages();
    }
    else{
        return 1;
    }
}

template <class TC>
void BEShaper<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are best-effort frames
    if (msg->arrivedOn("in"))
    {
        // If there are framesRequested the MAC layer is currently idle
        if(TC::getNumPendingRequests())
        {
            TC::framesRequested--;
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
        }
        else
        {
            enqueueMessage(msg);
        }
    }
}

template <class TC>
void BEShaper<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("in")){
        beQueue.insert(msg);
        cComponent::emit(beQueueLengthSignal, beQueue.length());
        TC::notifyListeners();
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void BEShaper<TC>::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
    }
}

template <class TC>
cMessage* BEShaper<TC>::pop()
{
    Enter_Method("pop()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = (cMessage*) beQueue.pop();
        cComponent::emit(beQueueLengthSignal, beQueue.length());
        return message;
    }
    return TC::pop();
}

template <class TC>
cMessage* BEShaper<TC>::front()
{
    Enter_Method("front()");
    //BEFrames
    if (!beQueue.isEmpty())
    {
        cMessage* message = (cMessage*) beQueue.front();
        return message;
    }
    return TC::front();
}

template <class TC>
bool BEShaper<TC>::isEmpty()
{
    return beQueue.isEmpty() && TC::isEmpty();
}

template <class TC>
void BEShaper<TC>::clear()
{
    TC::clear();
    beQueue.clear();
}


}

#endif

