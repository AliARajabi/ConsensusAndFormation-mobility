/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusMobilityBase.h
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
 * description: Implementation of the module of the basic and constant layout of Consensus mobility model.
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

#ifndef CONSENSUSMOBILITYBASE_H_
#define CONSENSUSMOBILITYBASE_H_


#include <MobilityBase.h>
#include <simtime_t.h>
#include <SimpleAddress.h>
#include "ApplPkt_m.h"
#include "FormPkt_m.h"



class ApplPkt;
class FormPkt;

/**
 * @brief to handles message broadcasting and processing and layout constant foundation for this type of mobility.
 *
 *
 * @ingroup mobility
 * @ingroup ConsensusAndFormation Mobility
 * @author Ali Asghar Rajabi
 */
class ConsensusMobilityBase : public MobilityBase
{
  protected:

    /** @brief The message Used for motion scheduling. */
    cMessage *moveTimer;
    /** @brief The message used to determine the delay in starting the move to ensure that all packets are received before the move begins and the correct formation of the neighborhood matrix. */
    cMessage *startdelay;
    /** @brief The message used to scheduling broadcast of agents states message.*/
    cMessage *broadcastTimer;
    /** @brief The message used to schedule the beginning of the next window and calculation of neighbor matrix and other mobility parameters. */
    cMessage * matrixcalculation;

    /** @brief The simulation time interval used for motion scheduling. */
    simtime_t updateInterval;
    /** @brief The simulation time interval used to Specify the period of calculation of the neighborhood matrix and the parameters of the physical model of the agents */
    simtime_t observationWindowTime;
    /** @brief The simulation time interval used to broadcast agents states.*/
    simtime_t broadcastInterval;
    /** @brief The simulation time interval used to determine the delay in starting the move. */
    simtime_t startdelayTime;
    /** @brief The simulation time when the mobility state was last updated. */
    simtime_t lastUpdate;
    /** @brief The next simulation time when the mobility module needs to update its internal state. */
    simtime_t nextChange;

    /** @brief application packet pointer type. */
    typedef ApplPkt* appkt_ptr_t;
    /** @brief mobility packet pointer type. */
    typedef FormPkt* Formpkt_ptr_t;

    /** @brief Message kinds used by this layer.*/
    enum TestApplMessageKinds {
        BROADCAST_MESSAGE=50
    };


    /** @name gate ids*/
    /*@{*/
    int ApplLayerIn; // data from application layer
    int ApplLayerOut; // data to application layer
    int ApplControlIn; // control from application layer
    int ApplControlOut; // control to application layer
    /*@}*/

    /** @brief Number of nodes existing. */
    unsigned int nieghbourNum;
    /** @brief index on node. */
    unsigned int Myindex;
    /** @brief PRR value for each link. */
    double *Prr;
    /** @brief The number of packets received from each neighbor in the last window. */
    double *nPackets;
    /** @brief the value that determines if it is the start of the mobility process. */
    bool isStart;
    /** @brief The corresponding row of the node in the neighbor matrix. */
    double *connectivityGraphMatrix;
    /** @brief The number of packets received from each neighbor in the last window. */
    int *neighboursMsgCount;


  public:
    /** @brief Construct a Consensus mobility base  object.  */
    ConsensusMobilityBase();

    virtual ~ConsensusMobilityBase();

    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int stage);

  protected:

    /** @brief Returns the required number of initialize stages. */
    virtual int numInitStages() const {return 3;}


    /** @brief Called every time a message arrives*/
    virtual void handleMessage(cMessage *message);

    /** @brief Handle self messages such as timer... */
    virtual void handleSelfMessage(cMessage *message);

    /** @brief Handle messages from application layer */
    virtual void handleApplMsg(cMessage *);

    /** @brief Handle control messages from application layer */
    virtual void handleApplControl(cMessage *);


    /** @brief calculate neighborhood matrix. */
    virtual void calculateMatrix();

    /** @brief calculate physical model parameters like control input according to the agent and its neighbor states. */
    virtual void calculateParameters() = 0;

    /** @brief prepare broadcast message according to agent physical model and mobility type. */
    virtual void prepareMessage(FormPkt *)=0;

    /** @brief save received message data according to agent physical model and mobility type. */
    virtual void saveStates(LAddress::L3Type,FormPkt *)=0;

    /** @brief caculate prr for the last window */
    virtual void calculatePrr();


    /** @brief Schedules the move timer. */
    virtual void scheduleMobility();

    /** @brief Moves and Visualize the representation. */
    virtual void moveAndVisualize();

    /** @brief Moves according to the mobility model to the current simulation time.
     *
     * Subclasses must override and update lastPosition, lastSpeed, lastUpdate, nextChange
     * and other state according to the mobility model.
     */
    virtual void move() = 0;


    /** @brief broadcast agent states according to agent physical model and mobility type. */
   void sendBroadcast();

};


#endif /* CONSENSUSMOBILITYBASE_H_ */
