#ifndef I_DYNAMIC_LIBRARY_HPP
# define I_DYNAMIC_LIBRARY_HPP

class IDynamicLibrary {
	public:
		IDynamicLibrary() {};
		virtual ~IDynamicLibrary() {};

		virtual void	refresh_window () = 0;
		virtual void	close_window () = 0;
};

#endif // !I_DYNAMIC_LIBRARY_HPP