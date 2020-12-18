
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



#include "czmilCreateAudit.hpp"


double settings_version = 2.0;


czmilCreateAudit::czmilCreateAudit (QWidget *parent)
  : QWizard (parent)
{
  QResource::registerResource ("/icons.rcc");


  //  Set the main icon

  setWindowIcon (QIcon (":/icons/czmilCreateAudit.png"));


  envin ();


  // Set the application font

  QApplication::setFont (options.font);


  setWizardStyle (QWizard::ClassicStyle);


  setOption (HaveHelpButton, true);
  setOption (ExtendedWatermarkPixmap, false);


  connect (this, SIGNAL (helpRequested ()), this, SLOT (slotHelpClicked ()));


  //  Set the window size and location from the defaults

  this->resize (options.window_width, options.window_height);
  this->move (options.window_x, options.window_y);

  setPage (0, new startPage (this));
  setPage (1, optionPg = new optionPage (this, &options));
  setPage (2, new fileInputPage (this, &inputFiles, options.input_dir));
  setPage (3, new runPage (this, &progress, &options));


  setButtonText (QWizard::CustomButton1, tr("&Run"));
  setOption (QWizard::HaveCustomButton1, true);
  button (QWizard::CustomButton1)->setToolTip (tr ("Start audit creation"));
  connect (this, SIGNAL (customButtonClicked (int)), this, SLOT (slotCustomButtonClicked (int)));


  setStartId (0);
}



czmilCreateAudit::~czmilCreateAudit ()
{
}



void czmilCreateAudit::initializePage (int id)
{
  button (QWizard::HelpButton)->setIcon (QIcon (":/icons/contextHelp.png"));
  button (QWizard::CustomButton1)->setEnabled (false);

  switch (id)
    {
    case 0:
      input_files.clear ();
      break;

    case 1:
      break;

    case 2:
      break;

    case 3:

      button (QWizard::CustomButton1)->setEnabled (true);

      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1] = field ("czmilChan1").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2] = field ("czmilChan2").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3] = field ("czmilChan3").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4] = field ("czmilChan4").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5] = field ("czmilChan5").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6] = field ("czmilChan6").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7] = field ("czmilChan7").toBool ();
      options.czmil_chan[CZMIL_IR_CHANNEL] = field ("czmilIRChan").toBool ();
      options.czmil_chan[CZMIL_DEEP_CHANNEL] = field ("czmilDeepChan").toBool ();
      options.water_surface = field ("waterSurface").toBool ();


      //  Use frame geometry to get the absolute x and y.

      QRect tmp = this->frameGeometry ();
      options.window_x = tmp.x ();
      options.window_y = tmp.y ();


      //  Use geometry to get the width and height.

      tmp = this->geometry ();
      options.window_width = tmp.width ();
      options.window_height = tmp.height ();


      envout ();


      break;
    }
}



void czmilCreateAudit::cleanupPage (int id)
{
  switch (id)
    {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;
    }
}



//  This is where the fun stuff happens.

