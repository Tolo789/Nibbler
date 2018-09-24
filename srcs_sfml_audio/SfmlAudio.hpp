#ifndef RTAUDIO_INTERFACE_HPP
# define RTAUDIO_INTERFACE_HPP

# include "SFML/Audio.hpp"
# include "IDynamicAudioLibrary.hpp"


class RtAudioInterface : public IDynamicAudioLibrary {
    private:
		RtAudioInterface(RtAudioInterface const & src);

		RtAudioInterface& operator=(RtAudioInterface const & rhs);

		sf::SoundBuffer startBuffer;
		sf::SoundBuffer eatBuffer;
		sf::SoundBuffer deathBuffer;
		sf::Sound sound;

	public:
		RtAudioInterface(void);
		~RtAudioInterface(void);

		void	play_start_sound (void);
		void	play_eat_sound (void);
		void	play_death_sound (void);

		bool active;
};

extern "C" {
	RtAudioInterface	*getAudioInterface(void);
	void	deleteAudioInterface(RtAudioInterface *test);
}

#endif // !RTAUDIO_INTERFACE_HPP