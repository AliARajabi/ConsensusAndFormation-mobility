/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusMobilityBase.cc
 *
 * author:      Ali Asghar Rajabi <aa.rajabi@ec.iut.ac.ir>
 *
 *
 *              https://ece.iut.ac.ir/en/taxonomy/term/21
 *
 * copyright:
 *
 *
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:    Consensus and formation (Mobility Model for multi-agent consensus and formation control)
 * description: A class that handles message broadcasting and processing and layout constant foundation for this type of mobility.
 ***************************************************************************
 * Citation of the following publication is appreciated if you use ConsensusAndFormation for
 * a publication of your own.
 *
 *
 *
 * BibTeX:
 *
 *
 **************************************************************************/



#include <cenvir.h>
#include <cexception.h>
#include <cmessage.h>
#include <cmodule.h>
#include <cpar.h>
#include <csimplemodule.h>
#include <csimulation.h>
#include <random.h>
#include <simtime.h>
#include <SimpleAddress.h>
#include <ConsensusMobilityBase.h>
#include <sstream>
#include <string>

ConsensusMobilityBase::ConsensusMobilityBase()
{
    moveTimer = NULL;
    startdelay = NULL;
    broadcastTimer = NULL;
    updateInterval = 0;
    lastUpdate = 0;
    nextChange = -1;
    isStart=true;
    Myindex=0;
}

ConsensusMobilityBase::~ConsensusMobilityBase()
{
    cancelAndDelete(moveTimer);
    cancelAndDelete(broadcastTimer);
    delete [] neighboursMsgCount;
    delete [] nPackets;
    delete [] Prr;
}


void ConsensusMobilityBase::initialize(int stage)
{
    MobilityBase::initialize(stage);
    EV << "initializing MovingMobilityBase stage " << stage << endl;
    if (stage == 0) {
        //// timers:
        moveTimer = new cMessage("move");
        matrixcalculation = new cMessage("start windows calculation");
        broadcastTimer = new cMessage("broadcast Timer");
        //// end of timers.

        //// read ned file parameters
        nieghbourNum=getParentModule()->par("numHosts");
        updateInterval = par("updateInterval");
        observationWindowTime = par("observationWindowTime");
        broadcastInterval = par("broadcastInterval");
        startdelayTime  = par("startDelay");
        //// end of ned file parameters

        //// handle gates
        ApplLayerIn = findGate("ApplLayerIn");
        ApplLayerOut= findGate("ApplLayerOut");
        ApplControlIn = findGate("ApplControlIn");
        ApplControlOut = findGate("ApplControlOut");
        //// end of gates

        Myindex=this->getParentModule()->getIndex();

        nPackets = new double[nieghbourNum];
        Prr = new double[nieghbourNum];
        neighboursMsgCount = new int[nieghbourNum];
        for (unsigned int j=0;j<nieghbourNum;j++){
            nPackets[j] = 0.00;
            Prr[j] = 0.00;
            neighboursMsgCount[j] = 0.00;
        }
        connectivityGraphMatrix = new double[nieghbourNum];


    }
    else if (stage == 2) {
        move();
        lastUpdate = simTime();
        emitMobilityStateChangedSignal();
        updateVisualRepresentation();
        scheduleMobility();

        /* If a delay is initially considered, it will be applied, otherwise,
         *  the end of the first observation window is applied according to the entered value.
        */
        if(startdelayTime != 0.00)
        {
            startdelay = new cMessage("start delay");
            scheduleAt(simTime()+ startdelayTime, startdelay);
        }else
            scheduleAt(simTime()+observationWindowTime, matrixcalculation);

        scheduleAt(simTime() + dblrand(), broadcastTimer);
    }

}


void ConsensusMobilityBase::moveAndVisualize()
{
    simtime_t now = simTime();
    if (nextChange == now || lastUpdate != now) {
        move();
        lastUpdate = simTime();
        emitMobilityStateChangedSignal();
        updateVisualRepresentation();
    }
}
void ConsensusMobilityBase::calculateMatrix()
{
    if(isStart)
        isStart=false;
    /* any agent that we received at least one message from it in
     * the previous observation window considered as a neighbor
     * and its corresponding element in the neighborhood matrix
     *equals one.
     *equals */
    for(unsigned int i = 0;i < nieghbourNum; i++)
    {
        connectivityGraphMatrix[i]=0;
        if(i!=Myindex){
            if (neighboursMsgCount[i]>0)
                connectivityGraphMatrix[i] = 1;
            else
                connectivityGraphMatrix[i] = 0;
        }
        neighboursMsgCount[i]=0;
    }
    calculateParameters();
}

