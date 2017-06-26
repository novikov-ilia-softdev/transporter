AC_INIT([transporter], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AC_LANG([C++])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
CXXFLAGS="$CXXFLAGS -std=c++11"

AC_CHECK_LIB([pthread], [main], [],
[ 
	echo "pthread failure." 
	exit -1
])

AC_CHECK_LIB([gtest], [main], [],
[ 
	echo "gtest failure." 
	exit -1
])

AC_CONFIG_FILES([
 	Makefile
 	src/Makefile
 	test/Makefile
])
AC_OUTPUT