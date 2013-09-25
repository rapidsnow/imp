//
// impressionistUI.cpp
//
// The user interface part for the program.
//


#include <FL/fl_ask.H>

#include <algorithm>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    myWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}





//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version 1.1.9 for CS 384G, Fall 2008");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	//	int type=(int)v;
	long long tmp = reinterpret_cast<long long>(v);
	int type = static_cast<int>(tmp);

	pDoc->setBrushType(type);
}

//--------------------------------------------------------
// Fairly inelegant way of deciding which brush angle
// determination method to use
// Seriously, how the hell do you pass arguments without breaking the ability to get pDoc?
// You can do it with menu items for the choice things, but there is no equivalent for buttons, 
// they can only have 0 or 1 for a value
//--------------------------------------------------------
void ImpressionistUI::cb_angle_radio_0(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->setAngleRadio(0);
}
void ImpressionistUI::cb_angle_radio_1(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->setAngleRadio(1);
}
void ImpressionistUI::cb_angle_radio_2(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->setAngleRadio(2);
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------------
// Updates the line brush width to use from the value of the width
// slider
// Called by the UI when the width slider is moved
//-----------------------------------------------------------------
void ImpressionistUI::cb_widthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the brush angle to use from the value of the angle
// slider
// Called by the UI when the angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nBrushAngle=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the alpha value to use from the value of the alpha
// slider
// Called by the UI when the alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------------------
// Updates the scatter radius to use from the value of the scatter radius
// slider
// Called by the UI when the alpha slider is moved
//-----------------------------------------------------------------------
void ImpressionistUI::cb_scatterRadiusSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nScatterRadius=int( ((Fl_Slider *)o)->value() ) ;
}


//----------- Kernel Dialog Callbacks -------------
//-----------------------------------------------------------------------
// Applies the given kernel to the image
// Called by the UI when the apply filter button is pressed
//-----------------------------------------------------------------------

//-------------------------------------------------------------
// Brings up the kernel dialog
// This is called by the UI when the kernel menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_kernel(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_kernelDialog->show();
}

//---The kernel grid callback------------------------
void ImpressionistUI::cb_kernel_values(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	//	int index=(int)v;
	long long tmp = reinterpret_cast<long long>(v);
	int index = static_cast<int>(tmp);

	float value = atof( ((Fl_Float_Input *)o)->value() ); //atof() casts from unsigned char to float
	printf("%d: %f\n", index, value);

	//pDoc->setTmpKnlValue(value);
}


void ImpressionistUI::cb_filter_kernel(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI * m_pUI = pDoc->m_pUI;
	pDoc->applyFilter(pDoc->m_ucPainting,
		pDoc->m_nPaintWidth,
		pDoc->m_nPaintHeight,
		pDoc->m_ucPainting,
		m_pUI->m_nKernel,
		5,
		5,
		0.,
		0.);
	/*pDoc->applyFilter(m_paintView, 
		m_paintView->m_nWindowWidth, 
		m_paintView->m_nWindowHeight, 
		m_paintView, 
		m_nKernel, 
		5 //pDoc->getKernelSizeX(), 
		5 //pDoc->getKernelSizeY(),
		0., 
		m_paintView->m_pPaintBitstart);*/
}

void ImpressionistUI::cb_kernel_size_x(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	//	Intuitively equivalent to int size=(int)v;
	long long tmp = reinterpret_cast<long long>(v);
	int size = static_cast<int>(tmp);

	pDoc->setKernelSizeX(size);
}

void ImpressionistUI::cb_kernel_size_y(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	//	Intuitively equivalent to int size=(int)v;
	long long tmp = reinterpret_cast<long long>(v);
	int size = static_cast<int>(tmp);

	pDoc->setKernelSizeY(size);
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the brush lineWidth
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}


//------------------------------------------------
// Set the brush lineWidth
//------------------------------------------------
void ImpressionistUI::setLineWidth(int lineWidth)
{
	m_nLineWidth=lineWidth;

	if (lineWidth<=40)
		m_LineWidthSlider->value(m_nLineWidth);
}

// Helper function for setting the angle determination method
void ImpressionistUI::setAngleRadio(int choice)
{
	m_nAngleChoice=choice;
}

int ImpressionistUI::getAngleRadio()
{
	return m_nAngleChoice;
}

//------------------------------------------------
// Return the brush angle
//------------------------------------------------
int ImpressionistUI::getBrushAngle()
{
	return m_nBrushAngle;
}


//------------------------------------------------
// Set the brush angle
//------------------------------------------------
void ImpressionistUI::setBrushAngle(int BrushAngle)
{
	m_nBrushAngle=BrushAngle;

	if (BrushAngle<=360 && m_nAngleChoice==0)
		m_BrushAngleSlider->value(m_nBrushAngle);
}

//------------------------------------------------
// Return the alpha value
//------------------------------------------------
int ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}


//------------------------------------------------
// Set the alpha value
//------------------------------------------------
void ImpressionistUI::setAlpha(int alpha)
{
	m_nAlpha=alpha;

	if (alpha<=255)
		m_AlphaSlider->value(m_nAlpha);
}

