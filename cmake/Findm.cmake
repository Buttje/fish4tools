find_library(M_LIBRARY	NAMES m	PATH /usr/lib /usr/lib64 )

INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES (m.h HAVE_M_H)

if (M_LIBRARY AND HAVE_M_H)
	set( M_FOUND TRUE )
endif (M_LIBRARY AND HAVE_M_H)

if ( M_FOUND )
	message( STATUS "Found libm: ${M_LIBRARY}")
else ( M_FOUND )
	message( STATUS "M not found")
endif ( M_FOUND )
