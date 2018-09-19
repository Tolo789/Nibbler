#ifndef I_DYNAMIC_LIBRARY_HPP
# define I_DYNAMIC_LIBRARY_HPP

# include <vector>
# include <tuple>

class IDynamicLibrary {
	public:
		IDynamicLibrary() {};
		virtual ~IDynamicLibrary() {};

		virtual void	get_user_input () = 0;
		virtual void	refresh_window (std::vector<std::tuple<int, int>> &snake_body, std::tuple<int, int> &fruit_pos) = 0;
		virtual void	close_window () = 0;

		class DynamicLibraryException : public std::exception {};
};

#endif // !I_DYNAMIC_LIBRARY_HPP
