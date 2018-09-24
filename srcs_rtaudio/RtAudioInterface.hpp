#ifndef RTAUDIO_INTERFACE_HPP
# define RTAUDIO_INTERFACE_HPP

# include "RtAudio/RtAudio.h"
# include "IDynamicAudioLibrary.hpp"


class RtAudioInterface : public IDynamicAudioLibrary {

    private:
		RtAudioInterface(RtAudioInterface const & src);

		RtAudioInterface& operator=(RtAudioInterface const & rhs);

	public:
		RtAudioInterface(void);
		~RtAudioInterface(void);

		void	play_eat_sound (void);
		void	play_death_sound (void);

		bool active;
};

extern "C" {
	RtAudioInterface	*getAudioInterface(void);
	void	deleteAudioInterface(RtAudioInterface *test);
}

#endif // !RTAUDIO_INTERFACE_HPP