void 
czmilCreateAudit::slotCustomButtonClicked (int id __attribute__ ((unused)))
{
  QApplication::setOverrideCursor (Qt::WaitCursor);


  button (QWizard::FinishButton)->setEnabled (false);
  button (QWizard::BackButton)->setEnabled (false);
  button (QWizard::CustomButton1)->setEnabled (false);


  //  Get the files from the QTextEdit box on the fileInputPage.

  QTextCursor inputCursor = inputFiles->textCursor ();

  inputCursor.setPosition (0);


  QStringList isort_files;

  isort_files.clear ();

  do
    {
      isort_files << inputCursor.block ().text ();
    } while (inputCursor.movePosition (QTextCursor::NextBlock));


  //  Sort so we can remove dupes.

  isort_files.sort ();


  //  Remove dupes and place into input_files.

  QString name, prev_name = "";
  input_files.clear ();

  for (int32_t i = 0 ; i < isort_files.size () ; i++)
    {
      name = isort_files.at (i);

      if (name != prev_name)
        {
          input_files.append (name);
          prev_name = name;
        }
    }


  input_file_count = input_files.size ();


  //  Main processing loop

  CZMIL_CPF_Header                cpf_header;
  CZMIL_CPF_Data                  cpf;
  CZMIL_CAF_Header                caf_header;
  CZMIL_CAF_Data                  caf;
  int32_t                         cpf_hnd, caf_hnd, percent = 0, old_percent = -1, create_count = 0;
  char                            string[1024];


  progress.obar->setRange (0, input_file_count * 100);


  //  Loop through each input file.

  for (int32_t i = 0 ; i < input_file_count ; i++)
    {
      name = input_files.at (i);

      strcpy (string, name.toLatin1 ());


      QString status;
      status.sprintf ("Processing file %d of %d : ", i + 1, input_file_count);
      status += QFileInfo (name).fileName ();

      QListWidgetItem *stat = new QListWidgetItem (status);

      progress.list->addItem (stat);
      progress.list->setCurrentItem (stat);
      progress.list->scrollToItem (stat);


      //  Try to open the input file.

      if ((cpf_hnd = czmil_open_cpf_file (string, &cpf_header, CZMIL_READONLY_SEQUENTIAL)) < 0)
        {
          QMessageBox::critical (this, tr ("czmilCreateAudit Open input file"), tr ("The file ") + name + 
                                 tr (" could not be opened.") + tr ("  The error message returned was:\n\n") +
                                 QString (czmil_strerror ()));
        }
      else
        {
          //  Try to open the output file.

          QString cafName = name;
          cafName.replace (".cpf", ".caf");
          char caf_name[1024];
          strcpy (caf_name, cafName.toLatin1 ());


          //  First, we want to make sure there isn't already a CAF file for this CPF.  If one is already there, we want to
          //  make sure it has been applied.  If it hasn't we're going to tell the user to deal with it externally.

          if ((caf_hnd = czmil_open_caf_file (caf_name, &caf_header)) == CZMIL_SUCCESS)
            {
              if (!caf_header.application_timestamp)
                {
                  QMessageBox::critical (this, tr ("czmilApplyAudit"), tr ("The file ") + cafName + tr (" already exists and it has not been applied.\n") +
                                         tr ("If you really want to replace this file with a new one you must manually delete it.\n\nTerminating!"));
                  exit (-1);
                }

              czmil_close_caf_file (caf_hnd);
            }


          memset (&caf_header, 0, sizeof (CZMIL_CAF_Header));

          if ((caf_hnd = czmil_create_caf_file (caf_name, &caf_header)) != CZMIL_SUCCESS)
            {
              QMessageBox::critical (this, tr ("czmilCreateAudit Create output file"), tr ("The file ") + cafName + 
                                     tr (" could not be created.") + tr ("  The error message returned was:\n\n") +
                                     QString (czmil_strerror ()));
            }
          else
            {
              progress.fbar->reset ();

              progress.fbox->setTitle (QFileInfo (name).fileName ());

              progress.fbar->setRange (0, 100);


              //  Loop through the entire file reading each record.

              for (int32_t rec = 0 ; rec < cpf_header.number_of_records ; rec++)
                {
                  if (czmil_read_cpf_record (cpf_hnd, rec, &cpf) != CZMIL_SUCCESS)
                    {
                      QMessageBox::critical (this, tr ("czmilCreateAudit Read CPF record"), tr ("Record %1 ").arg (rec) + tr ("in file ") + name + 
                                             tr (" could not be read.") + tr ("  The error message returned was:\n\n") +
                                             QString (czmil_strerror ()));
                      exit (-1);
                    }


                  for (int32_t k = 0 ; k < 9 ; k++)
                    {
                      //  Check to see if we are going to use the specific channel.

                      if (options.czmil_chan[k])
                        {
                          for (int32_t m = 0 ; m < cpf.returns[k] ; m++)
                            {
                              //  Check for a manually invalid point.

                              if (cpf.channel[k][m].status & CZMIL_RETURN_MANUALLY_INVAL)
                                {
                                  //  Check for including water surface if requested.

                                  if (cpf.channel[k][m].ip_rank || options.water_surface || cpf.optech_classification[k] == CZMIL_OPTECH_CLASS_HYBRID)
                                    {
                                      caf.shot_id = rec;
                                      caf.channel_number = k;
                                      caf.optech_classification = cpf.optech_classification[k];
                                      caf.interest_point = cpf.channel[k][m].interest_point;
                                      caf.return_number = m;
                                      caf.number_of_returns = cpf.returns[k];

                                      create_count++;


                                      //  Write the record.

                                      if (czmil_write_caf_record (caf_hnd, &caf) != CZMIL_SUCCESS)
                                        {
                                          QMessageBox::critical (this, tr ("czmilCreateAudit Write CAF record"), tr ("Error writing to file ") + name + 
                                                                 tr ("  The error message returned was:\n\n") + QString (czmil_strerror ()));
                                          exit (-1);
                                        }
                                    }
                                }
                            }
                        }
                    }


                  //  We don't want to eat up all of the free time on the system with a progress bar.

                  percent = (int32_t) (((float) rec / (float) cpf_header.number_of_records) * 100.0);
                  if (percent - old_percent >= 10 || old_percent > percent)
                    {
                      progress.fbar->setValue (percent);
                      old_percent = percent;

                      qApp->processEvents ();
                    }
                }

              czmil_close_caf_file (caf_hnd);


              progress.list->addItem (" ");
              QListWidgetItem *tot = new QListWidgetItem (tr ("File : ") + cafName + tr ("\n%1 audit records written.").arg (create_count));

              progress.list->addItem (tot);
              progress.list->setCurrentItem (tot);
              progress.list->scrollToItem (tot);

              create_count = 0;
            }


          czmil_close_cpf_file (cpf_hnd);


          progress.fbar->setValue (100);
        }
    }


  progress.obar->setValue (input_file_count * 100);


  button (QWizard::FinishButton)->setEnabled (true);
  button (QWizard::CancelButton)->setEnabled (false);


  QApplication::restoreOverrideCursor ();
  qApp->processEvents ();

  progress.list->addItem (" ");
  QListWidgetItem *cur = new QListWidgetItem (tr ("Processing complete, press Finish to exit."));

  progress.list->addItem (cur);
  progress.list->setCurrentItem (cur);
  progress.list->scrollToItem (cur);
}