//------------------------------------------------
// Return the scatter radius
//------------------------------------------------
int ImpressionistUI::getScatterRadius()
{
	return m_nScatterRadius;
}


//------------------------------------------------
// Set the scatter radius
//------------------------------------------------
void ImpressionistUI::setScatterRadius(int scatterRadius)
{
	m_nScatterRadius=scatterRadius;

	if (scatterRadius<=40)
		m_ScatterRadiusSlider->value(m_nScatterRadius);
}

//------------------------------------------------
// Return the X kernel Size
//------------------------------------------------
int ImpressionistUI::getKernelSizeX()
{
	return m_nKernelSizeX;
}


//------------------------------------------------
// Set the X kernel size
//------------------------------------------------
void ImpressionistUI::setKernelSizeX(int size)
{
	m_nKernelSizeX=size;
}

//------------------------------------------------
// Return the Y kernel Size
//------------------------------------------------
int ImpressionistUI::getKernelSizeY()
{
	return m_nKernelSizeY;
}


//------------------------------------------------
// Set the Y kernel size
//------------------------------------------------
void ImpressionistUI::setKernelSizeY(int size)
{
	m_nKernelSizeY=size;
}

//------------------------------------------------
// Return the temporary kernel value
//------------------------------------------------
float ImpressionistUI::getTmpKnlValue()
{
	return m_nTmpKnlValue;
}

