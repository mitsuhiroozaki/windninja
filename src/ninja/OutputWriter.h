/******************************************************************************
*
* Filename: OutputWriter.h
*
* Project:  WindNinja 
* Purpose:  Class to handle output of WindNinja simulations to various GDAL
*           formats
* Author:   Levi Malott, lmnn3@mst.edu 
*
******************************************************************************
*
* THIS SOFTWARE WAS DEVELOPED AT THE ROCKY MOUNTAIN RESEARCH STATION (RMRS)
* MISSOULA FIRE SCIENCES LABORATORY BY EMPLOYEES OF THE FEDERAL GOVERNMENT
* IN THE COURSE OF THEIR OFFICIAL DUTIES. PURSUANT TO TITLE 17 SECTION 105
* OF THE UNITED STATES CODE, THIS SOFTWARE IS NOT SUBJECT TO COPYRIGHT
* PROTECTION AND IS IN THE PUBLIC DOMAIN. RMRS MISSOULA FIRE SCIENCES
* LABORATORY ASSUMES NO RESPONSIBILITY WHATSOEVER FOR ITS USE BY OTHER
* PARTIES,  AND MAKES NO GUARANTEES, EXPRESSED OR IMPLIED, ABOUT ITS QUALITY,
* RELIABILITY, OR ANY OTHER CHARACTERISTIC.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef OUTPUTWRITER_H
#define OUTPUTWRITER_H 

#include "ascii_grid.h"
#include "EasyBMP.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_Geometry.h"
#include "ninjaUnits.h"
#include "ninjaMathUtility.h"
#include "wn_Arrow.h"

#include "ogr_spatialref.h"
#include "ogr_core.h"
#include "gdal_version.h"
#include "cpl_port.h"
#include "cpl_error.h"
#include "cpl_conv.h"
#include "cpl_string.h"
#include "cpl_vsi.h"
#include "gdalwarper.h"
#include "gdal_priv.h"
#include "gdal.h"

#include "gdal_util.h"

#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "ninjaException.h"


#include "Style.h"

#include <stdio.h>
#include <fstream>



/*
 * =====================================================================================
 *        Class:  OutputWriter
 *  Description:  Handles writing the output of simulations to supported GDAL formats
 * =====================================================================================
 */
class OutputWriter
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        OutputWriter ();                             /* constructor */
        ~OutputWriter();

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        void setSpeedGrid(AsciiGrid<double> &s);
        void setDirGrid(AsciiGrid<double> &d);
#ifdef EMISSIONS
        void setDustGrid(AsciiGrid<double> &d);
#endif
        void setDEMfile(std::string fname) {demFile=fname;}
        void setNinjaTime(std::string t) {ninjaTime=t;}
        void setRunNumber(int n) {runNumber=n;}
        void setMaxRunNumber(int n) {maxRunNumber=n;}
        
        void setMemDs(GDALDatasetH hSpdMemDs, GDALDatasetH hDirMemDs, GDALDatasetH hDustMemDs);

        /* ====================  OPERATORS     ======================================= */
        bool write(std::string outputFilename, std::string driver);

    protected:
        /* ====================  METHODS       ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  METHODS       ======================================= */
        void _createDefaultStyles();
        void _destroyDefaultStyles();
        void _createOGRFileWithFields();
        bool _createPDFFromDEM(std::string outputfn);
        bool _writePDF(std::string outputfn);
        bool _writeGTiff(std::string filename, GDALDatasetH &hMemDs);
        
        /* ====================  DATA MEMBERS  ======================================= */
        AsciiGrid<double> spd;
        AsciiGrid<double> dir;
#ifdef EMISSIONS
        AsciiGrid<double> dust;
#endif
        int runNumber;
        int maxRunNumber;
        GDALDatasetH hSpdMemDs;
        GDALDatasetH hDirMemDs;
        GDALDatasetH hDustMemDs;
        
        std::string ninjaTime;
        double resolution;
        std::string demFile;
        std::string inputSpeedFile;
        velocityUnits::eVelocityUnits speedUnits;
        std::string inputDirFile;
        std::string kmlFile;
        std::string kmzFile;
        std::string legendFile;
        std::string timeDateLegendFile;
        std::string wxModelName;

        static const char * SPEED;//      = "speed";
        static const char * DIR;//        = "dir";
        static const char * AV_DIR;//     = "AV_dir";
        static const char * AM_DIR;//     = "AM_dir";
        static const char * QGIS_DIR;//   = "QGIS_dir";
        static const char * OGR_FILE;


        static const int NCOLORS = 5; 
        double *split_vals;
        Style ** colors;

        double northExtent, eastExtent, southExtent, westExtent;
        double linewidth;

        GDALDatasetH hSrcDS;
        GDALDatasetH hDstDS;
        GDALDriverH hDriver;
        OGRSpatialReferenceH hSrcSRS;
        OGRSpatialReferenceH hDestSRS;
        OGRCoordinateTransformationH hTransform;
        OGRStyleTableH hStyleTbl;
        unsigned char *pafScanline;
        char** papszOptions;
        OGRLayerH hLayer;
        OGRFieldDefnH hFieldDefn;
        OGRDataSourceH hDataSource;
        GDALDriverH hOGRDriver;

}; /* -----  end of class OutputWriter  ----- */

#endif /*  OUTPUTWRITER_H  */