//  Get the users defaults.

void
czmilCreateAudit::envin ()
{
  //  We need to get the font from the global settings.

#ifdef NVWIN3X
  QString ini_file2 = QString (getenv ("USERPROFILE")) + "/ABE.config/" + "globalABE.ini";
#else
  QString ini_file2 = QString (getenv ("HOME")) + "/ABE.config/" + "globalABE.ini";
#endif

  options.font = QApplication::font ();

  QSettings settings2 (ini_file2, QSettings::IniFormat);
  settings2.beginGroup ("globalABE");


  QString defaultFont = options.font.toString ();
  QString fontString = settings2.value (QString ("ABE map GUI font"), defaultFont).toString ();
  options.font.fromString (fontString);


  settings2.endGroup ();


  double saved_version = 1.0;


  // Set defaults so that if keys don't exist the parameters are defined

  options.window_x = 0;
  options.window_y = 0;
  options.window_width = 900;
  options.window_height = 500;
  options.input_dir = ".";
  for (int32_t i = 0 ; i < 9 ; i++)
    {
      options.czmil_chan[i] = NVTrue;
    }
  options.water_surface = NVFalse;


  //  Setting CZMIL channel 7 (IR) to NVFalse because we usually won't want that.

  options.czmil_chan[7] = NVFalse;


  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmilCreateAudit.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmilCreateAudit.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmilCreateAudit");

  saved_version = settings.value (QString ("settings version"), saved_version).toDouble ();


  //  If the settings version has changed we need to leave the values at the new defaults since they may have changed.

  if (settings_version != saved_version) return;


  options.window_width = settings.value (QString ("width"), options.window_width).toInt ();
  options.window_height = settings.value (QString ("height"), options.window_height).toInt ();
  options.window_x = settings.value (QString ("x position"), options.window_x).toInt ();
  options.window_y = settings.value (QString ("y position"), options.window_y).toInt ();

  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1] =
    settings.value (QString ("use CZMIL shallow channel 1"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2] =
    settings.value (QString ("use CZMIL shallow channel 2"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3] =
    settings.value (QString ("use CZMIL shallow channel 3"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4] =
    settings.value (QString ("use CZMIL shallow channel 4"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5] =
    settings.value (QString ("use CZMIL shallow channel 5"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6] =
    settings.value (QString ("use CZMIL shallow channel 6"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7] =
    settings.value (QString ("use CZMIL shallow channel 7"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7]).toBool ();
  options.czmil_chan[CZMIL_IR_CHANNEL] = settings.value (QString ("use CZMIL IR channel"), options.czmil_chan[CZMIL_IR_CHANNEL]).toBool ();
  options.czmil_chan[CZMIL_DEEP_CHANNEL] = settings.value (QString ("use CZMIL DEEP channel"), options.czmil_chan[CZMIL_DEEP_CHANNEL]).toBool ();
  options.water_surface = settings.value (QString ("include water surface"), options.water_surface).toBool ();

  settings.endGroup ();
}




//  Save the users defaults.

void
czmilCreateAudit::envout ()
{
  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmilCreateAudit.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmilCreateAudit.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmilCreateAudit");


  settings.setValue (QString ("settings version"), settings_version);

  settings.setValue (QString ("width"), options.window_width);
  settings.setValue (QString ("height"), options.window_height);
  settings.setValue (QString ("x position"), options.window_x);
  settings.setValue (QString ("y position"), options.window_y);

  settings.setValue (QString ("use CZMIL shallow channel 1"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1]);
  settings.setValue (QString ("use CZMIL shallow channel 2"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2]);
  settings.setValue (QString ("use CZMIL shallow channel 3"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3]);
  settings.setValue (QString ("use CZMIL shallow channel 4"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4]);
  settings.setValue (QString ("use CZMIL shallow channel 5"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5]);
  settings.setValue (QString ("use CZMIL shallow channel 6"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6]);
  settings.setValue (QString ("use CZMIL shallow channel 7"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7]);
  settings.setValue (QString ("use CZMIL IR channel"), options.czmil_chan[CZMIL_IR_CHANNEL]);
  settings.setValue (QString ("use CZMIL DEEP channel"), options.czmil_chan[CZMIL_DEEP_CHANNEL]);
  settings.setValue (QString ("include water surface"), options.water_surface);

  settings.endGroup ();
}



void 
czmilCreateAudit::slotHelpClicked ()
{
  QWhatsThis::enterWhatsThisMode ();
}
