//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusAndFormatioResult_loger.ned
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
//* description: Implementation of the module that specifies the Consensus or formation time of the consensus mobility model.
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


// This implantation is a base module for recording consensus or formation
// time for consensus and formation mobility. In consensus mobility, there is a
// minor knowledge of all neighbors, so determining the exact time of consensus
// or formation in each agent is impossible. in this case, for solving this issue
// we define a module that continuously supervises all the agents and decides the
// exact time of consensus or formation.  The formation(consensus) time for this
// implementation is considered to be the time that all agents enter their
// formation (consensus) location with the error specified with "positionThreshold"
// in the ned file and remain in the formation(consensus) state.


simple ConsensusAndFormatioResult_loger
{
	parameters:
	    @display("bgb=210,450,white;i=block/table2");
	    double positionThreshold; // Error treshlod for position 
}