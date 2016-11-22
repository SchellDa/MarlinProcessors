#ifndef RefTrackAlignProcessor_h
#define RefTrackAlignProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <Eigen/Dense>
#include <memory>
#include <gear/SiPlanesParameters.h>
#include <gear/SiPlanesLayerLayout.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TF1.h>
#if defined(USE_AIDA) || defined(MARLIN_USE_AIDA)
#include <AIDA/IHistogram2D.h>
#include <AIDA/IProfile1D.h>
#endif
using namespace lcio;
using namespace marlin;

/**  
 * @param CollectionName Name of the MCParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id: RefTrackAlignProcessor.h,v 1.4 2005-10-11 12:57:39 gaede Exp $ 
 */

class RefTrackAlignProcessor : public Processor
{ 
public:
  
	virtual Processor*  newProcessor() { return new RefTrackAlignProcessor; }
	
	
	RefTrackAlignProcessor();
	
	/** Called at the begin of the job before anything is read.
	 * Use to initialize the processor, e.g. book histograms.
	 */
	virtual void init();
	
	/** Called for every run.
	 */
	virtual void processRunHeader( LCRunHeader* run );
	
	/** Called for every event - the working horse.
	 */
	virtual void processEvent( LCEvent * evt ); 
	
	
	virtual void check( LCEvent * evt ); 
	
	
	/** Called after data processing for clean up.
	 */
	virtual void end();
  
  
protected:
	/// REF tracker data collection name
	std::string _colRefData;
	/// fitted Track collection name
	std::string _colTracks;
	/// REF alignment DB name
	std::string _refAlignDB;
	/// REF cut data file
	std::string _refCutDB;
	/// Flip X coordinate
	bool _flipXCoordinate;
	/// Flip Y coordinate
	bool _flipYCoordinate;
	/// REF sensor id
	int _refSensorId;
	/// NAF mode
	bool _noisyAsFuckMode;


private:
	struct track_t {
		std::vector<Eigen::Vector3d> fitted;
		std::vector<Eigen::Vector3d> raw;
		std::vector<int> fittedSensor;
		std::vector<int> rawSensor;
		int eventNumber;
		int trackNumber;
	};

	std::vector<Eigen::Vector2d> getRefHits(LCCollection* col);
	std::vector<Eigen::Vector3d> transformRefHits(std::vector<Eigen::Vector2d> hits);
	std::vector<track_t> getTracksFromCollection(LCEvent* evt, LCCollection* col);

	void bookHistos();
	void cutCorrelationHistogram(TH2D* hist, AIDA::IProfile1D* debugProfile);

	const gear::SiPlanesParameters* _siPlanesParameters;
	const gear::SiPlanesLayerLayout* _siPlanesLayerLayout;

	size_t _totalEvents;
	size_t _validEvents;

	TH2D* _refTrackExtrapolatedXCor;
	TH2D* _refTrackExtrapolatedYCor;
	TH1D* _xCorHist;
	TH1D* _yCorHist;

#if defined(USE_AIDA) || defined(MARLIN_USE_AIDA)
	AIDA::IHistogram2D* refTrackXCorrelation;
	AIDA::IHistogram2D* refTrackYCorrelation;
	AIDA::IHistogram2D* refTrackGlobalXCor;
	AIDA::IHistogram2D* refTrackGlobalYCor;
	AIDA::IProfile1D* refTrackGlobalXProfile;
	AIDA::IProfile1D* refTrackGlobalYProfile;
#endif
};

#endif



