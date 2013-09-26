// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	int     clearPreview();                 // called by the UI to clear the preview canvas

	void applyFilter( const unsigned char* sourceBuffer, //The filter kernel
					  int srcBufferWidth, 
					  int srcBufferHeight,
					  unsigned char* destBuffer,
					  const float *filterKernel, 
					  int knlWidth, 
					  int knlHeight, 
					  float divisor, 
					  double offset );

	void	setBrushType(int type);					// called by the UI to set the brushType
	int		getSize();								// get the UI size
	void	setSize(int size);						// set the UI size
	int		getLineWidth();							// get the line width
	void	setLineWidth(int lineWidth);			// set the line width

	int		getBrushAngle();						// get the brush angle
	void	setBrushAngle(int BrushAngle);			// set the brush angle

	int		getAngleRadio();						// get and set the radio button number for angle determination
	void	setAngleRadio(int choice);

	Point	getRightClickStart();					// get the start point for angle calculations
	void	setRightClickStart(Point start);		// set the start point for angle calculations

	int		getAlpha();								// get the alpha value
	void	setAlpha(int alpha);					// set the alpha value
	int		getScatterRadius();						// get the scatter radius for scatteredPointsBrush
	void	setScatterRadius(int scatterRadius);	// get the scatter radius for scatteredPointsBrush

	char*	getImageName();							// get the current image name

	void	setKernelSizeX(int size);				//Set the x kernel dimension
	int		getKernelSizeX();						//Get the x kernel dimension
	void	setKernelSizeY(int size);				//Set the y kernel dimension
	int		getKernelSizeY();						//Get the y kernel dimension
	void	setDivisor(float div);
	float	getDivisor();
	void	setOffset(float off);
	float	getOffset();
	void	setKnlValue(float value, int index);	//Set the temporary kernel value
	float   getKnlValue(int index);					//Get the temporary kernel value

	Point	getLastPoint();							// get the last point, used for brush angle calculations
	void	setLastPoint(Point start);				// set the last point, used for brush angle calculations

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	// Used by the filtering code so that we can
	// preview filters before applying.
	unsigned char*	m_ucPreviewBackup;



	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;
	int m_nLineWidth;
	int m_nBrushAngle;
	int m_nAngleChoice;
	int m_nAlpha;
	int m_nScatterRadius;

	// Size of the kernel;
	int m_nKernelSizeX;
	int m_nKernelSizeY;
	float m_nTmpKnlValue;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );



private:
	char			m_imageName[256];
	Point			m_pRightClickStart;
	Point			m_pLastPoint;

};

extern void MessageBox(char *message);

#endif
