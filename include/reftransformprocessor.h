#ifndef RefTransformProcessor_h
#define RefTransformProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <Eigen/Dense>
#include <memory>
#include <gear/SiPlanesParameters.h>
#include <gear/SiPlanesLayerLayout.h>
#include <TH2D.h>
#include <TH1D.h>
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
 * @version $Id: RefTransformProcessor.h,v 1.4 2005-10-11 12:57:39 gaede Exp $ 
 */

class RefTransformProcessor : public Processor
{ 
public:
  
	virtual Processor*  newProcessor() { return new RefTransformProcessor; }
	
	
	RefTransformProcessor();
	
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
	/// REF 
	std::string _refAlignDB;
	/// REF cut data file
	std::string _refCutDB;
	/// fitted Track collection name
	std::string _colTracks;
	/// Output collection name
	std::string _colTransformedRefData;
	/// Output collection with tracks hitting REF
	// std::string _colFilteredTracks;
	/// Clear-text output filename
	std::string _csvOutputFile;
	/// Clear-text enable
	bool _csvOutputFileEnable;
	/// Width of the datacut in multiples of sigma
	int _cutWidthTimesSigma;
	/// Flip X coordinate
	bool _flipXCoordinate;
	/// Flip Y coordinate
	bool _flipYCoordinate;
	/// REF sensor id
	int _refSensorId;
	/// Debug CSV output
	bool _debugCsvOutput;
	/// Debug CSV output file
	std::string _debugCsvOutputFile;

	struct track_t {
		std::vector<Eigen::Vector3d> fitted;
		std::vector<Eigen::Vector3d> raw;
		std::vector<int> fittedSensor;
		std::vector<int> rawSensor;
		int eventNumber;
		int trackNumber;
	};

	struct cut_t {
		double meanX;
		double meanY;
		double sigmaX;
		double sigmaY;
	};

	cut_t _cutData;

private:
	std::vector<Eigen::Vector2d> getRefHits(LCCollection* col);
	std::vector<Eigen::Vector3d> transformRefHits(std::vector<Eigen::Vector2d> hits);
	std::vector<track_t> getTracksFromCollection(LCEvent* evt, LCCollection* col);

	void bookHistos();

	const gear::SiPlanesParameters* _siPlanesParameters;
	const gear::SiPlanesLayerLayout* _siPlanesLayerLayout;

#if defined(USE_AIDA) || defined(MARLIN_USE_AIDA)
#endif
};

#endif



