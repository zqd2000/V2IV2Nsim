/*
 *
 * Part of 5G-Sim-V2I/N
 *
 *
*/

#pragma once

#define ATT_MAXDISTVIOLATED 1000

#include <omnetpp.h>
#include "nr/common/NRCommon.h"
#include "stack/phy/ChannelModel/LteRealisticChannelModel.h"
#include "stack/phy/layer/LtePhyBase.h"
#include "nr/stack/phy/layer/NRPhyUe.h"
#include "nr/stack/phy/layer/NRPhyGnb.h"
#include "../../mac/layer/NRMacGnb.h"


/*
 * Realistic Channel Model as taken from
 * "--- Guidelines for evaluation of radio interface technologies for IMT-2020"
 *
 * see inherit class for method description
 */
class NRRealisticChannelModel : public LteRealisticChannelModel
{
public:
	virtual void initialize();
    virtual void resetOnHandover(MacNodeId nodeId, MacNodeId oldMasterId) {
            positionHistory_.erase(nodeId);
            losMap_.erase(nodeId);
            lastComputedSF_.erase(nodeId);
            jakesFadingMap_.erase(nodeId);
			losMap_.erase(nodeId);
			lastComputedSF_.erase(nodeId);
			jakesFadingMap_.erase(nodeId);
//        }
    }
    inet::Coord getMyPosition(){
    	return myCoord3d;
    }
    bool isNodeB(){
    	return isNodeB_;
    }
protected:
    simtime_t lastStatisticRecord;

    DeploymentScenarioNR scenarioNR_;
    NRChannelModel channelModelType_;
    bool isNodeB_;
    //bool dynamic_los_;
    bool veinsObstacleShadowing;
    inet::Coord myCoord3d;

    bool dynamicNlos_;//using obstacleControl

    int errorCount;

    double antennaGainGnB_;

    virtual std::vector<double> getSINR(LteAirFrame *frame, UserControlInfo* lteInfo);

    virtual double getAttenuationNR(const MacNodeId & nodeId, const Direction & dir, const inet::Coord & uecoord, const inet::Coord & enodebcoord);

    virtual double getAttenuation_D2D(MacNodeId nodeId, Direction dir, inet::Coord coord, MacNodeId node2_Id,
            inet::Coord coord_2);

    virtual double computeIndoorHotspot(const double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    virtual double computeDenseUrbanEmbb(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    virtual double computeRuralEmbb(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    virtual double computeUrbanMacroMmtc(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    virtual double computeUrbanMacroUrllc(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    virtual bool isCorrupted(LteAirFrame *frame, UserControlInfo* lteInfo);

    virtual bool error_D2D(LteAirFrame *frame, UserControlInfo* lteI, std::vector<double> rsrpVector);

    virtual std::vector<double> getRSRP_D2D(LteAirFrame *frame, UserControlInfo* lteInfo_1, MacNodeId destId,
            inet::Coord destCoord);

    virtual double getStdDevNR(const double & d3ddistance, const double & d2ddistance, const MacNodeId & nodeId);

    void checkScenarioAndChannelModel();

    void computeLosProbabilityNR(const double & d2ddistance, const MacNodeId & nodeId);

    double calcDistanceBreakPoint(const double & d2d);

    double computeUMaA(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computeUMaB(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computeUMiA(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computeUMiB(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computeRMaA(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computeRMaB(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    double computePLumaLos(const double & d3ddistance, double & d2ddistance);

    double computePLumiALos(const double & d3ddistance, double & d2ddistance);

    double computePLumiBLos(const double & d3ddistance, double & d2ddistance);

    double computePLrmaLos(const double & d3ddistance, double & d2ddistance);

    double computePLrmaNlos(const double & d3ddistance, double & d2ddistance);

    double calcDistanceBreakPointRMa(const double & d2ddistance);

    double computeExtCellPathLossNR(double & d3ddistance, double & d2ddistance, const MacNodeId & nodeId);

    bool computeMultiCellInterferenceNR(const MacNodeId & eNbId, const MacNodeId & ueId, const inet::Coord & uecoord,
            bool isCqi, std::vector<double> & interference, Direction dir, const Coord & enodebcoord);

    virtual bool computeUplinkInterference(MacNodeId eNbId, MacNodeId senderId, bool isCqi, const RbMap& rbmap, std::vector<double> * interference);
	virtual bool computeDownlinkInterference(MacNodeId eNbId, MacNodeId ueId, inet::Coord coord, bool isCqi, const RbMap& rbmap, std::vector<double> * interference);

    bool computeExtCellInterferenceNR(const MacNodeId & eNbId, const MacNodeId & nodeId, const Coord & uecoord,
            bool isCqi, std::vector<double> & interference, const Coord & enodebcoord);
};
