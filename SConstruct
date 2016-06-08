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

paths 			= [ '.', 			# dont really like this but ended up needing for root dict to work ok
					'include', 
					JDB_LIB + "/include", 
					JDB_LIB + "/include/jdb", 
					ROOT_SYS + "/include" 
					]
paths.extend( Glob( "include/*" ) )


########################### ROOT dictionary creation ##########################
rootcint_env = Environment(ENV = {'PATH' : os.environ['PATH']})
# SOURCES.file - returns the basename of each full-path source - ended up not using because root_Cint dict would compile but not run
rootcint = Builder( action='rootcint $TARGET $_CPPINCFLAGS $SOURCES.file' )  
rootcint_env.Append( BUILDERS 		= { 'RootCint' : rootcint } )
# hack to make the rootcint use abs path to headers
rootcint_env[ "_CPPINCFLAGS" ] = "-I" + Dir(".").abspath + "/" + str( " -I" + Dir(".").abspath + "/").join( map( str, Glob( "#include/*" ) ) ) 
root_dict = rootcint_env.RootCint( "src/TreeData/CintDictionary.cpp", Glob( "include/TreeData/*.h" ) )
Clean( root_dict, "src/TreeData/CintDictionary_rdict.pcm" )
rootcint_env.Alias( 'dict', root_dict )


########################## Project Target #####################################
common_env = Environment()
common_env.Append(LIBS 			= libraries)
common_env.Append(CPPDEFINES 	= cppDefines)
common_env.Append(CPPFLAGS 		= cppFlags)
common_env.Append(CXXFLAGS 		= cxxFlags)
common_env.Append(LINKFLAGS 	= ROOTLIBS + " " + JDB_LIB + "/lib/libJDB.a" )
common_env.Append(CPPPATH		= paths)

jdb_log_level = ARGUMENTS.get( "ll", 60 )
common_env.Append(CXXFLAGS 		= "-DJDB_LOG_LEVEL=" + str(jdb_log_level) )

target = common_env.Program( target='bin/app', source=[Glob( "src/*.cpp" ), Glob( "src/*/*.cpp" )] )
Depends( target, root_dict )
Depends( target, JDB_LIB + "/lib/libJDB.a" )

# set as the default target
Default( target )


