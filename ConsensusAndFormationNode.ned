//* -*- mode:c++ -*- ********************************************************
//* file:        ConsensusAndFormationNode.ned
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
//* description: Implementation of the module of the agent of Consensus mobility model.
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

import org.mixim.base.modules.IBaseArp;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.nic.IWirelessNicUpperCtrl;
import org.mixim.modules.power.battery.BatteryStats;
import org.mixim.modules.power.battery.SimpleBattery;



module ConsensusAndFormationNode
{
    parameters:
        string nicType = default("Nic802154_TI_CC2420");  //type of used nic
        string networkType = default("BaseNetwLayer");       //type of the network layer
        string applicationType = default("ConsensusAndFormationAppLayer");  //type of the application layer
        string mobilityType = default("ConsensusAndFormationMobility"); //type of the mobility module
        string arpType = default("org.mixim.modules.netw.ArpHost");                 //type of address resolution module
        int numHosts; // total number of hosts in the network;
        batteryStats.detail = default(false);
        batteryStats.timeSeries = default(false);
        battery.nominal = default(1000 mAh);
        battery.capacity = default(battery.nominal);
        battery.voltage = default(3 V);
        battery.resolution = default(60 s);
        battery.publishDelta = default(1);
        battery.publishTime = default(battery.resolution);
        battery.numDevices = default(1);
        @display("bgb=210,450,white;i=device/UAV;i2=status/battery;b=40,40,rect");
        @node();

    gates:
        input radioIn; // gate for sendDirect
    submodules:
        arp: <arpType> like IBaseArp {
            @display("p=140,153;i=block/network2");
        }
        //mobility: <mobilityType> like inet.mobility.IMobility {
        mobility: ConsensusAndFormationMobility {
            parameters:
                @display("p=140,30;i=block/cogwheel");
        }
        nic: <nicType> like IWirelessNicUpperCtrl {
            parameters:
                @display("p=70,380;i=block/wrxtx,#008000");
        }
        // OSI network layer
        netwl: <networkType> like IBaseNetwLayer {
            parameters:
                @display("p=68,192;i=block/layer");
        }
        appl: ConsensusAndFormationAppLayer {
            parameters:
                @display("p=70,30;i=app");
        }
        batteryStats: BatteryStats {
            @display("p=140,296;i=block/table,#FF8040");
        }
        battery: SimpleBattery {
            @display("p=140,216;i=block/plug,#FF8000");
        }
        //lqi: FormLqi {
            //parameters:
                //@display("p=140,380;i=block/classifier2_l");
        //}
    connections:
        nic.upperLayerOut --> netwl.lowerLayerIn;
        nic.upperLayerIn <-- netwl.lowerLayerOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> netwl.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- netwl.lowerControlOut;


        netwl.upperLayerOut --> appl.lowerLayerIn;
        netwl.upperLayerIn <-- appl.lowerLayerOut;
        netwl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
        netwl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;

        appl.mobilityLayerOut --> mobility.ApplLayerIn;
        appl.mobilityLayerIn <-- mobility.ApplLayerOut;
        appl.mobilityControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> mobility.ApplControlIn;
        appl.mobilityControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- mobility.ApplControlOut;

        radioIn --> nic.radioIn;
}
