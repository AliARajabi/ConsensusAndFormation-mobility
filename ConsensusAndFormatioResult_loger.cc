/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormatioResult_loger.cc
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


#include <cenvir.h>
#include <cexception.h>
#include <cmessage.h>
#include <cobjectfactory.h>
#include <coutvector.h>
#include <cownedobject.h>
#include <cpar.h>
#include <cregistrationlist.h>
#include <csimulation.h>
#include <distrib.h>
#include <ConsensusAndFormationMobility.h>
#include <INETDefs.h>
#include <regmacros.h>
#include <ConsensusAndFormatioResult_loger.h>
#include <simtime.h>
#include <simutil.h>
#include <stddef.h>
#include <iostream>

Define_Module(ConsensusAndFormatioResult_loger);

ConsensusAndFormatioResult_loger::ConsensusAndFormatioResult_loger()
{
    calcTimer = NULL;
    setTime = NULL;
    positionThreshold = 0;
    writed = false;
    started = false;
    formationTime = -1;
    nodeNum = 0;
}


void ConsensusAndFormatioResult_loger::initialize()
{
    //// read ned file parameters
    positionThreshold = par("positionThreshold").doubleValue();

    writed = false;
    started = false;
    formationTime = -1;

    //// timers:
    calcTimer = new cMessage("calculate distance");
    setTime = new cMessage("set Consensus or Formation time");
    //// end of timers.

    nodeNum = getParentModule()->par("numNodes");
    nodesPosition = new Coord[nodeNum];

    // naming the cout vectors
    XPositionTrajectory.setName("X Position Trajectory of nodes in Consensus or Formation");
    YPositionTrajectory.setName("Y Position Trajectory of nodes in Consensus or Formation");
    position_up_threshold.setName(" upper threshold of positions ");
    position_down_threshold.setName(" lower threshold of positions ");

   const char *mobilotyModel = getParentModule()->getSubmodule("node",0)->getSubmodule("mobility")->par("MobilityType");
   initializeModel(mobilotyModel);

   scheduleAt(simTime()+0.1, calcTimer);
}

void ConsensusAndFormatioResult_loger::initializeModel(const char*MobilotyModel) {
    if (!strcmp(MobilotyModel, "consensus")) {
            mobilityType = CONSENSUS;
        } else if (!strcmp(MobilotyModel, "formation")) {
            mobilityType = FORMATION;
        } else {
            //mobilityType = UNKNOWN;
            EV << "Error! Unknown physical model type: " <<endl;
            throw cRuntimeError(this,"mobility model is wrong");
        }
}

/** @brief in formation(consensus) all agent desire to a known position,
 *  so if we subtract this position from the last position it will approach zero.
 *   This function with doing this action for all agent and adding error value
 *   determine if agents entered in threshold position and record this time as formation(consensus) time.
 *   If agents remain in this threshold for 10 second formation time will record in results.
 **/
void ConsensusAndFormatioResult_loger::calculateDistance()
{
    for (unsigned int i = 0;i < nodeNum; i++)
    {
        ConsensusAndFormationMobility *mod = check_and_cast<ConsensusAndFormationMobility *>(this->getParentModule()->getSubmodule("node",i)->getSubmodule("mobility"));
        Coord position = mod->getCurrentPosition();
        if(mobilityType == FORMATION){
        Coord formationPosition = mod->getFromationPosition();
        nodesPosition[i] = position - formationPosition;
        }else
            nodesPosition[i] = position;
    }

    double xpos = 0.00;
    double ypos = 0.00;
    for (unsigned int count = 1;count<nodeNum;count++){
        xpos += nodesPosition[0].x - nodesPosition[count].x;
        ypos += nodesPosition[0].y - nodesPosition[count].y;
    }

    XPositionTrajectory.record(xpos);
    YPositionTrajectory.record(ypos);

    position_up_threshold.record(positionThreshold);
    position_down_threshold.record(-positionThreshold);

    if(xpos*ypos<0)
         ypos *= -1;

   double posErr = xpos+ypos;
    if(!writed){
        if(!started){
            if(posErr<positionThreshold && posErr>-positionThreshold){
                if(mobilityType == FORMATION)
                    formationTime = simTime().dbl();
                else
                    consensusTime = simTime().dbl();
                scheduleAt(simTime()+10, setTime);
                started = true;
            }
        }else{
            if(posErr>20 || posErr<-20){
                formationTime = -1;
                cancelEvent(setTime);
                started = false;
            }
        }
    }
}


void ConsensusAndFormatioResult_loger::handleSelfMessage(cMessage *message)
{
    if(message==calcTimer){
           scheduleAt(simTime()+ 0.1, calcTimer);
           calculateDistance();
       }else if(message==setTime){
                  writed = true;
       }else
           EV << "CSMA Error: unknown timer fired:" << message << endl;
}
void ConsensusAndFormatioResult_loger::handleMessage(cMessage * message)
{
    if (message->isSelfMessage())
        handleSelfMessage(message);
    else
            throw cRuntimeError("Mobility modules can only receive self messages");
}

 void ConsensusAndFormatioResult_loger::finish()
{
     if(mobilityType == FORMATION)
         recordScalar("formation time", formationTime);
     else
         recordScalar("consensus time", consensusTime);

     cancelAndDelete(calcTimer);
     cancelAndDelete(setTime);
}
