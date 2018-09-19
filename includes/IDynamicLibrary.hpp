#ifndef I_DYNAMIC_LIBRARY_HPP
# define I_DYNAMIC_LIBRARY_HPP

# include <vector>
# include <tuple>

class IDynamicLibrary {
	public:
		IDynamicLibrary(void) {};
		virtual ~IDynamicLibrary(void) {};

		virtual void	get_user_input (void) = 0;
		virtual void	refresh_window (void) = 0;
		virtual void	close_window (void) = 0;

		class DynamicLibraryException : public std::exception {};
};

#endif // !I_DYNAMIC_LIBRARY_HPP
