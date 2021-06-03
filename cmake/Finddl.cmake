find_library(DL_LIBRARY	NAMES dl	PATH /usr/lib /usr/lib64 )

INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES (dl.h HAVE_DL_H)

if (DL_LIBRARY AND HAVE_DL_H)
	set( DL_FOUND TRUE )
endif (DL_LIBRARY AND HAVE_DL_H)

if ( DL_FOUND )
	message( STATUS "Found libdl: ${DL_LIBRARY}")
else ( DL_FOUND )
	message( STATUS "DL not found")
endif ( DL_FOUND )
