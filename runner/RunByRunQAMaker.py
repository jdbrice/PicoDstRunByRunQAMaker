


c_template = """ 
<?xml version="1.0" encoding="utf-8" ?>
<job maxFilesPerProcess="1" filesPerHour=".5" fileListSyntax="paths" simulateSubmission="false">
	<command>
		starver SL15e

		./app prod.xml $INPUTFILE0 {args} &gt;&amp; log_$INPUTFILE0.log 
	</command>

	<stdout URL="file:/star/data03/pwg/jdb/scratch/log/$JOBID.out" />
	<stderr URL="file:/star/data03/pwg/jdb/scratch/log/$JOBID.err" />
	<input URL="filelist:/star/u/jdb/work/PicoDstRunByRunQAMaker/bin/n.lis" nFiles="{nFiles}"/>
	
	<output fromScratch="*.root" toURL="file:/star/data03/pwg/jdb/scratch/" />
	<output fromScratch="log_*.log" toURL="file:/star/data03/pwg/jdb/scratch/" />

	<SandBox>
 		<Package>
 			<File>file:./app</File>
 			<File>file:./list.lis</File>
 			<File>file:./prod.xml</File> 
 			<File>file:./config/</File> 
 		</Package> 
 	</SandBox>

	<Generator> 
 		<Location>/star/data03/pwg/jdb/scratch/gen</Location> 
 	</Generator> 
</job>
"""



prods = ( "AuAu_200_production_2014", "AuAu_200_production_low_2014", "AuAu_200_production_mid_2014", "AuAu_200_production_high_2014" )
triggers = ( "dimuon", "dimuonhft", "singlemuon", "emu" )


for prod in prods :
	for trig in triggers :
		filename = "RunByRunQAMaker_prod_" + prod + "_triggers_" + trig + ".xml"
		with open( filename, 'w' ) as f :
			args = "--RunByRunQAMaker:production=" + prod
			args = args + " --RunByRunQAMaker:triggers=" + trig
			f.write( c_template.format( nFiles=3788, args=args ) )
