#ifndef I_DYNAMIC_AUDIO_LIBRARY_HPP
# define I_DYNAMIC_AUDIO_LIBRARY_HPP

# include <exception>

class IDynamicAudioLibrary {
	public:
		IDynamicAudioLibrary(void) {};
		virtual ~IDynamicAudioLibrary(void) {};

		virtual void	play_start_sound (void) = 0;
		virtual void	play_eat_sound (void) = 0;
		virtual void	play_death_sound (void) = 0;

		class DynamicAudioLibraryException : public std::exception {};
};

#endif // !I_DYNAMIC_AUDIO_LIBRARY_HPP
