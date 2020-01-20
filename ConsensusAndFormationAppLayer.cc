/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormationAppLayer.cc
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
 * description: Implementation of the module of the base application layer of Consensus mobility model.
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
#include <ApplPkt_m.h>
#include <ccomponent.h>
#include <cenvir.h>
#include <cmessage.h>
#include <cmodule.h>
#include <cnamedobject.h>
#include <cobjectfactory.h>
#include <cpar.h>
#include <cregistrationlist.h>
#include <csimplemodule.h>
#include <ConsensusAndFormationAppLayer.h>
#include <INETDefs.h>
#include <NetwControlInfo.h>
#include <regmacros.h>
#include <simutil.h>
#include <SimpleAddress.h>
#include <sstream>

using std::endl;

Define_Module(ConsensusAndFormationAppLayer);


void ConsensusAndFormationAppLayer::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if(stage == 0) {
        lowerLayerIn  = findGate("lowerLayerIn");
        lowerLayerOut = findGate("lowerLayerOut");
        lowerControlIn  = findGate("lowerControlIn");
        lowerControlOut = findGate("lowerControlOut");

        mobilityControlIn  = findGate("mobilityControlIn");
        mobilityControlOut = findGate("mobilityControlOut");
        mobilityLayerIn  = findGate("mobilityLayerIn");
        mobilityLayerOut = findGate("mobilityLayerOut");

        headerLength = par("headerLength");

    }
}

/**
 * Decapsulates the packet from the received application packet
 **/
cMessage* ConsensusAndFormationAppLayer::decapsMsg(Applpkt_ptr_t msg)
{
    cMessage *m = msg->decapsulate();
    // delete the appl packet
    delete msg;
    return m;
}


/**
 * Encapsulates the received FormPkt into a ApplPkt and set all needed
 * header fields.
 **/
ConsensusAndFormationAppLayer::Applpkt_ptr_t ConsensusAndFormationAppLayer::encapsMsg(cPacket *FormPkt) {
    LAddress::L3Type applAddr = LAddress::L3BROADCAST;

    Applpkt_ptr_t pkt = new ApplPkt(FormPkt->getName(), FormPkt->getKind());
    pkt->setBitLength(headerLength);

    pkt->setSrcAddr(myAddr());
    pkt->setDestAddr(applAddr);

    // set the control info for network layer
    NetwControlInfo::setControlInfo(pkt, LAddress::L3BROADCAST );

    //encapsulate the application packet
    pkt->encapsulate(FormPkt);
    return pkt;
}


/**
 * this function send mobility message to network layer
 **/
void ConsensusAndFormationAppLayer::handleUpperMsg(cMessage* msg)
{
    assert(dynamic_cast<cPacket*>(msg));
    send(encapsMsg(static_cast<cPacket*>(msg)), lowerLayerOut);

}



/**
 * this function send mobility message to mobility module
 **/
void ConsensusAndFormationAppLayer::handleLowerMsg( cMessage* msg )
{
    Applpkt_ptr_t m = static_cast<Applpkt_ptr_t>(msg);
    const LAddress::L3Type& dest = m->getDestAddr();
    if (LAddress::isL3Broadcast(dest))
        send(decapsMsg(m), mobilityLayerOut);
    else
    {
        // do any thing
    }

}



void ConsensusAndFormationAppLayer::handleSelfMsg(cMessage *msg)
{
        EV <<" Unkown selfmessage! -> delete, kind: "<<msg->getKind()<<endl;
}

void ConsensusAndFormationAppLayer::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        handleSelfMsg(msg);
    } else if(msg->getArrivalGateId()==mobilityLayerIn) {
        handleUpperMsg(msg);
    } else if(msg->getArrivalGateId()==mobilityControlIn) {
        handleUpperControl(msg);
    } else if(msg->getArrivalGateId()==lowerControlIn){
        handleLowerControl(msg);
    } else if(msg->getArrivalGateId()==lowerLayerIn) {
        handleLowerMsg(msg);
    }
    else if(msg->getArrivalGateId()==-1) {
        /* Classes extending this class may not use all the gates, f.e.
         * BaseApplLayer has no upper gates. In this case all upper gate-
         * handles are initialized to -1. When getArrivalGateId() equals -1,
         * it would be wrong to forward the message to one of these gates,
         * as they actually don't exist, so raise an error instead.
         */
        opp_error("No self message and no gateID?? Check configuration.");
    } else {
        /* msg->getArrivalGateId() should be valid, but it isn't recognized
         * here. This could signal the case that this class is extended
         * with extra gates, but handleMessage() isn't overridden to
         * check for the new gate(s).
         */
        opp_error("Unknown gateID?? Check configuration or override handleMessage().");
    }
}

LAddress::L3Type ConsensusAndFormationAppLayer::myAddr()
{
   return LAddress::L3Type(this->getParentModule()->getIndex());
}

ConsensusAndFormationAppLayer::~ConsensusAndFormationAppLayer()
{
}

