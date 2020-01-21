/* -*- mode:c++ -*- ********************************************************
 * file:        ConsensusAndFormationMobility.cc
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


#include "ConsensusAndFormationMobility.h"
#include "FWMath.h"


Define_Module(ConsensusAndFormationMobility);


ConsensusAndFormationMobility::ConsensusAndFormationMobility()
{
    targetPosition = Coord::ZERO;
    Ui = Coord::ZERO;
    lastSpeed = Coord::ZERO;
    lastPosition = Coord::ZERO;
    virtualLeaderSpeed = Coord::ZERO;
    virtualLeaderPosition = Coord::ZERO;
    M = 0;
    Gama = 0;
    C = 0;
    kp = 0;
    kv = 0;
    maxSpeed =0;
}

ConsensusAndFormationMobility::~ConsensusAndFormationMobility()
{
    delete [] neighboursPosition;
    delete [] neighboursSpeed;

}

void ConsensusAndFormationMobility::initialize(int stage)
{
    ConsensusMobilityBase::initialize(stage);
    EV << "initializing ConsensusAndFormationMobility stage " << stage << endl;
    if (stage == 0)
    {
        // read physical parameters of the agent from ned file
        maxSpeed = par("maxSpeed");

        const char *mobilotyModel = par("MobilityType");
        const char *phisicalmodel = par("NodePhysicalModel");

        initialPositionX = par("initialPositionX").doubleValue();
        initialPositionY = par("initialPositionY").doubleValue();

        initialSpeedX = par("StartSpeedX").doubleValue();
        initialSpeedY = par("StartSpeedY").doubleValue();

        neighboursPosition = new Coord[nieghbourNum];
        neighboursSpeed = new Coord[nieghbourNum];

        targetPosition.x = par("formationPositionX");
        targetPosition.y = par("formationPositionY");

        virtualLeaderPosition.x = par("virtualLeaderPositionX");
        virtualLeaderPosition.y = par("virtualLeaderPositionY");

        virtualLeaderSpeed.x = par("virtualLeaderSpeedX");
        virtualLeaderSpeed.y = par("virtualLeaderSpeedY");

        M = par("M");
        Gama = par("Gama");
        C = par("C");
        kp = par("kp");
        kv = par("kv");

        initializeModel(phisicalmodel ,mobilotyModel);

    }else if(stage == 1){
        initializeSpeed();
        /* If the user does not determine initial position their initial position will Specify
         * randomly in the constraint area.
        */
        if(initialPositionX !=(-1) && initialPositionY !=(-1))
        {
            lastPosition.x = initialPositionX;
            lastPosition.y = initialPositionY;
        }

    }else if (stage == 2) {
        lastMove = simTime();
    }
}

void ConsensusAndFormationMobility::initializeSpeed()
{
    /* If the user does not determine initial speed their initial speed will Specify
     * randomly in the max speed Interval.
    */
 if(initialSpeedX ==(-1) || initialSpeedY ==(-1))
 {
     lastSpeed.x = dblrand()*maxSpeed/sqrt(2);
     lastSpeed.y = dblrand()*maxSpeed/sqrt(2);
 }else
 {
     lastSpeed.x = initialSpeedX;
     lastSpeed.y = initialSpeedY;
 }
}

