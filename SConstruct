#!python
import subprocess
import os


subprocess.check_output

ROOTCFLAGS    	= subprocess.check_output( ['root-config',  '--cflags'] ).split( " " )
ROOTLDFLAGS    	= subprocess.check_output( ["root-config",  "--ldflags"] ).split( " " )
ROOTLIBS      	= subprocess.check_output( ["root-config",  "--libs"] ).split( " " )
ROOTGLIBS     	= subprocess.check_output( ["root-config",  "--glibs"] )
ROOT_SYS 		= os.environ[ "ROOTSYS" ]
JDB_LIB			= os.environ[ "JDB_LIB" ]

# Set our required libraries
libraries 		= []
print ROOTLIBS[ 1: ]
print libraries
library_paths 	= [ ROOTLIBS[0] ]
cppDefines 		= {}
cppFlags 		= ['-Wall']#, '-Werror']
cxxFlags 		= ['-std=c++11' ]
# cxxFlags.extend( [ROOTLIBS] )
# cxxFlags.append( ROOTCFLAGS )
paths 			= [ 'include', JDB_LIB + "/include", JDB_LIB + "/include/jdb", ROOT_SYS + "/include" ]

# define the attributes of the build environment shared between
# both the debug and release builds
common_env = Environment()
common_env.Append(LIBS 			= libraries)
common_env.Append(LIBPATH 		= library_paths)
common_env.Append(CPPDEFINES 	= cppDefines)
common_env.Append(CPPFLAGS 		= cppFlags)
common_env.Append(CXXFLAGS 		= cxxFlags)
common_env.Append(LDFLAGS 		= ROOTLIBS )
common_env.Append(CPPPATH		= paths)

target = common_env.Program( target='app', source=Glob( "src/*.cpp" ) )

# set as the default target
Default( target )