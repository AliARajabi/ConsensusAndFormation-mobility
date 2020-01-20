//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusAndFormationMobility.ned
//*
//* author:      Ali Asghar Rajabi <aa.rajabi@ec.iut.ac.ir>
//*
//*
//*              https://ece.iut.ac.ir/en/taxonomy/term/21
//*
//* copyright:
//*
//*
//*
//*              This program is free software; you can redistribute it
//*              and/or modify it under the terms of the GNU General Public
//*              License as published by the Free Software Foundation; either
//*              version 2 of the License, or (at your option) any later
//*              version.
//*              For further information see file COPYING
//*              in the top level directory
//***************************************************************************
//* part of:    Consensus and formation (Mobility Model for multi-agent consensus and formation control)
//* description: Implementation of the module of the Consensus and formation mobility model
//***************************************************************************
//* Citation of the following publication is appreciated if you use ConsensusAndFormation for
//* a publication of your own.
//*
//*
//*
//* BibTeX:
//*
//*
//**************************************************************************/

package ConsensusAndFormation;

// To calculate control input, next position and next speed of the agent and handle
//  broadcast messaging, according to physical type and mobility type.
// This is the mobility module of Consensus and formation. It should be instantiated in each  that belongs to a Consensus or formation.
// The NED parameter "PhysicalModel" determines the physical model that considers for agents and Can be one of the first order or the second order.
// The NED parameter "MobilityType" determines the objective that considers for the system and can be one of formation or consensus.
// The current implantation uses "ConsensusMobilityBase" for the timing of messaging and movement.
// The current implantation uses the physical equation of "Frank L. Lewis. Cooperative Control of Multi-Agent Systems Optimal and Adaptive Design Approaches" for agents.


simple ConsensusAndFormationMobility extends ConsensusMobilityBase
{
    parameters:
        
        string MobilityType = default("consensus");  	// Can be one of: formation or consensus
		string NodePhysicalModel = default("first order");  	// Can be one of: first order or second order
        
        double maxSpeed  = default(30); // maximum speed of agents.
        // node position and speed
		double initialPositionX @unit(m) = default(-1 m); // node initial x-position
		double initialPositionY @unit(m) = default(-1 m); // node initial y-position


		double StartSpeedX @unit(mps) = default(-1mps);  // node initial x-speed
		double StartSpeedY @unit(mps) = default(-1mps);  // node initial y-speed


        double virtualLeaderPositionX @unit(m);  //virtual leadre initial x-position
        double virtualLeaderPositionY @unit(m);  //virtual leadre initial y-position

        double formationPositionX @unit(m); // node x-position in formation
        double formationPositionY @unit(m); // node y-position in formation

        double virtualLeaderSpeedX @unit(mps);  //virtual leadre initial x-speed
        double virtualLeaderSpeedY @unit(mps);  //virtual leadre initial y-speed

		//physical parameters:
        double M @unit(g) = default(1250g);  //weight of the agent.
        double Gama;  //damping gain of the agent.
        double C = default(1);  //stiffness gain of the agent.
        double kp = default(0); //position feedback  gain of the agent.
        double kv = default(0); //velocity feedback gain of the agent.
        
        @class(ConsensusAndFormationMobility);
}