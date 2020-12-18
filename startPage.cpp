
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



#include "startPage.hpp"

startPage::startPage (QWidget *parent):
  QWizardPage (parent)
{
  setPixmap (QWizard::WatermarkPixmap, QPixmap(":/icons/czmilCreateAuditWatermark.png"));


  setTitle (tr ("Introduction"));

  setWhatsThis (tr ("See, it really works!"));

  QLabel *label = new QLabel (tr ("The czmilCreateAudit program is used to capture audit information from CZMIL CPF files that have "
                                  "had their data edited via the Area-Based Editor or the CZMIL Manual Editor.  This means that the "
                                  "CPF data have been loaded into a PFM structure, editing has been performed on the PFM, and the edits "
                                  "have been unloaded to the CPF files.  In order for this program to work the edits <b>must be unloaded</b> "
                                  "from the PFM to the CPF files prior to running this program.  Only data points marked as <b><i>manually "
                                  "invalid</i></b> will be included in the CZMIL Audit File (.caf).  You may limit the channels that are "
                                  "audited by selecting specific channels in the option page.  Normally you would include all channels except, "
                                  "possibly, the IR.<br><br>"
                                  "Click the Next button to go to the Options page.  Context sensitive help is available "
                                  "by clicking on the Help button and then clicking, with the Question Arrow cursor, on the "
                                  "field of interest."));


  label->setWordWrap(true);


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->addWidget (label);
  vbox->addStretch (10);
}