void ConsensusAndFormationMobility::initializeModel(const char* Phisicalmodel ,const char*MobilotyModel) {
    if (!strcmp(Phisicalmodel, "first order")) {
        physicalModelType = FIRST_ORDER;
    } else if (!strcmp(Phisicalmodel, "second order")) {
        physicalModelType = SECOND_ORDER;
    } else {
        //physicalModelType = UNKNOWN;
        EV << "Error! Unknown physical model type: " <<endl;
        throw cRuntimeError(this,"physical model is wrong");
    }

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

void ConsensusAndFormationMobility::calculateParameters()
{
    switch (physicalModelType)
        {
            case FIRST_ORDER:
            {
                if(mobilityType == CONSENSUS)
                    // If the  physical model of agent Is considered first order and system objective is consensus.
                    calculateParameterConsensusFirst();
                else if(mobilityType == FORMATION)
                    // If the  physical model of agent Is considered first order and system objective is formation.
                    calculateParameterFormationFirst();
                else
                    EV << " type of mobility is wrong. " << endl;
            }
                break;
            case SECOND_ORDER:
            {
                if(mobilityType == CONSENSUS)
                    // If the  physical model of agent Is considered second order and system objective is consensus.
                    calculateParameterConsensusSecond();
                else if(mobilityType == FORMATION)
                    // If the  physical model of agent Is considered second order and system objective is formation.
                    calculateParameterFormationSecond();
                else
                    EV << " type of mobility is wrong. " << endl;
                       }
                break;
            default:
                EV << " type of physical model is wrong." << endl;
                break;
        }
}

/** @brief this function uses Ui=Sigma aij*(POSj-POSi),
 * to calculate control input of agent.
 **/

void  ConsensusAndFormationMobility::calculateParameterConsensusFirst()
{
    if(isStart)
     {
         //for now noting.
     }else
     {
         Coord TempSi_p= Coord::ZERO;
         for(unsigned int i = 0;i < nieghbourNum; i++)
         {
             Coord TempSi_s= Coord::ZERO;
             if(i!=Myindex && connectivityGraphMatrix[i]>0)
                 TempSi_s +=lastPosition - neighboursPosition[i];
             TempSi_p += TempSi_s;
         }

         Ui = TempSi_p;
     }
}

/** @brief this function uses Ui=Kp(LeaderPOS-POSi+FormPOSi)+Sigma aij*((POSj-FormPOSj)-(POSi-FormPOSi)),
 * to calculate control input of agent.
 **/

void  ConsensusAndFormationMobility::calculateParameterFormationFirst()
{
    if(isStart)
     {
         //for now noting.
     }else
     {
         Coord TempSi_p= Coord::ZERO;
         for(unsigned int i = 0;i < nieghbourNum; i++)
         {
             Coord TempSi_s= Coord::ZERO;
             if(i!=Myindex && connectivityGraphMatrix[i]>0)
                 TempSi_s +=lastPosition - targetPosition - neighboursPosition[i];
             TempSi_p += TempSi_s;
         }
         Ui = TempSi_p;
     }
}

/** @brief this function uses Ui=Sigma aij*((POSj-POSi)+Gama(SPEEPj-SPEEDi)),
 * to calculate control input of agent.
 **/
void  ConsensusAndFormationMobility::calculateParameterConsensusSecond()
{
    if(isStart)
     {
         //for now noting.
     }else
     {
         Coord TempSi_p= Coord::ZERO;
         for(unsigned int i = 0;i < nieghbourNum; i++)
         {
             Coord TempSi_s= Coord::ZERO;
             if(i!=Myindex && connectivityGraphMatrix[i]>0)
             {

                TempSi_s =lastSpeed - neighboursSpeed[i];
                TempSi_s *= Gama;
                TempSi_s +=lastPosition - neighboursPosition[i];
             }
             TempSi_p += TempSi_s;
         }

         Ui = TempSi_p;
     }
}

/** @brief this function uses Ui=+Kv(LeaderSPEED-SPEEDi)+Kp(LeaderPOS-POSi+FormPOSi)+Sigma aij*((POSj-FormPOSj)-(POSi-FormPOSi)+Gama(SPEEPj-SPEEDi)),
 * to calculate control input of agent.
 **/
void  ConsensusAndFormationMobility::calculateParameterFormationSecond()
{
    if(isStart)
     {
         //for now noting.
     }else
     {

         Coord tempSp=virtualLeaderSpeed-lastSpeed;
         tempSp *= Gama*kv;
         Coord tempPo=virtualLeaderPosition+targetPosition-lastPosition;
         tempPo *= kp;
         Coord TempSi_p= Coord::ZERO;
         for(unsigned int i = 0;i < nieghbourNum; i++)
         {
             Coord TempSi_s= Coord::ZERO;
             if(i!=Myindex && connectivityGraphMatrix[i]>0)
             {

                TempSi_s =lastSpeed - neighboursSpeed[i];
                TempSi_s *= Gama;
                TempSi_s +=lastPosition - targetPosition - neighboursPosition[i];
             }
             TempSi_p += TempSi_s;
         }

         TempSi_p *= C;
         TempSi_p += tempSp +tempPo;
         Ui = TempSi_p;
     }
}


void ConsensusAndFormationMobility::move()
{
    switch (physicalModelType)
            {
                case FIRST_ORDER:
                    // If the  physical model of agent Is considered first order.
                    firstOrderMove();
                    break;
                case SECOND_ORDER:
                    // If the  physical model of agent Is considered second order.
                    secondOrderMove();
                    break;
                default:
                    EV << " type of physical model is wrong." << endl;
                    break;
            }
}


/** @brief this function uses x(k+1)=x(k)+U(k),
 * to calculate next states of agent.
 **/
void ConsensusAndFormationMobility::firstOrderMove()
{
      double doubleUpdateInterval = (simTime() - lastMove).dbl();
      Coord tempSp=lastSpeed;
      tempSp *= doubleUpdateInterval;
      Coord tempAc=Ui;
      lastPosition=lastPosition + tempSp;

      Coord tempp= Coord::ZERO;
      lastSpeed = tempp - tempAc;

      //Reflect if we reach the borders
      Coord dummyCoord; double dummyAngle;
      handleIfOutside(REFLECT, dummyCoord, lastSpeed, dummyAngle);

      //If calculated speed is more than the maximum speed of agents it will be saturated.
      double speed = sqrt((lastSpeed.x*lastSpeed.x)+(lastSpeed.y*lastSpeed.y));
      if( speed > maxSpeed && lastSpeed != Coord::ZERO)
      {
          lastSpeed.x *= (maxSpeed/speed);
          lastSpeed.y *= (maxSpeed/speed);
      }

      lastMove = simTime();
      EV << " xpos = " << lastPosition.x << " ypos =" << lastPosition.y << " zpos =" << lastPosition.z << endl;
}


/** @brief this function uses x(k+1)=x(k)+v(k) and v(k+1)=v(k)+U(k)
 * to calculate next states of agent.
 **/
void ConsensusAndFormationMobility::secondOrderMove()
{
    double doubleUpdateInterval = (simTime() - lastMove).dbl();
    Coord tempSp=lastSpeed;
    tempSp *= doubleUpdateInterval;
    Coord tempAc=Ui;
    lastPosition=lastPosition + tempSp;

    tempAc *= doubleUpdateInterval;
    lastSpeed = lastSpeed - tempAc;

    //Reflect if we reach the borders
    Coord dummyCoord; double dummyAngle;
    handleIfOutside(REFLECT, dummyCoord, lastSpeed, dummyAngle);

    //If calculated speed is more than the maximum speed of agents it will be saturated.
    double speed = sqrt((lastSpeed.x*lastSpeed.x)+(lastSpeed.y*lastSpeed.y));
    if( speed > maxSpeed && lastSpeed != Coord::ZERO)
    {
        lastSpeed.x *= (maxSpeed/speed);
        lastSpeed.y *= (maxSpeed/speed);
    }

    lastMove = simTime();
    EV << " xpos = " << lastPosition.x << " ypos =" << lastPosition.y << " zpos =" << lastPosition.z << endl;
}


void ConsensusAndFormationMobility::prepareMessageConsensusFirst(FormPkt *msg)
{
    double Xpos=lastPosition.x;
    double Ypos=lastPosition.y;

    msg->setPositionX(Xpos);
    msg->setPositionY(Ypos);

}

/** since knowledge of neighbor position in, formation need an all-to-all communication.
 *  In this implantation, each agent Instead of sending its position sends (position - formation position).
 **/

void ConsensusAndFormationMobility::prepareMessageFormationFirst(FormPkt *msg)
{
    double Xpos=lastPosition.x;
    double Ypos=lastPosition.y;

    Xpos -= targetPosition.x;
    Ypos -= targetPosition.y;

    msg->setPositionX(Xpos);
    msg->setPositionY(Ypos);
}

void ConsensusAndFormationMobility::prepareMessageConsensusSecond(FormPkt *msg)
{
    double Xpos=lastPosition.x;
    double Ypos=lastPosition.y;

    msg->setPositionX(Xpos);
    msg->setPositionY(Ypos);

    msg->setSpeedX(lastSpeed.x);
    msg->setSpeedY(lastSpeed.y);

}

/** since knowledge of neighbor position in, formation need an all-to-all communication.
 *  In this implantation, each agent Instead of sending its position sends (position - formation position).
 **/

void ConsensusAndFormationMobility::prepareMessageFormationSecond(FormPkt *msg)
{
    double Xpos=lastPosition.x;
    double Ypos=lastPosition.y;

    Xpos -= targetPosition.x;
    Ypos -= targetPosition.y;

    msg->setPositionX(Xpos);
    msg->setPositionY(Ypos);

   msg->setSpeedX(lastSpeed.x);
   msg->setSpeedY(lastSpeed.y);
}

void ConsensusAndFormationMobility::prepareMessage(FormPkt *msg)
{
    switch (physicalModelType)
            {
                case FIRST_ORDER:
                {
                    if(mobilityType == CONSENSUS)
                    // If the  physical model of agent Is considered first order and system objective is consensus.
                    prepareMessageConsensusFirst(msg);
                else if(mobilityType == FORMATION)
                    // If the  physical model of agent Is considered first order and system objective is formation.
                    prepareMessageFormationFirst(msg);
                else
                    EV << " type of mobility is wrong. " << endl;
            }
                break;
            case SECOND_ORDER:
            {
                if(mobilityType == CONSENSUS)
                    // If the  physical model of agent Is considered second order and system objective is consensus.
                    prepareMessageConsensusSecond(msg);
                else if(mobilityType == FORMATION)
                    // If the  physical model of agent Is considered second order and system objective is formation.
                    prepareMessageFormationSecond(msg);
                else
                     EV << " type of mobility is wrong. " << endl;
                       }
                break;
            default:
                EV << " type of physical model is wrong." << endl;
                break;
        }
}


void ConsensusAndFormationMobility::firstOrderSaveStates(LAddress::L3Type nodeID,FormPkt *msg)
{
    neighboursPosition[nodeID].x=msg->getPositionX();
    neighboursPosition[nodeID].y=msg->getPositionY();
}

void ConsensusAndFormationMobility::secondOrderSaveStates(LAddress::L3Type nodeID,FormPkt *msg)
{
    neighboursPosition[nodeID].x=msg->getPositionX();
    neighboursPosition[nodeID].y=msg->getPositionY();

    neighboursSpeed[nodeID].x=msg->getSpeedX();
    neighboursSpeed[nodeID].y=msg->getSpeedY();
}

void ConsensusAndFormationMobility::saveStates(LAddress::L3Type nodeID,FormPkt *msg)
{
    switch (physicalModelType)
            {
                case FIRST_ORDER:
                    // If the  physical model of agent Is considered first order.
                    firstOrderSaveStates(nodeID,msg);
                    break;
                case SECOND_ORDER:
                    // If the  physical model of agent Is considered second order.
                    secondOrderSaveStates(nodeID,msg);
                    break;
                default:
                    EV << " type of physical model is wrong." << endl;
                    break;
            }
}

Coord ConsensusAndFormationMobility::getCurrentPosition()
{
    moveAndVisualize();
    return lastPosition;
}

Coord ConsensusAndFormationMobility::getFromationPosition()
{
    return targetPosition;
}

Coord ConsensusAndFormationMobility::getCurrentSpeed()
{
    moveAndVisualize();
    return lastSpeed;
}
