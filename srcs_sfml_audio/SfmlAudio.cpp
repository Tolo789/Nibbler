#include "SfmlAudio.hpp"

// === CONSTRUCTOR =============================================================

RtAudioInterface::RtAudioInterface(void) {
	active = false;

	if (!startBuffer.loadFromFile("sounds/start.wav")) {
		return ;
	}
	if (!eatBuffer.loadFromFile("sounds/eat.wav")) {
		return ;
	}
	if (!deathBuffer.loadFromFile("sounds/death.wav")) {
		return ;
	}

	active = true;
	return ;
}

RtAudioInterface::RtAudioInterface(RtAudioInterface const & src) {
	*this = src;
	return ;
}

RtAudioInterface::~RtAudioInterface(void) {
	if (!active)
		return ;
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
void	RtAudioInterface::play_start_sound (void) {
	if (!active)
		return ;
	sound.setBuffer(startBuffer);
	sound.play();
	return ;
}

void	RtAudioInterface::play_eat_sound (void) {
	if (!active)
		return ;
	sound.setBuffer(eatBuffer);
	sound.play();
	return ;
}

void	RtAudioInterface::play_death_sound (void) {
	if (!active)
		return ;
	sound.setBuffer(deathBuffer);
	sound.play();
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
