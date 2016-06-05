#!python
import subprocess
import os


subprocess.check_output

ROOTCFLAGS    	= subprocess.check_output( ['root-config',  '--cflags'] ).rstrip().split( " " )
ROOTLDFLAGS    	= subprocess.check_output( ["root-config",  "--ldflags"] )
ROOTLIBS      	= subprocess.check_output( ["root-config",  "--libs"] )
ROOTGLIBS     	= subprocess.check_output( ["root-config",  "--glibs"] )
ROOTLIBPATH 	= subprocess.check_output( ["root-config", "--libdir" ] )
ROOT_SYS 		= os.environ[ "ROOTSYS" ]
JDB_LIB			= os.environ[ "JDB_LIB" ]

# Set our required libraries
libraries 		= [ ]
library_paths 	= [ ROOTLIBPATH ]
cppDefines 		= {}
cppFlags 		= ['-Wall' ]#, '-Werror']
cxxFlags 		= ['-std=c++11' ]
cxxFlags.extend( ROOTCFLAGS )
paths 			= [ 'include', JDB_LIB + "/include", JDB_LIB + "/include/jdb", ROOT_SYS + "/include", Glob( "include/*" ) ]
# print Glob( "include/*" )
# Exit()
# define the attributes of the build environment shared between
# both the debug and release builds
common_env = Environment()
common_env.Append(LIBS 			= libraries)
common_env.Append(CPPDEFINES 	= cppDefines)
common_env.Append(CPPFLAGS 		= cppFlags)
common_env.Append(CXXFLAGS 		= cxxFlags)
common_env.Append(LINKFLAGS 	= ROOTLIBS + " " + JDB_LIB + "/lib/libJDB.a" )
common_env.Append(CPPPATH		= paths)

target = common_env.Program( target='bin/app', source=[Glob( "src/*.cpp" ), Glob( "src/*/*.cpp" )] )

# set as the default target
Default( target )