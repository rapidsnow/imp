//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>

#include "impressionist.h"
#include "originalView.h"
#include "paintView.h"
#include "previewView.h"

#include "impBrush.h"

const int FLT_WIDTH = 5;
const int FLT_HEIGHT = 5;

class ImpressionistUI {
public:
	ImpressionistUI();
	~ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	PreviewView*		m_previewView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_BrushAngleSlider;
	Fl_Slider*			m_AlphaSlider;
	Fl_Slider*			m_ScatterRadiusSlider;
	Fl_Button*          m_ClearCanvasButton;

	Fl_Round_Button*	m_BrushAngleRadio;

// for kernel dialog
	Fl_Window*			m_kernelDialog;
	Fl_Choice*			m_KernelSizeXChoice;
	Fl_Choice*			m_KernelSizeYChoice;
	Fl_Button*			m_ApplyKernelButton;
	Fl_Button*			m_PreviewKernelButton;
	Fl_Button*			m_CancelKernelButton;
	Fl_Float_Input*		m_KernelDivisorInput;
	Fl_Float_Input*		m_KernelOffsetInput;
	Fl_Float_Input*		m_KernelGrid[3*3];

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);

	int					getLineWidth();
	void				setLineWidth(int lineWidth);

	int					getBrushAngle();						// get the brush angle
	void				setBrushAngle(int BrushAngle);			// set the brush angle

	int					getAngleRadio();						// get the method to use to determine angle
	void				setAngleRadio(int choice);				// set the angle choice

	int					getAlpha();								// get the alpha value
	void				setAlpha(int alpha);					// set the alpha value

	int					getScatterRadius();						// get the scatter radius for scatteredPointsBrush
	void				setScatterRadius(int scatterRadius);	// get the scatter radius for scatteredPointsBrush

	// Callbacks for the image filter dialogue (different from
	// the other callbacks because they aren't static)
	void				initFltDesignUI(void);
	void				updateFilter(void);

	void				cancelFilter(void);
	void				applyFilter(void);
	void				previewFilter(void);

	int					getKernelSizeX();
	void				setKernelSizeX(int size);

	int					getKernelSizeY();
	void				setKernelSizeY(int size);

	float				getKnlValue(int index);
	void				setKnlValue(float value, int index);

	void				setDivisor(float div);
	float				getDivisor();

	void				setOffset(float div);
	float				getOffset();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int m_nSize;
	int m_nLineWidth;
	int m_nBrushAngle;
	int m_nAngleChoice;
	int m_nAlpha;
	int m_nCircleRadius;
	int m_nScatterRadius;

	int m_nKernelSizeX;
	int m_nKernelSizeY;
	float m_nDivisor;
	float m_nOffset;
	float m_nKernel[3*3];
	float m_nTmpKnlValue;

	// These attributes are set by the filter kernel UI
	double fltKernel[FLT_WIDTH*FLT_HEIGHT];		//the kernel of the image filter
	double scale,offset;						//the divisor and offset parameter, 
												//applied after convolving to transform 
												//the filtered image into the range [0,255]


	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		kernelSizeMenu[4];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void cb_kernel(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_angle_radio_0(Fl_Widget* o, void* v);
	static void cb_angle_radio_1(Fl_Widget* o, void* v);
	static void cb_angle_radio_2(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_widthSlides(Fl_Widget* o, void* v);
	static void cb_angleSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_scatterRadiusSlides(Fl_Widget* o, void* v);
	static void	cb_filter_kernel(Fl_Widget* o, void* v);
	static void	cb_filter_preview(Fl_Widget* o, void* v);
	static void	cb_kernel_size_x(Fl_Widget* o, void* v);
	static void	cb_kernel_size_y(Fl_Widget* o, void* v);
	static void	cb_divisor(Fl_Widget* o, void* v);
	static void	cb_offset(Fl_Widget* o, void* v);
	static void	cb_cancel(Fl_Widget* o, void* v);
	//static void	cb_kernel_values(Fl_Widget* o, void* v);
	static void	cb_kernel_values_0(Fl_Widget* o, void* v);
	static void	cb_kernel_values_1(Fl_Widget* o, void* v);
	static void	cb_kernel_values_2(Fl_Widget* o, void* v);
	static void	cb_kernel_values_3(Fl_Widget* o, void* v);
	static void	cb_kernel_values_4(Fl_Widget* o, void* v);
	static void	cb_kernel_values_5(Fl_Widget* o, void* v);
	static void	cb_kernel_values_6(Fl_Widget* o, void* v);
	static void	cb_kernel_values_7(Fl_Widget* o, void* v);
	static void	cb_kernel_values_8(Fl_Widget* o, void* v);

};

#endif

