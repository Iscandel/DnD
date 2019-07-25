#ifndef H__ANIMATION__H
#define H__ANIMATION__H

#include "tools/Timer.h"

///////////////////////////////////////////////////////////////////////////////
/// \bref Generic class for animation
///////////////////////////////////////////////////////////////////////////////
class Animation
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Type of animation. 
	///////////////////////////////////////////////////////////////////////////
	enum AnimType
	{
		INFINITE, //< Animation continues if finished
		UNIQUE    //< Animation stops if finished
	};

	///////////////////////////////////////////////////////////////////////////
	/// Type of loop.
	///////////////////////////////////////////////////////////////////////////
	enum LoopType
	{
		GO_BACK, //< Animation inverts the sens when the image set is over
		ONE_WAY  //< Animation starts again for the begining
	};
	  
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	/// \params imageNumber number of images in the animation
	///	
	/// \param type	Type of animation
	///		
    ///	\param loopType	Type of loop
	///			
	/// \param timeBetweenImages frame time between 2 images in milliseconds
	///////////////////////////////////////////////////////////////////////////
	Animation(unsigned int imageNumber = 1,
			  AnimType type = UNIQUE, 
			  LoopType tB = GO_BACK, 
			  unsigned int timeBetweenImages = 50);

	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	~Animation(void);

	///////////////////////////////////////////////////////////////////////////
	/// Resets the animation.
	///
	/// \param resetImage if true, resets direction et current image number.
	///////////////////////////////////////////////////////////////////////////
	void reset(bool resetImage = true);

	///////////////////////////////////////////////////////////////////////////
	/// Update the animation.
	///////////////////////////////////////////////////////////////////////////
	void update(unsigned int elapsedTime);

	///////////////////////////////////////////////////////////////////////////
	/// Starts the animation
	///
    /// \param resetImage if true, resets direction et current image number.
	///////////////////////////////////////////////////////////////////////////
	void startAnimation(bool resetImage = true) {reset(resetImage);}

	///////////////////////////////////////////////////////////////////////////
	/// Resumes the animation.
	///////////////////////////////////////////////////////////////////////////
	void resumeAnimation() {myIsStarted = true;}

	///////////////////////////////////////////////////////////////////////////
	/// Stops the animation
	///
    /// \param resetImage if true, resets direction et current image number.
	/// Otherwise, it is equivalent to the pause.
	///////////////////////////////////////////////////////////////////////////
	void stopAnimation(bool reset = true) {myIsStarted = false; if(reset)myCurrentImage = 0;} //Mettre fonction reset � la place

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the animation is paused.
	///
	/// \return true if paused, false if not paused.
	///////////////////////////////////////////////////////////////////////////
	bool isPaused() const {return !myIsStarted;}

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the animation is finished.
	///
	/// \return true if finished, false if not finished.
	///////////////////////////////////////////////////////////////////////////
	bool isFinished() const {return myIsPaused;}

	///////////////////////////////////////////////////////////////////////////
	/// Defines the number of images in the animation.
	///
	/// \param nb number of images in this animation.
	///////////////////////////////////////////////////////////////////////////
	void setImageNumber(unsigned int nb) {myImageNumber = nb;}

	///////////////////////////////////////////////////////////////////////////
	// Defines the type of animationn (Unique, infinite)
	///////////////////////////////////////////////////////////////////////////
	void setAnimType(AnimType t) {myAnimType = t;}

	///////////////////////////////////////////////////////////////////////////
	// Defines the type of loop (1 way, go back)
	///////////////////////////////////////////////////////////////////////////
	void setLoopType(LoopType b) {myLoopType = b;}

	///////////////////////////////////////////////////////////////////////////
	// Defines the time interval between two images
	///////////////////////////////////////////////////////////////////////////
	void setFrameTimeBetweenImages(unsigned int f) {myFrameTime = f;}

	///////////////////////////////////////////////////////////////////////////
	// Returns the index of the current image
	///////////////////////////////////////////////////////////////////////////
	int getImage() const {return myCurrentImage;}

	///////////////////////////////////////////////////////////////////////////
	// Returns the number of images in the animation
	///////////////////////////////////////////////////////////////////////////
	int getNbImages() const {return myImageNumber;}

protected:
	//Type of animation
	AnimType myAnimType;
	//Type of loop in the animation
	LoopType myLoopType;
	//Le nombre d'images
	unsigned int myImageNumber;
	//Time between 2 images
	unsigned int myFrameTime;
	//Current image index
	int myCurrentImage;
	//Indicates whether the animation is running
	bool myIsStarted;
	//Indicates if the image numbers are in the ascending way
	bool myIsFirstDirection;
	//Time measure
	unsigned int myTime;
	//
	bool myIsPaused;
};

#endif