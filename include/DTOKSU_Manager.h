#ifndef __DTOKSU_Manager_H_INCLUDED__   // if Matter.h hasn't been included yet...
#define __DTOKSU_Manager_H_INCLUDED__

//#define NETCDF_SWITCH

#include "DTOKSU.h"
#include <random>	// for std::normal_distribution<> etc.
#include <chrono>	// for chrono::high_resolution_clock::now().time_since_epoch().count();
#include <config4cpp/Configuration.h>	// For Configuration
#ifdef NETCDF_SWITCH
#include <netcdfcpp.h>	// for reading netcdf files
#endif
#include <exception>	// for Exception handling
#include <stdlib.h>

struct PlasmaFileReadFailure : public std::exception {
   const char * what () const throw () {
      return "Exception raised opening/reading/closing PlasmaData file\n";
   }
};

class DTOKSU_Manager{

	private:
		// Private member data
		DTOKSU *Sim;
		Matter *Sample;
		PlasmaGrid_Data Pgrid;
		PlasmaData Pdata;

		int Config_Status;

		template<typename T> int input_function(int &argc, char* argv[], int &i, std::stringstream &ss0, T &Temp)const;
		void show_usage(std::string name)const;
		void config_message()const;
		bool check_pdata_range()const;

		int configure_plasmagrid(std::string plasma_dirname);
		int read_data(std::string plasma_dirname);
		#ifdef NETCDF_SWITCH
		int read_MPSIdata(std::string plasma_dirname);
		#endif
	
	public:
		DTOKSU_Manager();
		DTOKSU_Manager( int argc, char* argv[] );
		DTOKSU_Manager( int argc, char* argv[], std::string = "Config_Files/DTOKSU_Config.cfg" );

		~DTOKSU_Manager(){
		};
		
		int Configure(std::string = "Config_Files/DTOKSU_Config.cfg");
		int Configure(int argc, char* argv[], std::string = "Config_Files/DTOKSU_Config.cfg");


		int Breakup();
		int Run();
};

#endif
