/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormatioResult_loger.h
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
 * description: Implementation of the module that specifies the Consensus or formation time of the consensus mobility model.
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

#ifndef CONSENSUSANDFORMATIONRESULT_LOGER_H_
#define CONSENSUSANDFORMATIONRESULT_LOGER_H_

#include <coutvector.h>
#include <csimplemodule.h>
#include <ConsensusAndFormationMobility.h>

class Coord;

/**
 * @brief this implantation is a base module for recording consensus or formation
 * time for consensus and formation mobility. In consensus mobility, there is a
 * minor knowledge of all neighbors, so determining the exact time of consensus
 * or formation in each agent is impossible. in this case, for solving this issue
 * we define a module that continuously supervises all the agents and decides the
 * exact time of consensus or formation.  The formation(consensus) time for this
 * implementation is considered to be the time that all agents enter their
 * formation (consensus) location with the error specified with "positionThreshold"
 * in the ned file and remain in the formation(consensus) state.
 *
 *
 * @ingroup mobility
 * @ingroup ConsensusAndFormation Mobility
 * @author Ali Asghar Rajabi
 */

class ConsensusAndFormatioResult_loger :public cSimpleModule
{
protected:

  /** @brief The message Used for calculating agents' position in the formation(consensus). */
  cMessage *calcTimer;

  /** @brief The message Used for determining if all the agents remain in the formation(consensus). */
  cMessage *setTime;

  /** @brief The agent's positions. */
  Coord *nodesPosition;

  /** @brief Error threshold for position. */
  double positionThreshold;
  /** @brief determines if all the agents remained in the formation(consensus) threshold. */
  bool writed;
  /** @brief determines if all the agents entered the formation(consensus) threshold. */
  bool started;
  /** @brief show the formation time. */
  double formationTime;
  /** @brief show the consensus time. */
  double consensusTime;
  /** @brief determines the mobility type of the agents. */
  int mobilityType;
  /** @brief Number of nodes existing. */
  unsigned int nodeNum;


  /** @brief The vector for displaying agent's x-positions trajectory. */
  cOutVector XPositionTrajectory;
  /** @brief The vector for displaying agent's x-positions trajectory. */
  cOutVector YPositionTrajectory;
  /** @brief The vector for displaying the up  threshold for position errors . */
  cOutVector position_up_threshold;
  /** @brief The vector for displaying the down threshold for position errors . */
  cOutVector position_down_threshold;

  /** @brief the objective of the system in the agent's last position.*/
  enum MOBILITY_TYPES
          {
      CONSENSUS = 0 , FORMATION ,
          };



public:
  /** @brief Construct a Consensus mobility base  object.  */
  ConsensusAndFormatioResult_loger();

  ~ConsensusAndFormatioResult_loger(){};

  /** @brief Initializes mobility model parameters.*/
  virtual void initialize();

protected:

  /** @brief Called every time a message arrives*/
  virtual void handleMessage(cMessage *message);

  /** @brief Handle self messages such as timer... */
  virtual void handleSelfMessage(cMessage *message);

  /** @brief calculates agents' position in the formation(consensus)
   *  and determine if they entered the formation(consensus) threshold.
  */
  virtual void calculateDistance();

  /** @brief Initializes the mobility type of agents.*/
  virtual void initializeModel(const char*);

  virtual void finish();

};



#endif /* CONSENSUSANDFORMATIONRESULT_LOGER_H_ */
