
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



QString czmil1Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 1 (central channel) data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil2Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 2 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil3Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 3 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil4Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 4 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil5Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 5 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil6Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 6 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmil7Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 7 data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmilIRText = 
  optionPage::tr ("Checking this box will cause all CZMIL IR Channel data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString czmilDeepText = 
  optionPage::tr ("Checking this box will cause all CZMIL Deep Channel data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).");

QString waterSurfaceText = 
  optionPage::tr ("Checking this box will cause all water surface data that is marked as "
                  "manually invalid to be placed in the CZMIL audit file (.caf).  Water surface data "
                  "(water processed returns with an ip_rank of 0) are not usually loaded into a PFM so this is usually not "
                  "checked.");