/*PRR:
 * This criterion shows the rate of the number of packets received successfully to all the sent packets.
 */
void ConsensusMobilityBase::calculatePrr() {
    double temp_prr;
    for (unsigned int i=0;i<nieghbourNum;i++){
        if (i != Myindex){
        temp_prr=nPackets[i]*broadcastInterval.dbl()/observationWindowTime.dbl();
        Prr[i]=temp_prr;
        nPackets[i]=0;
        }
    }
}

void ConsensusMobilityBase::sendBroadcast()
{
    FormPkt *pkt = new FormPkt("BROADCAST_MESSAGE", BROADCAST_MESSAGE);
    pkt->setDestAddr(LAddress::L3BROADCAST);
    // we use the host modules getIndex() as a appl address
    pkt->setSrcAddr( LAddress::L3Type( this->getParentModule()->getIndex()));

    prepareMessage(pkt);
    // end the broadcast message to the lower layer.
    send(pkt, ApplLayerOut);
}

void ConsensusMobilityBase::handleSelfMessage(cMessage *message)
{
    /*If a delay is initially considered, it clear neighboursMsgCount
     * for the delay time to increase the accuracy of the neighborhood matrix.
     */
    if(message==startdelay){
           calculatePrr();
        for(unsigned int j=0;j<nieghbourNum;j++){
            neighboursMsgCount[j] = 0.00;
        }
        scheduleAt(simTime()+observationWindowTime, matrixcalculation);
        cancelAndDelete(startdelay);
   }else if(message==moveTimer){
       /*At the beginning of the window, the neighborhood matrix
        * will be calculated and then the control input.
        */
       moveAndVisualize();
       scheduleMobility();
   }else if(message==broadcastTimer){
       scheduleAt(simTime() + broadcastInterval, broadcastTimer);
       sendBroadcast();
   }else if(message==matrixcalculation){
       /*first agent's next position and speed will be determined and then
        * visual representation updates and next move time will schedule.
        */
       scheduleAt(simTime()+observationWindowTime, matrixcalculation);
       calculatePrr();
       calculateMatrix();
   }else
       EV << "CSMA Error: unknown timer fired:" << message << endl;
}



void ConsensusMobilityBase::handleApplMsg(cMessage *msg)
{

    Formpkt_ptr_t formMsg = static_cast<Formpkt_ptr_t>(msg);

    const LAddress::L3Type& dest = formMsg->getDestAddr();

        if (LAddress::isL3Broadcast(dest)) {

            LAddress::L3Type nodeID = formMsg->getSrcAddr();

            saveStates(nodeID,formMsg);
            neighboursMsgCount[nodeID] = neighboursMsgCount[nodeID] +1;
            nPackets[nodeID]=nPackets[nodeID]+1;

        }
        else
        {
            std::stringstream convrecievedpacket;
            convrecievedpacket <<"addresses don't match and adress is  "<<dest<<" .";
            std::string srecievedpacket = convrecievedpacket.str();
            const char *chrecievedpacket=srecievedpacket.c_str();
            throw cRuntimeError(this,chrecievedpacket);

        }
        delete msg;
    }




void ConsensusMobilityBase::handleApplControl(cMessage *msg)
{
    //In this case, there is no need for this part, but it can be redefined for other purposes.
}


void ConsensusMobilityBase::handleMessage(cMessage * message)
{
    if (message->isSelfMessage())
        handleSelfMessage(message);
    else if(message->getArrivalGateId()==ApplControlIn)
        handleApplControl(message);
    else if(message->getArrivalGateId()==ApplLayerIn)
        handleApplMsg(message);
    else
        EV << "The received gate is unknown." << endl;
}

void ConsensusMobilityBase::scheduleMobility()
{
    cancelEvent(moveTimer);
    if ( updateInterval != 0) {
        simtime_t nextUpdate = simTime() + updateInterval;
        if (nextChange != -1 && nextChange < nextUpdate)
            scheduleAt(nextChange, moveTimer);
        else
            scheduleAt(nextUpdate, moveTimer);
    }
    else if (nextChange != -1)
        scheduleAt(nextChange, moveTimer);
}



