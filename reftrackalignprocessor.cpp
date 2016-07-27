#include "reftrackalignprocessor.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#ifdef MARLIN_USE_AIDA
#include <marlin/AIDAProcessor.h>
#include <AIDA/IHistogramFactory.h>
#include <AIDA/ICloud1D.h>
//#include <AIDA/IHistogram1D.h>
#endif // MARLIN_USE_AIDA


using namespace lcio;
using namespace marlin;


RefTrackAlignProcessor aRefTrackAlignProcessor;


RefTrackAlignProcessor::RefTrackAlignProcessor()
 : Processor("RefTrackAlignProcessor")
{
	_description = "Calculate REF offset-alignment using fitted Tracks.";


	// register steering parameters: name, description, class-variable, default value
	registerInputCollection(
		LCIO::TRACKERDATA,
        	"RefDataCollectionName", 
		"Name of the collection containing REF TrackerData",
		_colRefData,
		std::string("CMSPixelREF")
		);
	registerInputCollection(
		LCIO::TRACK,
		"TrackCollectionName",
		"Collection containing fitted and aligned Tracks through telescope.",
		_colTracks,
		std::string("track")
		);
	registerOutputCollection(
		LCIO::TRACKERHIT,
		"REFAlignedHits",
		"Collections where the aligned hits are written to.",
		_colAligned,
		std::string("AlignedREF")
		);
	registerProcessorParameter(
		"refAlignDbFileName",
		"File name of the align-DB generated by this processor",
		_refAlignDB,
		std::string("ref-align-db.slcio")
		);
}



void RefTrackAlignProcessor::init()
{
    streamlog_out(DEBUG) << "   init called  " << std::endl;

    // usually a good idea to
    printParameters();
}


void RefTrackAlignProcessor::processRunHeader(LCRunHeader* run)
{
} 

void RefTrackAlignProcessor::processEvent(LCEvent* evt)
{
	auto colRefData = evt->getCollection(_colRefData);
	auto colTracks = evt->getCollection(_colTracks);
	if(!colRefData || !colTracks) {
		return;
	}
	streamlog_out(WARNING) << "I'm running, whoooooo!" << std::endl;
}

/*
void RefTrackAlignProcessor::processEvent( LCEvent * evt )
{
    // this gets called for every event 
    // usually the working horse ...


#ifdef MARLIN_USE_AIDA

    // define a histogram pointer
    static AIDA::ICloud1D* hMCPEnergy ;    

    if( isFirstEvent() ) { 

        hMCPEnergy = AIDAProcessor::histogramFactory(this)->
            createCloud1D( "hMCPEnergy", "energy of the MCParticles", 100 ) ; 

    }
#endif // MARLIN_USE_AIDA

   // try to get lcio collection (exits if collection is not available)::
    // NOTE: if the AIDAProcessor is activated in your steering file and Marlin is linked with
    //      RAIDA you may get the message: "*** Break *** segmentation violation" followed by a
    //      stack-trace (generated by ROOT) in case the collection is unavailable. This happens
    //      because ROOT is somehow catching the exit signal commonly used to exit a program
    //      intentionally. Sorry if this messsage may confuse you. Please ignore it!
    LCCollection* col = evt->getCollection(_colRefData);


    // Alternativelly if you do not want Marlin to exit in case of a non-existing collection
    // use the following (commented out) code:
    //LCCollection* col = NULL;
    //try{
    //    col = evt->getCollection( _colName );
    //}
    //catch( lcio::DataNotAvailableException e )
    //{
    //    streamlog_out(WARNING) << _colName << " collection not available" << std::endl;
    //    col = NULL;
    //}

    // this will only be entered if the collection is available
    if( col != NULL ){

        int nMCP = col->getNumberOfElements()  ;

        for(int i=0; i< nMCP ; i++){

            MCParticle* p = dynamic_cast<MCParticle*>( col->getElementAt( i ) ) ;

#ifdef MARLIN_USE_AIDA
            // fill histogram from LCIO data :
            hMCPEnergy->fill( p->getEnergy() ) ;
#endif
        } 
    }



    //-- note: this will not be printed if compiled w/o MARLINDEBUG=1 !

    streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
        << "   in run:  " << evt->getRunNumber() << std::endl ;
}
*/


void RefTrackAlignProcessor::check( LCEvent * evt )
{
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void RefTrackAlignProcessor::end()
{
    //   std::cout << "RefTrackAlignProcessor::end()  " << name() 
    // 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
    // 	    << std::endl ;

}