//------------------------------------------------
// Set the temporary kernel value
//------------------------------------------------
void ImpressionistUI::setTmpKnlValue(float tmp)
{
	m_nTmpKnlValue=tmp;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Kernel...",     FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_kernel },
		{ "&Clear Canvas",  FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {0}
};

// Kernel Size menu definition
Fl_Menu_Item ImpressionistUI::kernelSizeMenu[6] = {
  {"1",	FL_ALT+'1', (Fl_Callback *)ImpressionistUI::cb_kernel_size_x, (void *) 1},
  {"2",	FL_ALT+'2', (Fl_Callback *)ImpressionistUI::cb_kernel_size_x, (void *) 2},
  {"3",	FL_ALT+'3', (Fl_Callback *)ImpressionistUI::cb_kernel_size_x, (void *) 3},
  {"4",	FL_ALT+'4', (Fl_Callback *)ImpressionistUI::cb_kernel_size_x, (void *) 4},
  {"5",	FL_ALT+'5', (Fl_Callback *)ImpressionistUI::cb_kernel_size_x, (void *) 5},
  {0}
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values
	m_nSize = 10;
	m_nLineWidth = 1;
	m_nBrushAngle = 0;
	m_nAlpha = 255;
	m_nScatterRadius = 10;

	m_nKernelSizeX = 5;
	m_nKernelSizeY = 5;

	// brush dialog definition
	m_brushDialog = new Fl_Window(450, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);
		
		
		//Add line width slider to the dialog
		Fl_Value_Slider * m_LineWidthSlider = new Fl_Value_Slider(10, 105, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_widthSlides);
		
		
		//Add brush angle slider to the dialog
		Fl_Value_Slider * m_BrushAngleSlider = new Fl_Value_Slider(10, 130, 300, 20, "Brush Angle");
		m_BrushAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_BrushAngleSlider->labelfont(FL_COURIER);
		m_BrushAngleSlider->labelsize(12);
		m_BrushAngleSlider->minimum(0);
		m_BrushAngleSlider->maximum(360);
		m_BrushAngleSlider->step(5);
		m_BrushAngleSlider->value(m_nBrushAngle);
		m_BrushAngleSlider->align(FL_ALIGN_RIGHT);
		m_BrushAngleSlider->callback(cb_angleSlides);
				

		//Add alpha slider to the dialog
		Fl_Value_Slider * m_AlphaSlider = new Fl_Value_Slider(10, 155, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0);
		m_AlphaSlider->maximum(255);
		m_AlphaSlider->step(1);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);

		
		//Add scatter radius slider to the dialog
		Fl_Value_Slider * m_ScatterRadiusSlider = new Fl_Value_Slider(10, 180, 300, 20, "Scatter Radius");
		m_ScatterRadiusSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_ScatterRadiusSlider->type(FL_HOR_NICE_SLIDER);
		m_ScatterRadiusSlider->labelfont(FL_COURIER);
		m_ScatterRadiusSlider->labelsize(12);
		m_ScatterRadiusSlider->minimum(1);
		m_ScatterRadiusSlider->maximum(100);
		m_ScatterRadiusSlider->step(1);
		m_ScatterRadiusSlider->value(m_nScatterRadius);
		m_ScatterRadiusSlider->align(FL_ALIGN_RIGHT);
		m_ScatterRadiusSlider->callback(cb_scatterRadiusSlides);

		//Add radio button to allow for brush angle selection
		{ Fl_Group* m_BrushAngleRadio = new Fl_Group(10, 210, 300, 30);
					m_BrushAngleRadio->box(FL_THIN_UP_FRAME);
		  { Fl_Round_Button* m_BrushAngleRadio1 = new Fl_Round_Button(15, 210, 30, 30, "Slider");
			m_BrushAngleRadio1->user_data((void*)(this)); //record self to be used by static callback functions
			m_BrushAngleRadio1->labelfont(FL_COURIER);
			m_BrushAngleRadio1->labelsize(12);

			//I've got to be honest. I couldn't find documentation for type(102) anywhere.
			//I took this idea from the test/radio.cxx file in the fltk library.
			//It was the only way that I could get the buttons to behave how I wanted them to.
			m_BrushAngleRadio1->type(102);
			m_BrushAngleRadio1->callback(cb_angle_radio_0); //0 corresponds to determine angle by slider
		  }
		  { Fl_Round_Button* m_BrushAngleRadio2 = new Fl_Round_Button(205, 210, 30, 30, "Right Click");
			m_BrushAngleRadio2->user_data((void*)(this)); //record self to be used by static callback functions
			m_BrushAngleRadio2->labelfont(FL_COURIER);
			m_BrushAngleRadio2->labelsize(12);
			m_BrushAngleRadio2->type(102);
			m_BrushAngleRadio2->callback(cb_angle_radio_1); //1 corresponds to determine angle by right click
		  }
		  { Fl_Round_Button* m_BrushAngleRadio3 = new Fl_Round_Button(78, 210, 30, 30, "Brush Direction");
			m_BrushAngleRadio3->user_data((void*)(this)); //record self to be used by static callback functions
			m_BrushAngleRadio3->labelfont(FL_COURIER);
			m_BrushAngleRadio3->labelsize(12);
			m_BrushAngleRadio3->type(102);
			m_BrushAngleRadio3->callback(cb_angle_radio_2); //2 corresponds to determine angle by cursor
		  }		  
		m_BrushAngleRadio->end();
		}

		

		m_brushDialog->end();

	//Create the kernel dialog window
	m_kernelDialog = new Fl_Window(400, 400, "Kernel Dialog");
		//Create a button to preview the filter kernel to the image
		//m_ApplyKernelButton = new Fl_Button(240,10,150,25,"&Preview Filter");
		//m_ApplyKernelButton->user_data((void*)(this));
		//m_ApplyKernelButton->callback(cb_filter_kernel);
	
		//Create a button to actually apply the filter kernel to the image
		m_ApplyKernelButton = new Fl_Button(240,10,150,25,"&Apply Filter");
		m_ApplyKernelButton->user_data((void*)(this));
		m_ApplyKernelButton->callback(cb_filter_kernel);

		m_KernelSizeXChoice = new Fl_Choice(60,30,50,25,"&X Size");
		m_KernelSizeXChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_KernelSizeXChoice->menu(kernelSizeMenu);

		//TODO: Add functionality to create and destroy the grid below
		m_KernelSizeXChoice->callback(cb_kernel_size_x);

		m_KernelSizeYChoice = new Fl_Choice(60,65,50,25,"&Y Size");
		m_KernelSizeYChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_KernelSizeYChoice->menu(kernelSizeMenu);

		//TODO: Add functionality to create and destroy the grid below
		m_KernelSizeYChoice->callback(cb_kernel_size_y);

		int knlIndex;
		//Create a grid of inputs for the kernel size
		for(int row = 0; row < m_nKernelSizeY; row++) {
			for(int column=0; column < m_nKernelSizeX; column++) {
				knlIndex=row*m_nKernelSizeX+column;
				m_KernelGrid[knlIndex] = new Fl_Float_Input(100 + column * 30, 125 + row * 30, 25, 25, "");
				m_KernelGrid[knlIndex]->user_data((void*)(this));   // record self to be used by static callback functions
				m_KernelGrid[knlIndex]->when(FL_WHEN_CHANGED);
				m_KernelGrid[knlIndex]->callback(cb_kernel_values);
				m_nKernel[knlIndex] = m_nTmpKnlValue;//This row is useless right now, needs to be part of a callback
				//^^ This means that we need to somehow pass in the index to the callback, but I can't figure out how to do that.
			}
		}

		//--------------------------------------------------------
		//
		//			Below is purely for testing because 
		//			my kernel callbacks suck and I'm sick
		//			of working on them.
		//
		//--------------------------------------------------------
		m_nKernel[0]  = 0; m_nKernel[1]  = 0; m_nKernel[2]  = 0; m_nKernel[3]  = 0; m_nKernel[4]  = 0;
		m_nKernel[5]  = 0; m_nKernel[6]  = 1; m_nKernel[7]  = 2; m_nKernel[8]  = 1; m_nKernel[9]  = 0;
		m_nKernel[10] = 0; m_nKernel[11] = 0; m_nKernel[12] = 0; m_nKernel[13] = 0; m_nKernel[14] = 0;
		m_nKernel[15] = 0; m_nKernel[16] = -1; m_nKernel[17] = -2; m_nKernel[18] = 1; m_nKernel[19] = 0;
		m_nKernel[20] = 0; m_nKernel[21] = 0; m_nKernel[22] = 0; m_nKernel[23] = 0; m_nKernel[24] = 0;
}

ImpressionistUI::~ImpressionistUI()
{
}
