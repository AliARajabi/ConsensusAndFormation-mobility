//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusAndFormationAppLayer.ned
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
//* description: Implementation of the module of the base application layer of Consensus mobility model.
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

// This implantation is a base application layer for consensus mobility.
// in consensus mobility knowledge of neighbors, states have a great impact on system stability,
// so in this case, any agent sends its states trough broadcast message for neighbors.
// This layer acts as a middle layer between the network layer and the mobility module.

simple ConsensusAndFormationAppLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
    gates:
        input lowerLayerIn; // from network layer
        output lowerLayerOut; // to network layer
        input lowerControlIn; // control from network layer
        output lowerControlOut; // control to network layer

        input mobilityLayerIn; // from mobility module
        output mobilityLayerOut; // to mobility module
        input mobilityControlIn; // control from mobility module
        output mobilityControlOut; // control to mobility module
}
