//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusAndFormation.ned
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
//* description: Implementation of network with the agents and the result loger.
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

import org.mixim.base.modules.BaseNetwork;


network ConsensusAndFormation extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network

    submodules:
        node[numNodes]: ConsensusAndFormationNode;
        resultLoger: ConsensusAndFormatioResult_loger {
            @display("p=113,0");
        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}
