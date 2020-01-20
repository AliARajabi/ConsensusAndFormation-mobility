//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusMobilityBase.ned
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
//* description: Implementation of the module of the basic and constant layout of Consensus mobility model.
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


// To handles message broadcasting and processing and layout constant foundation for this type of mobility.


import inet.mobility.models.MobilityBase;


simple ConsensusMobilityBase extends MobilityBase
{
    parameters:
        double updateInterval @unit(s) = default(0.1s); // the simulation time interval used to regularly signal mobility state changes and update the display
        double observationWindowTime @unit(s) = default(0.2s); // observation window interval this parameter It has a great impact on system stablity.
        double broadcastInterval @unit(s) = default(0.1s); // broadcast message sending interval. with a decrease in this parameter and observation window, system stability increases.
        double startDelay @unit(s) = default(0s);  // start delay interval.
        
    gates:       
        input ApplLayerIn; // from application layer
        output ApplLayerOut; // to application layer
        input ApplControlIn; // control from application layer
        output ApplControlOut; // control to application layer
        
        
}
