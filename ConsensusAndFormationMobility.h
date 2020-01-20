/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormationMobility.h
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
 * description: Implementation of the module of the Consensus and formation mobility model
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
#ifndef CONSENSUSANDFORMATIONMOBILITY_H_
#define CONSENSUSANDFORMATIONMOBILITY_H_


#include "INETDefs.h"
#include "ConsensusMobilityBase.h"


/**
 * @brief to calculate control input, next position and next speed of the agent and handle
 *  broadcast messaging, according to physical type and mobility type.
 * This is the mobility module of Consensus and formation. It should be instantiated in each  that belongs to a Consensus or formation.
 * The NED parameter "PhysicalModel" determines the physical model that considers for agents and Can be one of the first order or the second order.
 * The NED parameter "MobilityType" determines the objective that considers for the system and can be one of formation or consensus.
 * The current implantation uses "ConsensusMobilityBase" for the timing of messaging and movement.
 * The current implantation uses the physical equation of "Frank L. Lewis. Cooperative Control of Multi-Agent Systems Optimal and Adaptive Design Approaches" for agents.
 *
 * @ingroup mobility
 * @ingroup ConsensusAndFormation Mobility
 * @author Ali Asghar Rajabi
 */


class ConsensusAndFormationMobility : public ConsensusMobilityBase
{
  protected:
    /** @brief The last speed that was reported at lastUpdate. */
        Coord lastSpeed;
    /** @brief The  position in formation relative to virtual leader. */
        Coord targetPosition;
    /** @brief The control input of  that calculated. */
        Coord Ui;
    /** @brief The virtual leader speed. */
        Coord virtualLeaderSpeed;
    /** @brief The virtual leader position. */
        Coord virtualLeaderPosition;
    /** @brief The neighbors position. */
        Coord *neighboursPosition;
    /** @brief The neighbors speed. */
        Coord *neighboursSpeed;

    /** @brief The simulation time when the mobility state was last updated. */
        simtime_t lastMove;

    /** @brief the objective of the system in the agent's last position.*/
        enum MOBILITY_TYPES
                {
            CONSENSUS = 0 , FORMATION ,
                };

    /** @brief the physical model of agents.*/
        enum PHYSICALMODEL_TYPES
                {
            FIRST_ORDER = 0, SECOND_ORDER ,
                };

        /** @brief the agent's mobility type. */
        int physicalModelType;
        /** @brief the agent's physical model. */
        int mobilityType;

        /** @brief physical parameters:*/
        /*@{*/
        double M;
        double Gama;
        double C;
        double kp;
        double kv;

        double initialPositionX;
        double initialPositionY;

        double initialSpeedX;
        double initialSpeedY;

        double maxSpeed;
        /*@}*/

  public:
    /** @brief Construct a Consensus mobility base  object.  */
    ConsensusAndFormationMobility();

    virtual ~ConsensusAndFormationMobility();

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int stage);

  protected:

    /** @brief Initializes the speed of agents. */
    virtual void initializeSpeed();

    /** @brief Initializes the mobility type and agent's physical type.*/
    virtual void initializeModel(const char* ,const char*);


    /** @brief calculate the control input of the agents. */
    virtual void calculateParameters();

    /** @brief calculate the control input of the first order agents for consensus. */
    virtual void  calculateParameterConsensusFirst();

    /** @brief calculate the control input of the first order agents for formation. */
    virtual void  calculateParameterFormationFirst();

    /** @brief calculate the control input of the second order agents for consensus. */
    virtual void  calculateParameterConsensusSecond();

    /** @brief calculate the control input of the second order agents for formation. */
    virtual void  calculateParameterFormationSecond();


    /** @brief prepare broadcast message of the agents with according states. */
    virtual void prepareMessage(FormPkt *);

    /** @brief prepare broadcast message of the first order agents for consensus. */
    virtual void prepareMessageConsensusFirst(FormPkt *);

    /** @brief prepare broadcast message of the first order agents for formation. */
    virtual void prepareMessageFormationFirst(FormPkt *);

    /** @brief prepare broadcast message of the second order agents for consensus. */
    virtual void prepareMessageConsensusSecond(FormPkt *);

    /** @brief prepare broadcast message of the second order agents for formation. */
    virtual void prepareMessageFormationSecond(FormPkt *);


    /** @brief save neighbors state with received broadcast messages. */
    virtual void saveStates(LAddress::L3Type,FormPkt *);

    /** @brief save neighbors state of the first order agents. */
    virtual void firstOrderSaveStates(LAddress::L3Type,FormPkt *);

    /** @brief save neighbors state of the second order agents. */
    virtual void secondOrderSaveStates(LAddress::L3Type,FormPkt *);


    /** @brief Move the agents according to the current simulation time. */
    virtual void move();

    /** @brief Move the first order agents. */
    virtual void firstOrderMove();

    /** @brief Move the second order agents. */
    virtual void secondOrderMove();

public:

    /** @brief Returns the formation position of the agent. */
    virtual Coord getFromationPosition();

    /** @brief Returns the current position at the current simulation time. */
    virtual Coord getCurrentPosition();

    /** @brief Returns the current speed at the current simulation time. */
    virtual Coord getCurrentSpeed();

};


#endif /* CONSENSUSANDFORMATIONMOBILITY_H_ */
