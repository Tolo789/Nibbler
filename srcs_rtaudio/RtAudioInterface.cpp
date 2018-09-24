#include "RtAudioInterface.hpp"

// === CONSTRUCTOR =============================================================

RtAudioInterface::RtAudioInterface(void) {
	RtAudio audio;
  // Determine the number of devices available
  unsigned int devices = audio.getDeviceCount();
  // Scan through devices for various capabilities
  RtAudio::DeviceInfo info;
  for ( unsigned int i=0; i<devices; i++ ) {
    info = audio.getDeviceInfo( i );
    if ( info.probed == true ) {
      // Print, for example, the maximum number of output channels for each device
      std::cout << "device = " << i;
      std::cout << ": maximum output channels = " << info.outputChannels << "\n";
    }
  }
	return ;
}

RtAudioInterface::RtAudioInterface(RtAudioInterface const & src) {
	*this = src;
	return ;
}

RtAudioInterface::~RtAudioInterface(void) {
	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

RtAudioInterface& RtAudioInterface::operator=(RtAudioInterface const & rhs) {
	this->active = rhs.active;
	return *this;
}

// === ENDOPERATORS ============================================================

// === PRIVATE FUNCS ===========================================================
// === END PRIVATE FUNCS =======================================================

// === OVERRIDES ===============================================================
void	RtAudioInterface::play_eat_sound (void) {
	return ;
}

void	RtAudioInterface::play_death_sound (void) {
	return ;
}

// === END OVERRIDES ===========================================================

// === OTHERS ==================================================================
RtAudioInterface	*getAudioInterface(void) {
	return new RtAudioInterface();
}

void	deleteAudioInterface(RtAudioInterface *test) {
	delete test;
}
// === END OTHERS ==============================================================
