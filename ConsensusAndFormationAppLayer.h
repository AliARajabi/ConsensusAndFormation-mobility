/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormationAppLayer.h
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

#ifndef CONSENSUSANDFORMATIONAPPLAYER_H_
#define CONSENSUSANDFORMATIONEAPPLAYER_H_

#include <assert.h>
#include "BaseLayer.h"
#include "MiXiMDefs.h"
#include "Coord.h"
#include "ConsensusMobilityBase.h"
#include <cenvir.h>
#include <cmessage.h>
#include <coutvector.h>
#include <csimplemodule.h>
#include <INETDefs.h>
#include <SimpleAddress.h>

class ApplPkt;
class Coord;
class ConsensusMobilityBase;
class FormPkt;

/**
 * @brief this implantation is a base application layer for consensus mobility.
 * In consensus mobility knowledge of neighbors, states have a great impact on system stability,
 * so in this case, any agent sends its states trough broadcast message for neighbors.
 * This layer acts as a middle layer between the network layer and the mobility module.
 *
 * @ingroup mobility
 * @ingroup ConsensusAndFormation Mobility
 * @author Ali Asghar Rajabi
 */


class  ConsensusAndFormationAppLayer : public cSimpleModule
{
protected:

    /** @name gate ids*/
    /*@{*/
    int mobilityControlIn;
    int mobilityControlOut;
    int mobilityLayerIn;
    int mobilityLayerOut;

    int lowerLayerIn;
    int lowerLayerOut;
    int lowerControlIn;
    int lowerControlOut;
    /*@}*/

    /** @brief Length of the FormPkt header*/
   int headerLength;

    /** @brief application packet pointer type. */
    typedef ApplPkt* Applpkt_ptr_t;

public:

    /** @brief Construct a Consensus anf formation mobility base  object.*/
    ConsensusAndFormationAppLayer()
        : cSimpleModule()
    {}

    virtual ~ConsensusAndFormationAppLayer();

    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);

protected:

    /** @brief Called every time a message arrives*/
    void handleMessage(cMessage*);

    /** @brief Handle self messages such as timer... */
    virtual void handleSelfMsg(cMessage*);

    /** @brief Handle messages from appl layer */
    virtual void handleLowerMsg(cMessage*);

    /** @brief Handle control messages from appl layer*/
    virtual void handleLowerControl(cMessage* msg) {
        EV << "ConsensusAndFormatioAppLayer: in this case, there is no need for the lower control message.; delete msg\n";
        delete msg;
    }

    /** @brief Handle control messages from upper layer */
    virtual void handleUpperControl(cMessage *msg) {
        EV << "ConsensusAndFormatioAppLayer: mobility module has no control message yet; delete message\n";
        delete msg;
    }

    /** @brief Handle messages from mobility module */
    virtual void handleUpperMsg(cMessage*);


    /** @brief decapsulate lower layer message from NetwPkt */
    virtual cMessage*decapsMsg(Applpkt_ptr_t);

    /** @brief Encapsulate higher layer packet into an ApplPkt*/
    virtual Applpkt_ptr_t encapsMsg(cPacket*);


    /**
    * @brief Return my application layer address
    *
    * We use the node module index as application address
    **/
    virtual LAddress::L3Type myAddr();
};



#endif /* CONSENSUSANDFORMATIONAPPLAYER_H_ */
