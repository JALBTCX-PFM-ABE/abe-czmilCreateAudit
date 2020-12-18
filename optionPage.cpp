
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



#include "optionPage.hpp"
#include "optionPageHelp.hpp"


optionPage::optionPage (QWidget *prnt, OPTIONS *op):
  QWizardPage (prnt)
{
  options = op;
  parent = prnt;

  setTitle (tr ("Options"));

  setPixmap (QWizard::WatermarkPixmap, QPixmap (":/icons/czmilCreateAuditWatermark.png"));


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);


  czmilChan[CZMIL_SHALLOW_CHANNEL_1] = new QCheckBox (tr ("Shallow Channel 1"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setToolTip (tr ("If checked, include CZMIL shallow channel 1 (central channel) data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setWhatsThis (czmil1Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_1]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_1]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_2] = new QCheckBox (tr ("Shallow Channel 2"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setToolTip (tr ("If checked, include CZMIL shallow channel 2 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setWhatsThis (czmil2Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_2]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_2]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_3] = new QCheckBox (tr ("Shallow Channel 3"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setToolTip (tr ("If checked, include CZMIL shallow channel 3 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setWhatsThis (czmil3Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_3]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_3]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_4] = new QCheckBox (tr ("Shallow Channel 4"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setToolTip (tr ("If checked, include CZMIL shallow channel 4 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setWhatsThis (czmil4Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_4]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_4]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_5] = new QCheckBox (tr ("Shallow Channel 5"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setToolTip (tr ("If checked, include CZMIL shallow channel 5 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setWhatsThis (czmil5Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_5]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_5]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_6] = new QCheckBox (tr ("Shallow Channel 6"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setToolTip (tr ("If checked, include CZMIL shallow channel 6 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setWhatsThis (czmil6Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_6]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_6]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_7] = new QCheckBox (tr ("Shallow Channel 7"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setToolTip (tr ("If checked, include CZMIL shallow channel 7 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setWhatsThis (czmil7Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_7]);
  vbox->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_7]);

  czmilChan[CZMIL_IR_CHANNEL] = new QCheckBox (tr ("IR Channel"), this);
  czmilChan[CZMIL_IR_CHANNEL]->setToolTip (tr ("If checked, include CZMIL IR data"));
  czmilChan[CZMIL_IR_CHANNEL]->setWhatsThis (czmilIRText);
  czmilChan[CZMIL_IR_CHANNEL]->setChecked (options->czmil_chan[CZMIL_IR_CHANNEL]);
  vbox->addWidget (czmilChan[CZMIL_IR_CHANNEL]);

  czmilChan[CZMIL_DEEP_CHANNEL] = new QCheckBox (tr ("Deep Channel"), this);
  czmilChan[CZMIL_DEEP_CHANNEL]->setToolTip (tr ("If checked, include CZMIL Deep Channel data"));
  czmilChan[CZMIL_DEEP_CHANNEL]->setWhatsThis (czmilDeepText);
  czmilChan[CZMIL_DEEP_CHANNEL]->setChecked (options->czmil_chan[CZMIL_DEEP_CHANNEL]);
  vbox->addWidget (czmilChan[CZMIL_DEEP_CHANNEL]);

  waterSurface = new QCheckBox (tr ("Include water surface data"), this);
  waterSurface->setToolTip (tr ("If checked, include water surface (water processed ip_rank = 0) data"));
  waterSurface->setWhatsThis (waterSurfaceText);
  waterSurface->setChecked (options->water_surface);
  vbox->addWidget (waterSurface);


  registerField ("czmilChan1", czmilChan[CZMIL_SHALLOW_CHANNEL_1]);
  registerField ("czmilChan2", czmilChan[CZMIL_SHALLOW_CHANNEL_2]);
  registerField ("czmilChan3", czmilChan[CZMIL_SHALLOW_CHANNEL_3]);
  registerField ("czmilChan4", czmilChan[CZMIL_SHALLOW_CHANNEL_4]);
  registerField ("czmilChan5", czmilChan[CZMIL_SHALLOW_CHANNEL_5]);
  registerField ("czmilChan6", czmilChan[CZMIL_SHALLOW_CHANNEL_6]);
  registerField ("czmilChan7", czmilChan[CZMIL_SHALLOW_CHANNEL_7]);
  registerField ("czmilIRChan", czmilChan[CZMIL_IR_CHANNEL]);
  registerField ("czmilDeepChan", czmilChan[CZMIL_DEEP_CHANNEL]);
  registerField ("waterSurface", waterSurface);
}
